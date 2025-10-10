#include "donat_lib/MyText.hpp"

MyText::MyText(std::string content, sf::Vector2f position)
    : 
    m_font("assets/fonts/arial.ttf"),
    m_text(m_font)
{
    m_content = content;
    m_fontSize = 32;
    m_position = position;
    m_color = sf::Color::White;

    m_text.setString(content);
    m_text.setFillColor(m_color);
    m_text.setPosition(m_position);
    m_text.setCharacterSize(m_fontSize);
};

MyText::MyText(std::string content, int fontSize, sf::Color color, sf::Vector2f position)
    : 
    m_font("../../assets/fonts/arial.ttf"),
    m_text(m_font)
{
    m_content = content;
    m_fontSize = fontSize;
    m_position = position;
    m_color = color;

    m_text.setString(content);
    m_text.setFillColor(m_color);
    m_text.setPosition(m_position);
    m_text.setCharacterSize(m_fontSize);
};

MyText::~MyText()
{

};

void MyText::draw(sf::RenderWindow *window)
{
    window->draw(m_text);
};

void MyText::setContent(std::string newContent)
{
    m_content = newContent;
    m_text.setString(m_content);
};

std::string MyText::getContent()
{
    return m_content;
};
