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
* <Header file for file operations>
*
*/
#pragma once
#include "game.h"

// Returns true if the game has been saved successfully
bool saveGame(const Game& game, const char* fileName);

// Returns true if the game has been loaded successfully
bool loadGame(Game& game, const char* fileName);