#include "main_training.hpp"

struct Transition {
    std::array<float, STATE_DIM> s;
    int a;
    float r;
    std::array<float, STATE_DIM> s2;
    bool done;
};

class ReplayBuffer {
public:
    ReplayBuffer(size_t capacity=REPLAY_CAPACITY) : capacity(capacity) {}
    void push(const Transition &t) {
        if (buf.size() < capacity) buf.push_back(t);
        else {
            buf[pos] = t;
            pos = (pos + 1) % capacity;
        }
    }
    std::vector<Transition> sample(size_t n) {
        std::vector<Transition> out; out.reserve(n);
        std::uniform_int_distribution<size_t> dist(0, buf.size()-1);
        for (size_t i=0;i<n;i++) out.push_back(buf[dist(rng)]);
        return out;
    }
    size_t size() const { return buf.size(); }
private:
    std::vector<Transition> buf;
    size_t capacity;
    size_t pos = 0;
};

// -------------------- Training --------------------
int main() {
    // Create env and agent
    PongEnv env;
    DQN net;
    net->to(torch::kCPU);

    torch::optim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(LR));
    ReplayBuffer replay;

    float epsilon = EPS_START;
    size_t total_steps = 0;

    std::filesystem::create_directories("models");

    for (int ep = 1; ep <= TRAINING_EPISODES; ++ep) {
        State s = env.reset();
        float episode_reward = 0.0f;

        for (int t = 0; t < MAX_STEPS_PER_EPISODE; ++t) {
            // epsilon-greedy policy
            int action;
            if (randf() < epsilon) {
                action = std::uniform_int_distribution<int>(0, ACTION_DIM-1)(rng);
            } else {
                // query network
                torch::Tensor st = torch::from_blob((float*)s.v.data(), {1, STATE_DIM}).clone();
                torch::Tensor qs = net->forward(st);
                action = qs.argmax(1).item<int>();
            }

            // step environment (we use single frame dt for simplicity)
            StepResult res = env.step(action, PHYS_DT);
            Transition tr;
            std::copy(s.v.begin(), s.v.end(), tr.s.begin());
            tr.a = action;
            tr.r = res.reward;
            std::copy(res.next.v.begin(), res.next.v.end(), tr.s2.begin());
            tr.done = res.done;
            replay.push(tr);

            s = res.next;
            episode_reward += res.reward;
            total_steps++;

            // train
            if (replay.size() >= TRAIN_AFTER && total_steps % TRAIN_EVERY == 0) {
                auto batch = replay.sample(BATCH_SIZE);
                // build tensors
                torch::Tensor state_b = torch::zeros({(int)BATCH_SIZE, STATE_DIM});
                torch::Tensor next_b = torch::zeros({(int)BATCH_SIZE, STATE_DIM});
                torch::Tensor action_b = torch::zeros({(int)BATCH_SIZE}, torch::kInt64);
                torch::Tensor reward_b = torch::zeros({(int)BATCH_SIZE});
                torch::Tensor done_b = torch::zeros({(int)BATCH_SIZE});

                for (size_t i=0;i<batch.size();++i){
                    for (int j=0;j<STATE_DIM;++j){ state_b[i][j] = batch[i].s[j]; next_b[i][j] = batch[i].s2[j]; }
                    action_b[i] = batch[i].a;
                    reward_b[i] = batch[i].r;
                    done_b[i] = batch[i].done ? 0.0f : 1.0f; // multiplier (0 if terminal)
                }

                // Q(s,a)
                torch::Tensor qvals = net->forward(state_b);
                torch::Tensor qvals_a = qvals.gather(1, action_b.unsqueeze(1)).squeeze(1);

                // target: r + gamma * max_a' Q(s',a')
                torch::Tensor qnext = net->forward(next_b);
                torch::Tensor qnext_max = std::get<0>(qnext.max(1));
                torch::Tensor target = reward_b + GAMMA * qnext_max * done_b;

                // loss and step
                torch::Tensor loss = torch::mse_loss(qvals_a, target.detach());
                optimizer.zero_grad();
                loss.backward();
                optimizer.step();
            }

            // epsilon decay
            epsilon = std::max(EPS_END, epsilon * EPS_DECAY);

            if (res.done) break;
        }

        if (ep % 100 == 0) {
            std::cout << "Episode " << ep << " reward " << episode_reward << " epsilon " << epsilon << "\n";
            // save model
            torch::save(net, "models/pong_dqn.pt");
        }
    }

    // final save
    torch::save(net, "models/pong_dqn_final.pt");
    std::cout << "Training done. Model saved to models/pong_dqn_final.pt\n";
    return 0;
}
