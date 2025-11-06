#pragma once

#include <iostream>
#include <random>
#include <array>

#include "constants.hpp"
#include "pong_constants.hpp"

extern std::mt19937 rng;
extern std::uniform_real_distribution<float> uni01;

float randf();

struct State {
    std::array<float, STATE_DIM> v;
};

struct StepResult {
    State next;
    float reward;
    bool done;
};

class PongEnv {
    public:
        PongEnv();

        State reset();
        StepResult step(int action, float frame_dt=PHYS_DT);
        State getState();

    private:
        float left_paddle_y, right_paddle_y;
        float ball_x, ball_y;
        float ball_vx, ball_vy;
        float ball_speed;
        int steps;
        bool done;

        void clampPaddles();
        float left_paddle_x();
        float right_paddle_x();

        bool intersects(float bx, float by, float px, float py);
};
