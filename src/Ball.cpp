#include "Ball.hpp"

Ball::Ball()
    :
    m_shape(sf::Vector2f({10, 10}), sf::Color::White, sf::Vector2f({(WINDOW_WIDTH - 10) / 2, (WINDOW_HEIGH - 10) / 2}))
{
    m_speed = BALL_SPEED;
    m_velocity = sf::Vector2f(
        (rand() % 2 == 0 ? -1.f : 1.f),
        (rand() % 2 == 0 ? -0.5f : 0.5f)
    );
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
    m_shape.move(m_velocity * m_speed * dt);
};

sf::Vector2f Ball::getPosition()
{
    return m_shape.getPosition();
};

void Ball::reset()
{
    m_shape.setPosition(m_startPosition);
    m_velocity = sf::Vector2f(
        (rand() % 2 == 0 ? -1.f : 1.f),
        (rand() % 2 == 0 ? -0.5f : 0.5f)
    );
};