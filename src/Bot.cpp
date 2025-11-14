#include "Bot.hpp"

Bot::Bot(std::string gamemode, sf::RenderWindow *window, bool *isDebugMode, bool *isSimulationDisplayed)
    :
    m_simulatedBall(sf::Vector2f({DEBUG_BALL_SIZE, DEBUG_BALL_SIZE}), sf::Color::Green, sf::Vector2f({100, 100}))
{
    m_gamemode = gamemode;
    m_window = window;
    m_isDebugMode = isDebugMode;
    m_isSimulationDisplayed = isSimulationDisplayed;

    if (m_gamemode == "ai") {

        m_dqn = DQN();

        try {
            torch::load(m_dqn, "../training/build/models/pong_dqn_best.pt");
            m_dqn->eval();
            std::cout << "Loaded DQN model.\n";
        }
        catch (...) {
            std::cerr << "Model load failed.\n";
        }
    }
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
    else if (m_gamemode == "hard")
        updateHardBot(ball, himself, opponent, dt);
    else
        updateAIBot(ball, himself, opponent, dt);
};

void Bot::updateEasyBot(Ball ball, Player *himself, float dt)
{
    MyRect *ballShape = ball.getShape();
    MyRect *himselfShape = himself->getShape();

    float bY = ballShape->getPosition().y;
    float hY = himselfShape->getPosition().y;

    float bHeight = ballShape->getSize().y;
    float hHeight = himselfShape->getSize().y;

    float ballCenter = bY + bHeight / 2;
    float paddleCenter = hY + hHeight / 2;

    if (std::abs(ballCenter - paddleCenter) > PADDLE_SPEED * dt) {
        if (ballCenter < paddleCenter) {
            sf::Vector2f direction = {0, - PADDLE_SPEED * dt};
            if (BORDER_VERTICAL_HEIGHT <= (hY + direction.y))
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, (hY - BORDER_VERTICAL_HEIGHT) * -1});
        } else if (ballCenter > paddleCenter) {
            sf::Vector2f direction = {0, PADDLE_SPEED * dt};
            if ((hY + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - hY});
        }
    }
};

void Bot::updateMediumBot(Ball ball, Player *himself, Player *opponent, float dt)
{
    MyRect *himselfShape = himself->getShape();

    float hY = himselfShape->getPosition().y;
    float hHeight = himselfShape->getSize().y;
    float paddleCenter = hY + hHeight / 2;

    float yTarget = simulateBall(ball, himself, opponent);

    if (std::abs(yTarget - paddleCenter) > PADDLE_SPEED * dt) {
        if (yTarget < paddleCenter) {
            sf::Vector2f direction = {0, - PADDLE_SPEED * dt};
            if (BORDER_VERTICAL_HEIGHT <= (hY + direction.y))
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, (hY - BORDER_VERTICAL_HEIGHT) * -1});
        } else if (yTarget > paddleCenter) {
            sf::Vector2f direction = {0, PADDLE_SPEED * dt};
            if ((hY + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - hY});
        }
    }
};

void Bot::updateHardBot(Ball ball, Player *himself, Player *opponent, float dt)
{
    MyRect *himselfShape = himself->getShape();

    float hY = himselfShape->getPosition().y;
    float hHeight = himselfShape->getSize().y;
    float paddleCenter = hY + hHeight / 2;

    float interceptY = simulateBall(ball, himself, opponent);
    float yTarget = computeAttack(ball, himself, opponent, interceptY);

    if (std::abs(yTarget - paddleCenter) > PADDLE_SPEED * dt) {
        if (yTarget < paddleCenter) {
            sf::Vector2f direction = {0, - PADDLE_SPEED * dt};
            if (BORDER_VERTICAL_HEIGHT <= (hY + direction.y))
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, (hY - BORDER_VERTICAL_HEIGHT) * -1});
        } else if (yTarget > paddleCenter) {
            sf::Vector2f direction = {0, PADDLE_SPEED * dt};
            if ((hY + PADDLE_HEIGHT + direction.y) <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
                himselfShape->move(direction);
            else
                himselfShape->move({direction.x, WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT - hY});
        }
    }
};

std::array<float, 6> Bot::getState(Ball ball, Player* bot, Player* opponent)
{
    auto bPos = ball.getShape()->getPosition();
    auto bVel = ball.getVelocity();
    auto pPos = bot->getShape()->getPosition();
    auto oPos = opponent->getShape()->getPosition();

    return {
        bPos.x / WINDOW_WIDTH,
        bPos.y / WINDOW_HEIGH,
        bVel.x / BALL_MAX_SPEED,
        bVel.y / BALL_MAX_SPEED,
        pPos.y / WINDOW_HEIGH,
        oPos.y / WINDOW_HEIGH
    };
}

