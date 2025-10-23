#include "Ball.hpp"

Ball::Ball()
    :
    m_shape(sf::Vector2f({BALL_SIZE, BALL_SIZE}), sf::Color::White, sf::Vector2f({(WINDOW_WIDTH - BALL_SIZE) / 2, (WINDOW_HEIGH - BALL_SIZE) / 2}))
{
    m_speed = BALL_SPEED;
    m_velocity = sf::Vector2f(
        (rand() % 2 == 0 ? -1.f : 1.f),
        (rand() % 2 == 0 ? -0.5f : 0.5f)
    );
    m_startPosition = sf::Vector2f({(WINDOW_WIDTH - BALL_SIZE) / 2, (WINDOW_HEIGH - BALL_SIZE) / 2});
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
    if (m_waitingToReset) {
        if (m_resetClock.getElapsedTime().asSeconds() >= 1.f) {
            m_speed = BALL_SPEED;
            m_waitingToReset = false;
        }
    } else {
        m_shape.move(m_velocity * m_speed * dt);
        handleWallCollision();
        handlePaddleCollision(leftPaddle);
        handlePaddleCollision(rightPaddle);
    }
};

void Ball::reset()
{
    m_speed = BALL_SPEED;
    m_shape.setPosition(m_startPosition);
    m_resetClock.restart();
    m_waitingToReset = true;
};

void Ball::handleWallCollision() {
    sf::Vector2f position = m_shape.getPosition();

    if (position.y < BORDER_VERTICAL_HEIGHT || position.y + BALL_SIZE > WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT) {
        m_velocity.y = -m_velocity.y;
    }
};

void Ball::handlePaddleCollision(MyRect *paddle) {
    if (m_shape.getShape().getGlobalBounds().findIntersection(paddle->getShape().getGlobalBounds())) {
        float paddleCenter = paddle->getPosition().y + PADDLE_HEIGHT / 2;
        float impact = (m_shape.getPosition().y + BALL_SIZE / 2 - paddleCenter) / (PADDLE_HEIGHT / 2.f);
        float verticalSpeed = impact * IMPACT_VERTICAL_SPEED;
        m_velocity.x = -m_velocity.x;
        m_velocity.y = verticalSpeed / m_speed;
        if (m_speed < BALL_MAX_SPEED)
            m_speed += 50;
    }
};

MyRect *Ball::getShape()
{
    return &m_shape;
};

float Ball::getSpeed()
{
    return m_speed;
};

sf::Vector2f Ball::getVelocity()
{
    return m_velocity;
};
