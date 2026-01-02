#include "round.h"
#include "utils.h"
#include "card.h"

void initialDeal(Round& round)
{

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(*round.currentLead, round.deck.cards[round.deck.topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(*round.currentOther, round.deck.cards[round.deck.topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(*round.currentLead, round.deck.cards[round.deck.topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(*round.currentOther, round.deck.cards[round.deck.topCardIndex++]);
    }
}

void shuffleDeck(Deck& deck)
{
	for (size_t i = MAX_DECK_SIZE - 1; i >= 1; --i)
	{
		size_t j = generateRandomNumber(0, i);
		swapCards(deck.cards[i], deck.cards[j]);
	}
}

void startRound(Round& round, Player& player1, Player& player2)
{
	size_t index = 0;

	for (size_t s = 0; s < TOTAL_SUITS; ++s)
	{
		for (size_t r = 0; r < TOTAL_RANKS; ++r)
		{
			round.deck.cards[index].suit = Suit(s);
			round.deck.cards[index].rank = Rank(r);
			index++;
		}
	}

	unsigned int randomNumber = generateRandomNumber(0, 1);

	switch (randomNumber)
	{
		case 0:
			round.currentLead = &player1, round.currentOther = &player2; break;
		case 1:
			round.currentLead = &player2, round.currentOther = &player1; break;
	}

	shuffleDeck(round.deck);

	initialDeal(round);
}

void printLastTrick(const Round& round)
{
	if (round.trickHistory.size == 0) return;

	const Trick trick = round.trickHistory.tricks[round.trickHistory.size - 1];

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
	std::cout << "Trump suit: " << getSuitString(round.trump) << std::endl;
}