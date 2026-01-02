#pragma once
#include "card.h"

struct Round;

struct Game;

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

	bool isLeading;
	bool playedThisTurn = false;
};

Player initPlayer(const char* name);

void addCardToHand(Player& player, Card card);
void removeCardFromHand(Player& player, size_t index);
void printHand(const Player& player);
void playCard(Round& round, Player& player, int cardIndex);