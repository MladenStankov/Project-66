#pragma once
#include "game.h"

// Returns true if the game has been saved successfully
bool saveGame(const Game& game, const char* fileName);

// Returns true if the game has been loaded successfully
bool loadGame(Game& game, const char* fileName);