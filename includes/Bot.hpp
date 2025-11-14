#include "Ball.hpp"
#include "Player.hpp"
#include <algorithm>

#include <torch/torch.h>

#pragma once

struct DQNImpl : torch::nn::Module {
    DQNImpl() {
        fc1 = register_module("fc1", torch::nn::Linear(6, 64));
        fc2 = register_module("fc2", torch::nn::Linear(64, 64));
        out = register_module("out", torch::nn::Linear(64, 6));
    };
    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        return out->forward(x);
    };

    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, out{nullptr};
};

TORCH_MODULE(DQN);

class Bot {
    private:
        std::string m_gamemode;
        sf::RenderWindow *m_window;
        MyRect m_simulatedBall;
        bool *m_isDebugMode;
        bool *m_isSimulationDisplayed;

        DQN m_dqn = nullptr;

    public:
        Bot(std::string gamemode, sf::RenderWindow *window, bool *isDebugMode, bool *isSimulationDisplayed);
        ~Bot();

        void analyse(Ball ball, Player *himself, Player *opponent, float dt);
        void updateEasyBot(Ball ball, Player *himself, float dt);
        void updateMediumBot(Ball ball, Player *himself, Player *opponent, float dt);
        void updateHardBot(Ball ball, Player *himself, Player *opponent, float dt);

        std::array<float, 6> getState(Ball ball, Player* bot, Player* opponent);
        void updateAIBot(Ball ball, Player* himself, Player* opponent, float dt);

        float simulateBall(Ball ball, Player *himself, Player *opponent);
        float computeAttack(Ball ball, Player *himself, Player *opponent, float interceptY);
};
