#include "donat_lib/MyWindow.hpp"

MyWindow::MyWindow(std::string name, sf::VideoMode mode)
{
    m_name = name;
    m_mode = mode;
    m_window.create(m_mode, m_name, sf::State::Fullscreen);
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
};

MyWindow::~MyWindow()
{

};

void MyWindow::Init()
{
    while (m_window.isOpen()) {
        CheckEvents();
        Update();
        Draw();
    }
};

void MyWindow::CheckEvents()
{
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                m_window.close();
        }
    }
    m_game.checkEvents();
};

void MyWindow::Update()
{
    m_game.update();
};

void MyWindow::Draw()
{
    m_window.clear(sf::Color::Black);
    m_game.draw(&m_window);
    m_window.display();
};
