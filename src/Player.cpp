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

    if (BORDER_VERTICAL_HEIGHT <= (position.y + direction.y) && (position.y + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT) {
        m_shape.move(direction);
    } else if (BORDER_VERTICAL_HEIGHT < position.y && position.y + PADDLE_HEIGHT < WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT) {
        if (direction.y < 0) {
            m_shape.move({direction.x, (position.y - BORDER_VERTICAL_HEIGHT) * -1});
        } else {
            m_shape.move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - position.y});
        }
    }
};

void Player::draw(sf::RenderWindow *window)
{
    m_shape.draw(window);
};

MyRect *Player::getShape()
{
    return &m_shape;
};
