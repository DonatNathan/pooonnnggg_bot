#include "Player.hpp"

Player::Player(sf::Vector2f size, sf::Color color, sf::Vector2f position)
    :
    m_shape(size, color, position)
{

};

Player::~Player()
{

};

void Player::move(sf::Vector2f direction)
{
    sf::Vector2f position = m_shape.getPosition();
    if (20 <= (position.y + direction.y) && (position.y + direction.y) <= WINDOW_HEIGH - 120) {
        m_shape.move(direction);
    }
};

void Player::draw(sf::RenderWindow *window)
{
    m_shape.draw(window);
};
