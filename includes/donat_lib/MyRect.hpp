#include <SFML/Graphics.hpp>

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
};
