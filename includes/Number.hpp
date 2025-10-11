#include "donat_lib/MyRect.hpp"
#include <vector>
#include <array>

class Number
{
    private:
        char m_originalNumber;
        std::vector<MyRect> m_number;
        sf::Vector2f m_globalPosition;

    public:
        Number(char originalNumber, sf::Vector2f globalPosition);
        ~Number();

        void changeNumber(char newNumber);
        void createNumber();
        std::array<int, 15> getCodeNumber(char newNumber);
        void drawNumber(sf::RenderWindow *window);
};