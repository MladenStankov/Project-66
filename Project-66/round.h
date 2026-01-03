#pragma once
#include "card.h"
#include "player.h"
#include <iostream>

constexpr size_t MAX_DECK_SIZE = 24;

struct Game;

enum class RoundState {
	NOT_STARTED,
	STARTED,
	IN_MIDDLE,
	CLOSED,
	ENDED,
};

struct Trick {
	Card leadPlayerCard, nonLeadCard;
	Player* leadPlayer = nullptr, *nonLeadPlayer = nullptr;
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
	Trick lastTrick, currentTrick;
	RoundState state = RoundState::STARTED;
	RoundConclusion conclusion = {};
};

// Functions
void shuffleDeck(Deck& deck);

Round& startRound(Game& game);

void initialDeal(Round& round, Game& game);
void printLastTrick(const Round& round);
void printRoundInfo(const Round& round);
void changeRoundState(Round& round, RoundState state);
bool switchNine(Round& round, Player& player);
bool announceMarriage(Round& round, Player& player, Suit suit);
