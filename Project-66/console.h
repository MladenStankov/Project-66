/**
*  
* Solution to course project # 66
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Mladen Stankov
* @idnumber 3MI0600676
* @compiler GCC
*
* <Header file for console commands>
*
*/
#pragma once
#include "game.h"


constexpr unsigned int MAX_COMMAND_LEN = 100;

// Returns false if the game is terminated
void processCommand(char* command, Game& game);

enum class Color
{
	Red = 4,
	White = 7,
	Gray = 8,
};
void setConsoleColor(Color color);