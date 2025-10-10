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
    if (0 < (position.y + direction.y) && (position.y + direction.y) < WINDOW_HEIGH - PADDLE_HEIGHT) { // If there is a problem, change that
        m_shape.move(direction);
    }

    if (BORDER_VERTICAL_HEIGHT > position.y)
        m_shape.setPosition({m_shape.getPosition().x, BORDER_VERTICAL_HEIGHT});

    if (position.y > WINDOW_HEIGH - PADDLE_HEIGHT - BORDER_VERTICAL_HEIGHT)
        m_shape.setPosition({m_shape.getPosition().x, WINDOW_HEIGH - PADDLE_HEIGHT - BORDER_VERTICAL_HEIGHT});
};

void Player::draw(sf::RenderWindow *window)
{
    m_shape.draw(window);
};


MyRect *Player::getShape()
{
    return &m_shape;
};

