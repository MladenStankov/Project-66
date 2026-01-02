#pragma once
#include "card.h"
#include "player.h"
#include <iostream>

constexpr size_t MAX_DECK_SIZE = 24;

struct Game;

enum class RoundState {
	NOT_STARTED,
	ONGOING,
	ENDED,
};

struct Trick {
	Card leadPlayerCard, otherPlayerCard;
	Player* leadPlayer, * otherPlayer;
	Player* winner;
};

struct Deck {
	Card cards[MAX_DECK_SIZE] = {};
	size_t topCardIndex = 0;
};

struct RoundConclusion {
	Player* winner, * loser;
	unsigned int accumulatedPoints;
	unsigned int winnerPoints, loserPoints;
};

struct Round {
	Deck deck;
	Suit trump;
	Card bottomCard;
	Trick lastTrick;
	RoundState state = RoundState::ONGOING;
	RoundConclusion conclusion = {};
};

// Functions
void shuffleDeck(Deck& deck);

void startRound(Game& game);

void initialDeal(Round& round, Game& game);
void printLastTrick(const Round& round);
void printTrumpSuit(const Round& round);