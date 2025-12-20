#pragma once
#include "card.h"

// Constants
constexpr size_t MAX_HAND_SIZE = 6;

// Keeps track of the hand and points of the Player
struct Player
{
	Card hand[MAX_HAND_SIZE] = {};
	size_t cardCount = 0;
	int roundsPoints = 0;
	int gamePoints = 0;
};

void addCardToHand(Player& player, Card card);
void removeCardFromHand(Player& player, size_t index);
void printHand(const Player& player);