#include "donat_lib/MyRect.hpp"
#include "donat_lib/Globals.hpp"

#include <chrono>
#include <thread>

#pragma once

class Ball {
    private:
        MyRect m_shape;
        float m_speed;
        sf::Vector2f m_velocity;
        sf::Vector2f m_startPosition;

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