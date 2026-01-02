#pragma once
#include "card.h"

constexpr size_t MAX_HAND_SIZE = 6;

struct PlayerHand {
	Card hand[MAX_HAND_SIZE];
	size_t cardCount;
};

struct Player
{
	const char* name;
	PlayerHand hand;
	unsigned int currentRoundPoints;
	unsigned int overallPoints;
};

Player initPlayer(const char* name);

void addCardToHand(Player& player, Card card);
void removeCardFromHand(Player& player, size_t index);
void printHand(const Player& player);