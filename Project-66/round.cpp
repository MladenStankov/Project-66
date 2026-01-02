#include "round.h"
#include "utils.h"
#include "card.h"
#include "game.h"
#include "console.h"

void initialDeal(Round& round, Game& game)
{
	Player& leadingPlayer = getLeadingPlayer(game);
	Player& nonLeadingPlayer = getNonLeadingPlayer(game);

	for (int i = 0; i < 2; ++i)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			addCardToHand(leadingPlayer, round.deck.cards[round.deck.topCardIndex++]);
		}

		for (size_t i = 0; i < 3; ++i)
		{
			addCardToHand(nonLeadingPlayer, round.deck.cards[round.deck.topCardIndex++]);
		}
	}
}

void shuffleDeck(Deck& deck)
{
	for (unsigned int i = MAX_DECK_SIZE - 1; i >= 1; --i)
	{
		unsigned int j = generateRandomNumber(0, i);
		swapCards(deck.cards[i], deck.cards[j]);
	}
}

Round& startRound(Game& game)
{
	size_t index = 0;
	size_t roundHistorySize = game.roundsHistory.size;
	Round& currentRound = game.roundsHistory.history[roundHistorySize - 1];

	for (size_t s = 0; s < TOTAL_SUITS; ++s)
	{
		for (size_t r = 0; r < TOTAL_RANKS; ++r)
		{
			currentRound.deck.cards[index].suit = Suit(s);
			currentRound.deck.cards[index].rank = Rank(r + 9);
			index++;
		}
	}
	if (roundHistorySize == 1)
	{
		unsigned int randomNumber = generateRandomNumber(0, 2);

		switch (randomNumber)
		{
			case 0:
				game.player1.isLeading = true;
				break;
			case 1:
				game.player2.isLeading = true;
				break;
		}
	}
	else
	{
		Round lastRound = game.roundsHistory.history[roundHistorySize - 2];
		Player& winner = *lastRound.conclusion.winner;
		Player& loser = *lastRound.conclusion.loser;

		winner.isLeading = true;
		loser.isLeading = false;
	}


	shuffleDeck(currentRound.deck);

	initialDeal(currentRound, game);

	currentRound.bottomCard = currentRound.deck.cards[currentRound.deck.topCardIndex];
	currentRound.trump = currentRound.deck.cards[currentRound.deck.topCardIndex].suit;

	// Swap bottom card with the last card so it is drawn last
	swapCards(currentRound.deck.cards[currentRound.deck.topCardIndex], currentRound.deck.cards[MAX_DECK_SIZE - 1]);

	return currentRound;
}

void printLastTrick(const Round& round)
{
	const Trick trick = round.lastTrick;

	std::cout << "(Lead)" << trick.leadPlayer->name << ": ";
	printCard(trick.leadPlayerCard);
	std::cout << std::endl;

	std::cout << "(Other)" << trick.otherPlayer->name << ": ";
	printCard(trick.otherPlayerCard);
	std::cout << std::endl;

	std::cout << "Winner: " << trick.winner->name;
	std::cout << std::endl;
}

void printTrumpSuit(const Round& round)
{
	std::cout << "Trump suit: ";
	if (round.trump == Suit::CLUBS || round.trump == Suit::SPADES)
		setConsoleColor(Color::Gray);
	else setConsoleColor(Color::Red);

	std::cout << getSuitString(round.trump) << std::endl;

	setConsoleColor(Color::White);
}
void printBottomCard(const Round& round)
{
	std::cout << "Bottom Card: ";
	printCard(round.bottomCard);
	std::cout << std::endl;
}

void printRoundInfo(const Round& round)
{
	printTrumpSuit(round);

	printBottomCard(round);
}