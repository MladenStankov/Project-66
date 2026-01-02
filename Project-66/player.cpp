#include "player.h"
#include "card.h"
#include <iostream>

Player initPlayer(const char* name)
{
	PlayerHand newPlayerHand = { {}, 0 };
	Player newPlayer = {name, newPlayerHand, 0, 0 };

	return newPlayer;
}