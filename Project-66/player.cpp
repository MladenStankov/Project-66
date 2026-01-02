#include "player.h"
#include "card.h"
#include <iostream>

Player initPlayer(const char* name)
{
	PlayerHand newPlayerHand = { {}, 0 };
	Player newPlayer = {name, newPlayerHand, 0, 0, false };

	return newPlayer;
}

void addCardToHand(Player& player, Card card)
{
	if (player.hand.cardCount < 6)
	{
		player.hand.hand[player.hand.cardCount++] = card;
	}
}

void printHand(const Player& player)
{
	std::cout << "{ ";
	for (int i = 0; i < player.hand.cardCount; i++)
	{
		printCard(player.hand.hand[i]);
		if(i != player.hand.cardCount - 1)
			std::cout << " , ";
	}
	std::cout << " }";
}