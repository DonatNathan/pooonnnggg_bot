#include "Number.hpp"

Number::Number(char originalNumber, sf::Vector2f globalPosition)
{
    m_originalNumber = originalNumber;
    m_globalPosition = globalPosition;
    createNumber();
};

Number::~Number()
{

};

void Number::changeNumber(char newNumber)
{
    m_originalNumber = newNumber;
    createNumber();
};

void Number::createNumber()
{
    std::array<int, 15> code = getCodeNumber(m_originalNumber);
    for (int i = 0; i != code.size(); i++) {
        m_number.push_back(MyRect({SCORE_SIZE, SCORE_SIZE}, code[i] == 1 ? sf::Color::White : sf::Color::Black, {m_globalPosition.x + i % 3 * SCORE_SIZE, m_globalPosition.y + i / 3 * SCORE_SIZE}));
    }
};

std::array<int, 15> Number::getCodeNumber(char number)
{
    switch (number)
    {
    case '0':
        return {
            1, 1, 1,
            1, 0, 1,
            1, 0, 1,
            1, 0, 1,
            1, 1, 1
        };
    case '1':
        return {
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
        };
    case '2':
        return {
            1, 1, 1,
            0, 0, 1,
            1, 1, 1,
            1, 0, 0,
            1, 1, 1
        };
    case '3':
        return {
            1, 1, 1,
            0, 0, 1,
            1, 1, 1,
            0, 0, 1,
            1, 1, 1
        };
    case '4':
        return {
            1, 0, 1,
            1, 0, 1,
            1, 1, 1,
            0, 0, 1,
            0, 0, 1
        };
    case '5':
        return {
            1, 1, 1,
            1, 0, 0,
            1, 1, 1,
            0, 0, 1,
            1, 1, 1
        };
    case '6':
        return {
            1, 1, 1,
            1, 0, 0,
            1, 1, 1,
            1, 0, 1,
            1, 1, 1
        };
    case '7':
        return {
            1, 1, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
        };
    case '8':
        return {
            1, 1, 1,
            1, 0, 1,
            1, 1, 1,
            1, 0, 1,
            1, 1, 1
        };
    case '9':
        return {
            1, 1, 1,
            1, 0, 1,
            1, 1, 1,
            0, 0, 1,
            1, 1, 1
        };
    default:
        return {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1,
            1, 1, 1,
            1, 1, 1
        };
    }
};

void Number::drawNumber(sf::RenderWindow *window)
{
    for (auto&& rect : m_number)
        rect.draw(window);
};
