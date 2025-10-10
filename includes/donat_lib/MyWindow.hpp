#include <SFML/Graphics.hpp>
#include "donat_lib/Globals.hpp"
#include "donat_lib/MyGame.hpp"

#pragma once

class MyWindow {
    private:
        std::string m_name;
        sf::RenderWindow m_window;
        sf::VideoMode m_mode;

        MyGame m_game;

    public:
        MyWindow(std::string name, sf::VideoMode mode);
        ~MyWindow();
        
        void Init();
        void CheckEvents();
        void Draw();
        void Update();
};