void Bot::updateAIBot(Ball ball, Player* himself, Player* opponent, float dt)
{
    // --- 1. Build the state vector ---
    auto state = getState(ball, himself, opponent);

    // --- 2. Run the model ---

    torch::Tensor input = torch::from_blob((float*)state.data(), {1, 6}).clone();

    torch::Tensor qvalues = m_dqn->forward(input);
    int action = qvalues.argmax(1).item<int>();

    // --- 3. Move the paddle according to the chosen action ---
    MyRect* paddle = himself->getShape();
    float y = paddle->getPosition().y;

    if (action == 0) {
        // STAY STILL
        return;
    }
    else if (action == 1) {
        // MOVE UP
        sf::Vector2f dir(0, -PADDLE_SPEED * dt);
        if (y + dir.y >= BORDER_VERTICAL_HEIGHT)
            paddle->move(dir);
        else
            paddle->move({0, BORDER_VERTICAL_HEIGHT - y});
    }
    else if (action == 2) {
        // MOVE DOWN
        sf::Vector2f dir(0, PADDLE_SPEED * dt);
        if (y + PADDLE_HEIGHT + dir.y <= WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
            paddle->move(dir);
        else
            paddle->move({0, (WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT - PADDLE_HEIGHT) - y});
    }
}

float Bot::simulateBall(Ball ball, Player *himself, Player *opponent)
{
    sf::Vector2f ballPosition = ball.getShape()->getPosition();
    sf::Vector2f ballVelocity = ball.getVelocity();
    
    const float dtSimulation = 0.01f;

    sf::FloatRect rectOpponent = opponent->getShape()->getShape().getGlobalBounds();

    std::vector<sf::Vector2f> simulatedPositions;

    while ((ballVelocity.x > 0 && ballPosition.x + BALL_SIZE <= opponent->getShape()->getPosition().x) || (ballVelocity.x < 0 && ballPosition.x >= himself->getShape()->getPosition().x + PADDLE_WIDTH)) {

        ballPosition += ballVelocity * ball.getSpeed() * dtSimulation;

        simulatedPositions.push_back(ballPosition);

        if (ballPosition.y < BORDER_VERTICAL_HEIGHT || ballPosition.y + BALL_SIZE > WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT)
            ballVelocity.y = -ballVelocity.y;

        sf::FloatRect ballRect({ballPosition.x, ballPosition.y}, {BALL_SIZE, BALL_SIZE});

        if (ballRect.findIntersection(rectOpponent) && ballVelocity.x > 0) {
            float paddleCenter = rectOpponent.position.y + PADDLE_HEIGHT / 2;
            float impact = (ballPosition.y + BALL_SIZE / 2 - paddleCenter) / (PADDLE_HEIGHT / 2);
            float verticalSpeed = impact * IMPACT_VERTICAL_SPEED;

            ballVelocity.x = -ballVelocity.x;
            ballVelocity.y = verticalSpeed / ball.getSpeed();
        }
    }

    if (*m_isSimulationDisplayed) {

        if (*m_isDebugMode)
            m_simulatedBall.setColor(sf::Color::Green);
        else
            m_simulatedBall.setColor(sf::Color::White);

        for (auto&& point : simulatedPositions) {
            m_simulatedBall.setPosition({point.x + (BALL_SIZE - DEBUG_BALL_SIZE) / 2, point.y + (BALL_SIZE - DEBUG_BALL_SIZE) / 2});
            m_simulatedBall.draw(m_window);
        }
    }

    return ballPosition.y + BALL_SIZE / 2;
};

float Bot::computeAttack(Ball ball, Player *himself, Player *opponent, float interceptY)
{
    float botX = himself->getShape()->getPosition().x;
    float oppX = opponent->getShape()->getPosition().x;

    float oppCenter = opponent->getShape()->getPosition().y + PADDLE_HEIGHT / 2;
    float targetY = (oppCenter < WINDOW_HEIGH / 2.f) ? WINDOW_HEIGH - BORDER_VERTICAL_HEIGHT : BORDER_VERTICAL_HEIGHT;

    float deltaX = std::abs(oppX - botX);
    float deltaY = targetY - interceptY;
    float desiredSlope = deltaY / deltaX;

    float vX = std::abs(ball.getSpeed());
    float vY = desiredSlope * vX;
    float requiredImpact = std::clamp(vY / IMPACT_VERTICAL_SPEED, -1.f, 1.f);

    return interceptY + (PADDLE_HEIGHT / 2.f) * requiredImpact;
};
