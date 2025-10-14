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
        updateMediumBot(ball, himself, opponent, dt);
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
        if (BORDER_VERTICAL_HEIGHT <= (hY + direction.y))
            himselfShape->move(direction);
        else
            himselfShape->move({direction.x, (hY - BORDER_VERTICAL_HEIGHT) * -1});
    } else if (bY + bHeight / 2 > hY + hHeight / 2) {
        sf::Vector2f direction = {0, PADDLE_SPEED * dt};
        if ((hY + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
            himselfShape->move(direction);
        else
            himselfShape->move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - hY});
    }
};

void Bot::updateMediumBot(Ball ball, Player *himself, Player *opponent, float dt)
{
    MyRect *himselfShape = himself->getShape();

    float hY = himselfShape->getPosition().y;
    float hHeight = himselfShape->getSize().y;

    float yTarget = simulateBall(ball, himself, opponent);

    if (yTarget < hY + hHeight / 2) {
        sf::Vector2f direction = {0, - PADDLE_SPEED * dt};
        if (BORDER_VERTICAL_HEIGHT <= (hY + direction.y))
            himselfShape->move(direction);
        else
            himselfShape->move({direction.x, (hY - BORDER_VERTICAL_HEIGHT) * -1});
    } else if (yTarget > hY + hHeight / 2) {
        sf::Vector2f direction = {0, PADDLE_SPEED * dt};
        if ((hY + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
            himselfShape->move(direction);
        else
            himselfShape->move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - hY});
    }
};

void Bot::updateHardBot(Ball ball, Player *himself, Player *opponent, float dt)
{
    std::cout << "Hard analyse..." << std::endl;
};

float Bot::simulateBall(Ball ball, Player *himself, Player *opponent)
{
    sf::Vector2f ballPosition = ball.getShape()->getPosition();
    sf::Vector2f ballVelocity = ball.getVelocity();
    
    const float dtSimulation = 0.01f;

    while ((ballVelocity.x > 0 && ballPosition.x + BALL_SIZE < opponent->getShape()->getPosition().x) || (ballVelocity.x < 0 && ballPosition.x > himself->getShape()->getPosition().x + PADDLE_WIDTH)) {
        ballPosition += ballVelocity * ball.getSpeed() * dtSimulation;
        if (ballPosition.y < BORDER_VERTICAL_HEIGHT || ballPosition.y + BALL_SIZE > WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
            ballVelocity.y = -ballVelocity.y;
    }

    return ballPosition.y + BALL_SIZE / 2;
};
