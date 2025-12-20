#include "player.h"
#include "card.h"
#include <iostream>

void addCardToHand(Player& player, Card card)
{
	if (player.cardCount < MAX_HAND_SIZE)
	{
		player.hand[player.cardCount++] = card;
	}
}

void removeCardFromHand(Player& player, size_t index)
{
	if (index >= player.cardCount) return;

	for (size_t i = index; i < MAX_HAND_SIZE - 1; ++i)
	{
		player.hand[i] = player.hand[i + 1];
	}
	player.cardCount--; 
}

void printHand(const Player& player)
{
	std::cout << "Hand: ";
	for (size_t i = 0; i < player.cardCount; ++i)
	{
		printCard(player.hand[i]);
	}
	std::cout << std::endl;
}