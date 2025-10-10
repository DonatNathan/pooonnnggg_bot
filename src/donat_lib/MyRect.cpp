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
    m_rect.move(direction);
    m_position = m_rect.getPosition();
};

sf::Vector2f MyRect::getPosition()
{
    return m_position;
};

void MyRect::setPosition(sf::Vector2f newPosition)
{
    m_rect.setPosition(newPosition);
};

sf::RectangleShape MyRect::getShape()
{
    return m_rect;
};
