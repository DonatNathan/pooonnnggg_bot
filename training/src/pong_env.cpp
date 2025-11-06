#include "pong_env.hpp"

std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> uni01(0.0f, 1.0f);

float randf() {
    return uni01(rng);
};

PongEnv::PongEnv()
{
    reset();
};

State PongEnv::reset()
{
    // Place paddles near center, ball in middle with random direction
    left_paddle_y = WIN_H / 2.f - PADDLE_H / 2.f;
    right_paddle_y = WIN_H / 2.f - PADDLE_H / 2.f;

    ball_x = WIN_W / 2.f;
    ball_y = WIN_H / 2.f;
    // random horizontal dir
    ball_vx = (randf() < 0.5f) ? -1.f : 1.f;
    ball_vy = (randf() < 0.5f) ? -0.3f : 0.3f;
    ball_speed = BALL_INIT_SPEED;

    steps = 0;
    done = false;

    return getState();
};

StepResult PongEnv::step(int action, float frame_dt = PHYS_DT)
{
    // Apply action to right paddle
    float move = 0.f;
    if (action == 0) move = -PADDLE_SPEED * frame_dt;
    else if (action == 2) move = PADDLE_SPEED * frame_dt;
    right_paddle_y += move;
    clampPaddles();

    // Simple scripted opponent: follow ball center with limited speed
    float opp_center = left_paddle_y + PADDLE_H / 2.f;
    float tgt = ball_y;
    if (opp_center < tgt - 5.f) left_paddle_y += PADDLE_SPEED * frame_dt * 0.9f;
    else if (opp_center > tgt + 5.f) left_paddle_y -= PADDLE_SPEED * frame_dt * 0.9f;
    clampPaddles();

    // Move ball
    ball_x += ball_vx * ball_speed * frame_dt;
    ball_y += ball_vy * ball_speed * frame_dt;

    // Wall bounce
    if (ball_y - BALL_SIZE / 2.f < BORDER) {
        ball_y = BORDER + BALL_SIZE / 2.f;
        ball_vy = -ball_vy;
    } else if (ball_y + BALL_SIZE / 2.f > WIN_H - BORDER) {
        ball_y = WIN_H - BORDER - BALL_SIZE / 2.f;
        ball_vy = -ball_vy;
    }

    // Paddle collisions (left)
    if (ball_vx < 0 && intersects(ball_x, ball_y, left_paddle_x(), left_paddle_y)) {
        float paddle_center = left_paddle_y + PADDLE_H / 2.f;
        float impact = (ball_y - paddle_center) / (PADDLE_H / 2.f);
        float vy = impact * IMPACT_VERTICAL_SPEED;
        ball_vx = -ball_vx;
        ball_vy = vy / ball_speed;
        ball_speed = std::min(ball_speed + 20.f, BALL_MAX_SPEED);
    }

    // Paddle collisions (right)
    if (ball_vx > 0 && intersects(ball_x, ball_y, right_paddle_x(), right_paddle_y)) {
        float paddle_center = right_paddle_y + PADDLE_H / 2.f;
        float impact = (ball_y - paddle_center) / (PADDLE_H / 2.f);
        float vy = impact * IMPACT_VERTICAL_SPEED;
        ball_vx = -ball_vx;
        ball_vy = vy / ball_speed;
        ball_speed = std::min(ball_speed + 20.f, BALL_MAX_SPEED);
    }

    // scoring
    float reward = 0.f;
    if (ball_x < 0.f) {
        // right player scores
        reward = +1.0f;
        done = true;
    } else if (ball_x > WIN_W) {
        // left player scores
        reward = -1.0f;
        done = true;
    }

    steps++;
    if (steps >= MAX_STEPS_PER_EPISODE) { done = true; }

    StepResult r{getState(), reward, done};
    return r;
};

State PongEnv::getState()
{
    State s;
    // normalize positions to [0,1]
    s.v[0] = ball_x / float(WIN_W);
    s.v[1] = ball_y / float(WIN_H);
    s.v[2] = (ball_vx * ball_speed) / BALL_MAX_SPEED; // approx -1..1
    s.v[3] = (ball_vy * ball_speed) / BALL_MAX_SPEED;
    s.v[4] = right_paddle_y / float(WIN_H);
    s.v[5] = left_paddle_y / float(WIN_H);
    return s;
};

void PongEnv::clampPaddles()
{
    if (left_paddle_y < BORDER) left_paddle_y = BORDER;
    if (left_paddle_y + PADDLE_H > WIN_H - BORDER) left_paddle_y = WIN_H - BORDER - PADDLE_H;
    if (right_paddle_y < BORDER) right_paddle_y = BORDER;
    if (right_paddle_y + PADDLE_H > WIN_H - BORDER) right_paddle_y = WIN_H - BORDER - PADDLE_H;
};

float PongEnv::left_paddle_x() 
{
    return 30.f;
};

float PongEnv::right_paddle_x()
{
    return WIN_W - 30.f - PADDLE_W;
};

bool PongEnv::intersects(float bx, float by, float px, float py)
{
    float bl = bx - BALL_SIZE / 2.f, bt = by - BALL_SIZE / 2.f;
    float br = bx + BALL_SIZE / 2.f, bb = by + BALL_SIZE / 2.f;
    float pl = px, pt = py;
    float pr = px + PADDLE_W, pb = py + PADDLE_H;
    return !(br < pl || bl > pr || bb < pt || bt > pb);
};