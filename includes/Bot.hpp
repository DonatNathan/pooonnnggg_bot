#include "Ball.hpp"
#include "Player.hpp"

#pragma once

class Bot {
    private:
        std::string m_gamemode;

    public:
        Bot(std::string gamemode);
        ~Bot();

        void analyse(Ball ball, Player himself, Player opponent);
        void updateEasyBot(Ball ball, Player himself);
        void updateMediumBot(Ball ball, Player himself);
        void updateHardBot(Ball ball, Player himself, Player opponent);
};
