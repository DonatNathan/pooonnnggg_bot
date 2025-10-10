#include "donat_lib/MyRect.hpp"
#include "donat_lib/Globals.hpp"

#pragma once

class Ball {
    private:
        MyRect m_shape;
        float m_speed;
        sf::Vector2f m_velocity;
        sf::Vector2f m_startPosition;
        sf::Clock m_resetClock;
        bool m_waitingToReset = false;

    public:
        Ball();
        ~Ball();

        void draw(sf::RenderWindow *window);
        void update(float dt, MyRect *leftPaddle, MyRect *rightPaddle);
        void reset();

        void handleWallCollision();
        void handlePaddleCollision(MyRect *paddle);

        sf::Vector2f getPosition();
};