#include <SFML/Graphics.hpp>
#include "donat_lib/Globals.hpp"
#include <iostream>

#pragma once

class MyRect {
    private:
        sf::RectangleShape m_rect;
        sf::Vector2f m_size;
        sf::Color m_color;
        sf::Vector2f m_position;

    public:
        MyRect(sf::Vector2f size, sf::Color color, sf::Vector2f position);
        ~MyRect();
        
        void draw(sf::RenderWindow *window);
        void move(sf::Vector2f direction);

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f newPosition);
};
