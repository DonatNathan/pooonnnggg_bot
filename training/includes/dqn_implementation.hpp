#pragma once

#include <torch/torch.h>
#include "constants.hpp"

struct DQNImpl : torch::nn::Module {
    DQNImpl();
    torch::Tensor forward(torch::Tensor x);

    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, out{nullptr};
};

TORCH_MODULE(DQN);
