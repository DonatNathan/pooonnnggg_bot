#include <SFML/Graphics.hpp>
#include <string>

#pragma once

class MyText {
    private:
        int m_fontSize;
        sf::Font m_font;
        sf::Text m_text;
        sf::Color m_color;
        std::string m_content;
        sf::Vector2f m_position;

    public:
        MyText(std::string content, sf::Vector2f position);
        MyText(std::string content, int fontSize, sf::Color color, sf::Vector2f position);
        ~MyText();

        void draw(sf::RenderWindow *window);

        std::string getContent();
        void setContent(std::string newContent);
};
