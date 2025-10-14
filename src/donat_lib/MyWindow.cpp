#include "donat_lib/MyWindow.hpp"

MyWindow::MyWindow(std::string name, sf::VideoMode mode, std::string gamemode)
    :
    m_game(gamemode)
{
    m_name = name;
    m_mode = mode;
    m_window.create(m_mode, m_name, sf::State::Fullscreen);
    m_window.setFramerateLimit(FRAMERATE_LIMIT);

    sf::View view(sf::FloatRect({0, 0}, {640, 480}));

    float scaleX = static_cast<float>(mode.size.x) / 640.f;
    float scaleY = static_cast<float>(mode.size.y) / 480.f;
    float scale = std::min(scaleX, scaleY);

    float viewportWidth = 640.f * scale / mode.size.x;
    float viewportHeight = 480.f * scale / mode.size.y;
    float viewportLeft = (1.f - viewportWidth) / 2.f;
    float viewportTop = (1.f - viewportHeight) / 2.f;

    view.setViewport(sf::FloatRect({viewportLeft, viewportTop}, {viewportWidth, viewportHeight}));

    m_window.setView(view);
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
        } else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->scancode == sf::Keyboard::Scancode::D)
                m_game.changeDebugMode();
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
