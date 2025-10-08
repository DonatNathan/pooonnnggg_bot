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
