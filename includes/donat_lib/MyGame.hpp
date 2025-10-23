#include "donat_lib/MyRect.hpp"
#include "donat_lib/MyText.hpp"
#include "donat_lib/Globals.hpp"
#include "Number.hpp"
#include "Ball.hpp"
#include "Bot.hpp"
#include <iostream>
#include <vector>

#pragma once

class MyGame {
    private:
        sf::Clock m_clock;
        float m_dt;
        MyRect m_topBar;
        MyRect m_bottomBar;
        Player m_leftBoard;
        Player m_rightBoard;
        Ball m_ball;
        std::vector<MyRect> m_line;
        int m_scoreLeft;
        int m_scoreRight;
        Number m_leftPlayer;
        Number m_rightPlayer;
        std::string m_gamemode;
        Bot m_bot;
        bool m_isDebugMode;

    public:
        MyGame(std::string gamemode, sf::RenderWindow *window);
        ~MyGame();

        void checkEvents();
        void update();
        void updateScore();
        void draw(sf::RenderWindow *window);
        void changeDebugMode();
};
