#include "Ball.hpp"
#include "Player.hpp"
#include <algorithm>

#pragma once

class Bot {
    private:
        std::string m_gamemode;
        sf::RenderWindow *m_window;
        MyRect m_simulatedBall;
        bool *m_isDebugMode;
        bool *m_isSimulationDisplayed;

    public:
        Bot(std::string gamemode, sf::RenderWindow *window, bool *isDebugMode, bool *isSimulationDisplayed);
        ~Bot();

        void analyse(Ball ball, Player *himself, Player *opponent, float dt);
        void updateEasyBot(Ball ball, Player *himself, float dt);
        void updateMediumBot(Ball ball, Player *himself, Player *opponent, float dt);
        void updateHardBot(Ball ball, Player *himself, Player *opponent, float dt);

        float simulateBall(Ball ball, Player *himself, Player *opponent);
        float computeAttack(Ball ball, Player *himself, Player *opponent, float interceptY);
};
