/**
*  
* Solution to course project # 66
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Mladen Stankov
* @idnumber 3MI0600676
* @compiler Visual Studio
*
* <Main entry point of the application>
*
*/
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
            delete game.roundsHistory.history;
            std::cout << "Game ended. Thank you for playing!" << std::endl;
            return 0;
        }

        std::cout << "> ";
        std::cin.getline(command, MAX_COMMAND_LEN);

        cleanString(command);

        processCommand(command, game);
    }
}