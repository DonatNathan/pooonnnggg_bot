#include "donat_lib/MyGame.hpp"

MyGame::MyGame(std::string gamemode)
    :
    m_topBar(sf::Vector2f({WINDOW_WIDTH, BORDER_VERTICAL_HEIGHT}), sf::Color::White, sf::Vector2f({0, 0})),
    m_bottomBar(sf::Vector2f({WINDOW_WIDTH, BORDER_VERTICAL_HEIGHT}), sf::Color::White, sf::Vector2f({0, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT})),
    m_leftBoard(sf::Vector2f({PADDLE_WIDTH, PADDLE_HEIGHT}), sf::Color::White, sf::Vector2f({BORDER_HORIZONTAL_WIDTH, (WINDOW_HEIGH - PADDLE_HEIGHT) / 2})),
    m_rightBoard(sf::Vector2f({PADDLE_WIDTH, PADDLE_HEIGHT}), sf::Color::White, sf::Vector2f({WINDOW_WIDTH - BORDER_HORIZONTAL_WIDTH - PADDLE_WIDTH, (WINDOW_HEIGH - PADDLE_HEIGHT) / 2})),
    m_leftPlayer('0', sf::Vector2f({(WINDOW_WIDTH * (float) 0.25 - 32 / 2), 50})),
    m_rightPlayer('0', sf::Vector2f({(WINDOW_WIDTH * (float) 0.75 - 32 / 2), 50})),
    m_bot(gamemode)
{
    m_scoreLeft = 0;
    m_scoreRight = 0;
    m_gamemode = gamemode;
    float y = BORDER_VERTICAL_HEIGHT;
    m_isDebugMode = false;
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
    if (m_gamemode == "multiplayer") {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
            m_leftBoard.move({0, - PADDLE_SPEED * m_dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            m_leftBoard.move({0, PADDLE_SPEED * m_dt});
        }
    }
};

void MyGame::update()
{
    m_dt = m_clock.restart().asSeconds();

    m_bot.analyse(m_ball, &m_leftBoard, &m_rightBoard, m_dt);
    m_ball.update(m_dt, m_leftBoard.getShape(), m_rightBoard.getShape());
    updateScore();
};

void MyGame::updateScore()
{
    sf::Vector2f position = m_ball.getShape()->getPosition();

    if (position.x < 0) {
        m_scoreRight++;
        m_rightPlayer.changeNumber(m_scoreRight + 48);
        m_ball.reset();
    } else if (position.x + BALL_SIZE > WINDOW_WIDTH) {
        m_scoreLeft++;
        m_leftPlayer.changeNumber(m_scoreLeft + 48);
        m_ball.reset();
    }
};

void MyGame::draw(sf::RenderWindow *window)
{
    m_topBar.draw(window);
    m_bottomBar.draw(window);
    m_leftBoard.draw(window);
    m_rightBoard.draw(window);
    m_ball.draw(window);
    for (auto&& value : m_line)
        value.draw(window);
    m_leftPlayer.drawNumber(window);
    m_rightPlayer.drawNumber(window);
};

void MyGame::changeDebugMode()
{
    m_isDebugMode = !m_isDebugMode;

    if (m_isDebugMode) {
        m_leftBoard.getShape()->setColor(sf::Color::Blue);
        m_rightBoard.getShape()->setColor(sf::Color::Blue);
        m_ball.getShape()->setColor(sf::Color::Red);
    } else {
        m_leftBoard.getShape()->setColor(sf::Color::White);
        m_rightBoard.getShape()->setColor(sf::Color::White);
        m_ball.getShape()->setColor(sf::Color::White);
    }
};
