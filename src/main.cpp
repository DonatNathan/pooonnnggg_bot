#include "main.hpp"

void displayHelp()
{
    std::cout << "======= HELP =======\n" << std::endl;
    std::cout << "Executable:" << std::endl;
    std::cout << "  ./PongBot -m [mode]" << std::endl;
    std::cout << "Flags:" << std::endl;
    std::cout << "  -m, --mode: Choose the mode of the game between 'multiplayer', 'easy', 'medium', 'hard' and 'ai'" << std::endl;
    std::cout << "\n===== END HELP =====" << std::endl;
}

int argumentsErrorHandling(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Invalid number of arguments, 2 argument needed" << std::endl;
        return 1;
    }

    std::array<std::string, 5> modeList = {"multiplayer", "easy", "medium", "hard", "ai"};
    std::string flag = argv[1];
    std::string mode = argv[2];
    bool modeFound = false;

    if (flag != "-m") {
        std::cout << "Invalid flag: " << flag << ", did you mean '-m'?" << std::endl;
        return 1;
    }

    for (int i = 0; i < modeList.size(); i++) {
        if (modeList[i] == mode)
            modeFound = true;
    }

    if (!modeFound) {
        std::cout << "Invalid mode: " << argv[2] << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argumentsErrorHandling(argc, argv) == 1) {
        displayHelp();
        return 1;
    }

    MyWindow window("Ping Pooonnnggg", sf::VideoMode::getDesktopMode(), argv[2]);

    window.Init();

    return 0;
}

// TODO: Fix ball colliders
