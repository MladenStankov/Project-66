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
* <Header file for Round struct and logic>
*
*/
#pragma once
#include "card.h"
#include "player.h"
#include <iostream>

constexpr unsigned int MAX_DECK_SIZE = 24;

struct Game;

enum class RoundStatus {
	NOT_STARTED = 1,
	STARTED = 2,
	IN_MIDDLE = 3,
	ENDED = 4,
};

struct Trick {
	Card leadPlayerCard, nonLeadCard;
	Player* leadPlayer = nullptr, *nonLeadPlayer = nullptr;
	Player* winner = nullptr;
};

struct Deck {
	Card cards[MAX_DECK_SIZE] = {};
	unsigned int topCardIndex = 0;
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
	RoundStatus status = RoundStatus::NOT_STARTED;
	Player* playerWhoClosed = nullptr;
	bool isClosed = false;

	RoundConclusion conclusion = {};
};

// Functions
void shuffleDeck(Deck& deck);

Round& startRound(Game& game);

void initialDeal(Round& round, Game& game);
void printLastTrick(const Round& round);
void printRoundInfo(const Game& game, const Round& round);
void changeRoundState(Round& round, RoundStatus status);
bool switchNine(Round& round, Player& player);
bool announceMarriage(Game& game, Round& round, Player& player, Suit suit);

void endRound(Round& round, Game& game, Player* stopper = nullptr);
void cleanupRound(Round& round, Game& game, Player* winner, Player* loser, int accumulatedGamePoints);
