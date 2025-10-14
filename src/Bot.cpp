#include "Bot.hpp"

Bot::Bot(std::string gamemode)
{
    m_gamemode = gamemode;
};

Bot::~Bot()
{

};

void Bot::analyse(Ball ball, Player *himself, Player *opponent, float dt)
{
    if (m_gamemode == "easy")
        updateEasyBot(ball, himself, dt);
    else if (m_gamemode == "medium")
        updateMediumBot(ball, himself, dt);
    else
        updateHardBot(ball, himself, opponent, dt);
};

void Bot::updateEasyBot(Ball ball, Player *himself, float dt)
{
    MyRect *ballShape = ball.getShape();
    MyRect *himselfShape = himself->getShape();

    float bY = ballShape->getPosition().y;
    float hY = himselfShape->getPosition().y;

    float bHeight = ballShape->getSize().y;
    float hHeight = himselfShape->getSize().y;

    if (bY + bHeight / 2 < hY + hHeight / 2) {
        sf::Vector2f direction = {0, - PADDLE_SPEED * dt};
        if (0 < (hY + direction.y))
            himselfShape->move(direction);
    } else if (bY + bHeight / 2 > hY + hHeight / 2) {
        sf::Vector2f direction = {0, PADDLE_SPEED * dt};
        if ((hY + direction.y) < WINDOW_HEIGH - PADDLE_HEIGHT)
            himselfShape->move(direction);
    }

    if (BORDER_VERTICAL_HEIGHT > hY)
        himselfShape->setPosition({himselfShape->getPosition().x, BORDER_VERTICAL_HEIGHT});

    if (hY > WINDOW_HEIGH - PADDLE_HEIGHT - BORDER_VERTICAL_HEIGHT)
        himselfShape->setPosition({himselfShape->getPosition().x, WINDOW_HEIGH - PADDLE_HEIGHT - BORDER_VERTICAL_HEIGHT});
};

void Bot::updateMediumBot(Ball ball, Player *himself, float dt)
{
    std::cout << "Medium analyse..." << std::endl;
};

void Bot::updateHardBot(Ball ball, Player *himself, Player *opponent, float dt)
{
    std::cout << "Hard analyse..." << std::endl;
};
