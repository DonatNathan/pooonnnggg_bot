#include "donat_lib/MyRect.hpp"

class Player {
    private:
        MyRect m_shape;

    public:
        Player(sf::Vector2f size, sf::Color color, sf::Vector2f position);
        ~Player();
        
        void draw(sf::RenderWindow *window);
        void move(sf::Vector2f direction);

        MyRect *getShape();
};
