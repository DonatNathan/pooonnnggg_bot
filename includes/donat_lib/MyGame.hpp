#include "donat_lib/MyRect.hpp"
#include "donat_lib/MyText.hpp"
#include "donat_lib/Globals.hpp"

#pragma once

class MyGame {
    private:
        MyText m_scoreLeft;
        MyText m_scoreRight;
        MyRect m_topBar;
        MyRect m_bottomBar;
        MyRect m_leftBoard;
        MyRect m_rightBoard;
        MyRect m_ball;

    public:
        MyGame();
        ~MyGame();
        void draw(sf::RenderWindow *window);
};
