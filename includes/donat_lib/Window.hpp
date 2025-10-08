#include <SFML/Graphics.hpp>

#pragma once

class Window {
    private:
        std::string m_name;
        sf::RenderWindow m_window;
        sf::VideoMode m_mode;

    public:
        Window();
        Window(std::string name, sf::VideoMode mode);
        ~Window();
        void Init();
        void CheckEvents();
        void Draw();
        void Update();
};