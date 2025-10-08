#include "donat_lib/MyRect.hpp"

MyRect::MyRect(sf::Vector2f size, sf::Color color, sf::Vector2f position)
{
    m_size = size;
    m_color = color;
    m_position = position;

    m_rect.setSize(m_size);
    m_rect.setFillColor(m_color);
    m_rect.setPosition(m_position);
};

MyRect::~MyRect()
{

};

void MyRect::draw(sf::RenderWindow *window)
{
    window->draw(m_rect);
};

void MyRect::move(sf::Vector2f direction)
{
    if (20 <= (m_position.y + direction.y) && (m_position.y + direction.y) <= WINDOW_HEIGH - 120) {
        m_rect.move(direction);
        m_position.x += direction.x;
        m_position.y += direction.y;
    }
};
