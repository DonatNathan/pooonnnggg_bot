#include "Bot.hpp"

Bot::Bot(std::string gamemode)
{
    m_gamemode = gamemode;
};

Bot::~Bot()
{

};

void Bot::analyse(Ball ball, Player himself, Player opponent)
{
    if (m_gamemode == "easy")
        updateEasyBot(ball, himself);
    else if (m_gamemode == "medium")
        updateMediumBot(ball, himself);
    else
        updateHardBot(ball, himself, opponent);
};

void Bot::updateEasyBot(Ball ball, Player himself)
{
    std::cout << "Easy analyse..." << std::endl;
};

void Bot::updateMediumBot(Ball ball, Player himself)
{
    std::cout << "Medium analyse..." << std::endl;
};

void Bot::updateHardBot(Ball ball, Player himself, Player opponent)
{
    std::cout << "Hard analyse..." << std::endl;
};
