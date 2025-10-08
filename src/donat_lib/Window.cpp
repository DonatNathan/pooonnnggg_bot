#include "donat_lib/Window.hpp"

Window::Window()
{
    m_name = "New Graphical Project";
    m_mode = sf::VideoMode({500, 500});
    m_window.create(m_mode, m_name);
    m_window.setFramerateLimit(144);
};

Window::Window(std::string name, sf::VideoMode mode)
{
    m_name = name;
    m_mode = mode;
    m_window.create(m_mode, m_name);
    m_window.setFramerateLimit(144);
};

Window::~Window()
{

};

void Window::Init()
{
    while (m_window.isOpen()) {
        CheckEvents();
        Update();
        Draw();
    }
};

void Window::CheckEvents()
{
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
};

void Window::Update()
{

};

void Window::Draw()
{
    m_window.clear(sf::Color::Black);
    m_window.display();
};
