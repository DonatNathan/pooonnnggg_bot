#pragma once

#include <vector>
#include <random>

#include "constants.hpp"
#include "pong_env.hpp"

struct Transition {
    std::array<float, STATE_DIM> s;
    int a;
    float r;
    std::array<float, STATE_DIM> s2;
    bool done;
};

class ReplayBuffer {
    public:
        ReplayBuffer(size_t capacity=REPLAY_CAPACITY);

        void push(const Transition &t);
        std::vector<Transition> sample(size_t n);
        size_t size();
    private:
        std::vector<Transition> buf;
        size_t capacity;
        size_t pos = 0;
};
