#pragma once
#include "card.h"
#include "player.h"

constexpr size_t MAX_DECK_SIZE = 24;

struct Game {
	Card deck[MAX_DECK_SIZE] = {};
	size_t topCardIndex = 0;
	Card trumpCard;
	bool isStockClosed = false;
	Player player1, player2;
};


// Fills the deck and shuffles the card.
// Then deals 6 cards to both players and sets the trump card
void initGame(Game& game);

// Fisher–Yates shuffle
void shuffleDeck(Card deck[MAX_DECK_SIZE]);

// Deals 3 cards to player1, then 3 cards to player2.
// Then another 3 cards to player1 and 3 more cards to player2.
// That way both players have 6 cards.
void initialDealToPlayers(Card deck[MAX_DECK_SIZE], size_t& topCardIndex, Player& player1, Player& player2);

void processCommand(Game& game, const char* command);
void playRound(Game& game);