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
	bool hasMarriage = false;
	Suit marriageSuit;
};

Player initPlayer(const char* name);

void addCardToHand(Player& player, Card card, Suit* trump);
void removeCardFromHand(Player& player, size_t index);
void printHand(const Player& player);

// Returns false if the deck cards have ended and the round must end.
bool playCard(Round& round, Player& player, int cardIndex);

// Sort all cards by power and suit. Separates red and black suits,
// places trump suit first, places cards with same suit in order of power, ascending.
void sortHand(Player& player, const Suit& trump);

bool findCardInHand(Player& player, const Suit& suit, const Rank& rank, size_t& index);