#include "dqn_implementation.hpp"

DQNImpl::DQNImpl() {
    fc1 = register_module("fc1", torch::nn::Linear(STATE_DIM, 64));
    fc2 = register_module("fc2", torch::nn::Linear(64, 64));
    out = register_module("out", torch::nn::Linear(64, ACTION_DIM));
}

torch::Tensor DQNImpl::forward(torch::Tensor x) {
    x = torch::relu(fc1->forward(x));
    x = torch::relu(fc2->forward(x));
    return out->forward(x);
}
