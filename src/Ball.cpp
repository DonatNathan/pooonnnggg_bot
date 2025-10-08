#include "Ball.hpp"

Ball::Ball()
    :
    m_shape(sf::Vector2f({10, 10}), sf::Color::White, sf::Vector2f({(WINDOW_WIDTH - 10) / 2, (WINDOW_HEIGH - 10) / 2}))
{
    m_speed = BALL_SPEED;
    m_velocity = sf::Vector2f({0, 0});
    m_startPosition = sf::Vector2f({(WINDOW_WIDTH - 10) / 2, (WINDOW_HEIGH - 10) / 2});
};

Ball::~Ball()
{

};

void Ball::draw(sf::RenderWindow *window)
{
    m_shape.draw(window);
};

void Ball::update(float dt)
{

};
