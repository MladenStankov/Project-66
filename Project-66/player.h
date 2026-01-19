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
* <Header file for Player struct and related functions>
*
*/
#pragma once
#include "card.h"

struct Round;

struct Game;

constexpr unsigned int MAX_HAND_SIZE = 6;

struct PlayerHand {
	Card hand[MAX_HAND_SIZE];
	unsigned int cardCount;
};

struct Player
{
	const char* name;
	PlayerHand hand;

	unsigned int currentPoints;
	unsigned int gamePoints;

	bool isLeading;
	bool playedThisTurn = false;
	bool hasMarriage = false;
	Suit marriageSuit;
};

Player initPlayer(const char* name);

void addCardToHand(Player& player, Card card, Suit* trump);
void removeCardFromHand(Player& player, unsigned int index);
void printHand(const Player& player);

// Returns false if the deck cards have ended and the round must end.
bool playCard(Game& game, Round& round, Player& player, int cardIndex);

// Sort all cards by power and suit. Separates red and black suits,
// places trump suit first, places cards with same suit in order of power, ascending.
void sortHand(Player& player, const Suit& trump);

bool findCardInHand(Player& player, const Suit& suit, const Rank& rank, unsigned int& index);