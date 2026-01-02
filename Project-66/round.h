#pragma once
#include "card.h"
#include "player.h"
#include <iostream>

constexpr size_t MAX_DECK_SIZE = 24;
constexpr size_t MAX_TRICKS = 12;

enum class RoundState {
	ONGOING,
	ENDED,
};

struct Trick {
	Card leadPlayerCard;
	Card otherPlayerCard;

	Player* leadPlayer, *otherPlayer;
	Player* winner;
};

struct TrickHistory {
	Trick tricks[MAX_TRICKS] = {};
	size_t size = 0;
};

struct Deck {
    Card cards[MAX_DECK_SIZE];
    size_t topCardIndex;
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

	Player* currentLead, *currentOther;
	TrickHistory trickHistory;

	RoundState state = RoundState::ONGOING;
	RoundConclusion conclusion = {};
};

// Fisher–Yates shuffle
void shuffleDeck(Deck& deck);

// Create and shuffle deck and deal 6 cards to players
void startRound(Round& round, Player& player1, Player& player2);

// Deal 3 to leading Player, then 3 to the other.
// Then 3 more to the leading, and lastly 3 to the other.
void initialDeal(Round& round);

void printLastTrick(const Round& round);

void printTrumpSuit(const Round& round);