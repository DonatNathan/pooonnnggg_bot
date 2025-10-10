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

void Ball::update(float dt, MyRect *leftPaddle, MyRect *rightPaddle)
{
    m_shape.move(m_velocity * m_speed * dt);
    handleWallCollision();
    handlePaddleCollision(leftPaddle);
    handlePaddleCollision(rightPaddle);
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

void Ball::handleWallCollision() {
    sf::Vector2f position = m_shape.getPosition();

    if (position.y < 10 || position.y + 10 > WINDOW_HEIGH - 10) {
        m_velocity.y = -m_velocity.y;
    }
};

void Ball::handlePaddleCollision(MyRect *paddle) {
    if (m_shape.getShape().getGlobalBounds().findIntersection(paddle->getShape().getGlobalBounds())) {
        m_velocity.x = -m_velocity.x;
        m_velocity.y += ((rand() % 100) / 100.f - 0.5f) * 0.5f;
    }
};
