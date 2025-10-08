#include "donat_lib/MyGame.hpp"

MyGame::MyGame()
    :
    m_scoreLeft("0", sf::Vector2f({(WINDOW_WIDTH * (float) 0.25 - 32 / 2), 50})),
    m_scoreRight("0", sf::Vector2f({(WINDOW_WIDTH * (float) 0.75 - 32 / 2), 50})),
    m_topBar(sf::Vector2f({WINDOW_WIDTH, 10}), sf::Color::White, sf::Vector2f({0, 0})),
    m_bottomBar(sf::Vector2f({WINDOW_WIDTH, 10}), sf::Color::White, sf::Vector2f({0, WINDOW_HEIGH - 10})),
    m_leftBoard(sf::Vector2f({10, 100}), sf::Color::White, sf::Vector2f({10, (WINDOW_HEIGH - 100) / 2})),
    m_rightBoard(sf::Vector2f({10, 100}), sf::Color::White, sf::Vector2f({WINDOW_WIDTH - 20, (WINDOW_HEIGH - 100) / 2})),
    m_ball(sf::Vector2f({10, 10}), sf::Color::White, sf::Vector2f({(WINDOW_WIDTH - 10) / 2, (WINDOW_HEIGH - 10) / 2}))
{

};

MyGame::~MyGame()
{

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
};
