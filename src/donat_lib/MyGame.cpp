#include "donat_lib/MyGame.hpp"

MyGame::MyGame()
    :
    m_scoreLeft("0", sf::Vector2f({(WINDOW_WIDTH * (float) 0.25 - 32 / 2), 50})),
    m_scoreRight("0", sf::Vector2f({(WINDOW_WIDTH * (float) 0.75 - 32 / 2), 50})),
    m_topBar(sf::Vector2f({WINDOW_WIDTH, BORDER_VERTICAL_HEIGHT}), sf::Color::White, sf::Vector2f({0, 0})),
    m_bottomBar(sf::Vector2f({WINDOW_WIDTH, BORDER_VERTICAL_HEIGHT}), sf::Color::White, sf::Vector2f({0, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT})),
    m_leftBoard(sf::Vector2f({PADDLE_WIDTH, PADDLE_HEIGHT}), sf::Color::White, sf::Vector2f({BORDER_HORIZONTAL_WIDTH, (WINDOW_HEIGH - PADDLE_HEIGHT) / 2})),
    m_rightBoard(sf::Vector2f({PADDLE_WIDTH, PADDLE_HEIGHT}), sf::Color::White, sf::Vector2f({WINDOW_WIDTH - BORDER_HORIZONTAL_WIDTH - PADDLE_WIDTH, (WINDOW_HEIGH - PADDLE_HEIGHT) / 2}))
{
    float y = BORDER_VERTICAL_HEIGHT;
    while (y < WINDOW_HEIGH) {
        m_line.push_back(MyRect(sf::Vector2f({MIDDLE_LINE_POINT_SIZE, MIDDLE_LINE_POINT_SIZE}), sf::Color::White, sf::Vector2f({(WINDOW_WIDTH - MIDDLE_LINE_POINT_SIZE) / 2, y})));
        y += MIDDLE_LINE_POINT_SIZE + MIDDLE_LINE_POINT_GAB;
    }
};

MyGame::~MyGame()
{

};

void MyGame::checkEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        m_rightBoard.move({0, - PADDLE_SPEED * m_dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
        m_rightBoard.move({0, PADDLE_SPEED * m_dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        m_leftBoard.move({0, - PADDLE_SPEED * m_dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        m_leftBoard.move({0, PADDLE_SPEED * m_dt});
    }
};

void MyGame::update()
{
    m_dt = m_clock.restart().asSeconds();

    m_ball.update(m_dt, m_leftBoard.getShape(), m_rightBoard.getShape());
    updateScore();
};

void MyGame::updateScore()
{
    sf::Vector2f position = m_ball.getPosition();

    if (position.x < 0) {
        m_scoreRight.setContent(std::to_string(std::stoi(m_scoreLeft.getContent()) + 1));
        m_ball.reset();
    } else if (position.x + BALL_SIZE > WINDOW_WIDTH) {
        m_scoreLeft.setContent(std::to_string(std::stoi(m_scoreLeft.getContent()) + 1));
        m_ball.reset();
    }
};

void MyGame::draw(sf::RenderWindow *window)
{
    m_scoreLeft.draw(window);
    m_scoreRight.draw(window);
    m_topBar.draw(window);
    m_bottomBar.draw(window);
    m_leftBoard.draw(window);
    m_rightBoard.draw(window);
    m_ball.draw(window);
    for (auto&& value : m_line)
        value.draw(window);
};
