#pragma once
#include "game.h"


constexpr size_t MAX_COMMAND_LEN = 100;

// Returns false if the game is terminated
void processCommand(char* command, Game& game);

enum class Color
{
	Red = 4,
	White = 7,
	Gray = 8,
};
void setConsoleColor(Color color);