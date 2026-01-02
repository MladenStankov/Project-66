#include <iostream>
#include <windows.h>
#include "console.h"
#include "game.h"
#include "utils.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand(time(nullptr));
    
    GameSettings gameSettings = initGameSettings();
    Game game = initGame(gameSettings);
    char command[MAX_COMMAND_LEN] = "";

    std::cout << "Welcome to Santase (66)!" << std::endl;
    std::cout << "Type 'start' to begin or 'help' for help." << std::endl;

    while (true)
    {
        if (game.status == GameStatus::ENDED)
        {
            std::cout << "Game ended. Thank you for playing!" << std::endl;
            return 0;
        }

        std::cout << "> ";
        std::cin >> command;

        cleanString(command);

        processCommand(command, game);
    }
}