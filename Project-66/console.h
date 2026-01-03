#pragma once
#include "game.h"


constexpr size_t MAX_COMMAND_LEN = 100;

// Shows all avaiable commands and information about them
void showHelp();

// Shows the general rules and the confirmed settings by the User.
void showRules(const GameSettings& gameSettings);

// Returns false if the game is terminated
void processCommand(char* command, Game& game);


enum class Color
{
	Red = 4,
	White = 7,
	Gray = 8,
};
void setConsoleColor(Color color);