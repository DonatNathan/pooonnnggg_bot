#include "main.hpp"

int main(int argc, char **argv)
{
    std::cout << "Hay Cap'tain !" << std::endl;

    MyWindow window("Ping Pooonnnggg", sf::VideoMode({(unsigned int) WINDOW_WIDTH, (unsigned int) WINDOW_HEIGH}));
    window.Init();

    return 0;
}
