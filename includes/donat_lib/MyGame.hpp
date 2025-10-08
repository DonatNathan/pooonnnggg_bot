#include "donat_lib/MyRect.hpp"
#include "donat_lib/MyText.hpp"
#include "donat_lib/Globals.hpp"
#include "Ball.hpp"
#include <iostream>

#pragma once

class MyGame {
    private:
        sf::Clock m_clock;
        float m_dt;
        MyText m_scoreLeft;
        MyText m_scoreRight;
        MyRect m_topBar;
        MyRect m_bottomBar;
        MyRect m_leftBoard;
        MyRect m_rightBoard;
        Ball m_ball; 
    public:
        MyGame();
        ~MyGame();
        void checkEvents();
        void update();
        void draw(sf::RenderWindow *window);
};
