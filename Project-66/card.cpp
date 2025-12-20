#include "card.h"
#include <iostream>

const char* getRankString(Rank rank)
{
	switch (rank)
	{
		case Rank::NINE:
			return "Nine";
		case Rank::TEN:
			return "Ten";
		case Rank::JACK:
			return "Jack";
		case Rank::QUEEN:
			return "Queen";
		case Rank::KING:
			return "King";
		case Rank::ACE:
			return "Ace";
	}
}

const char* getSuitString(Suit suit)
{
	switch (suit)
	{
	case Suit::CLUBS:
		return CLUBS_SYMBOL;
	case Suit::DIAMONDS:
		return DIAMONDS_SYMBOL;
	case Suit::HEARTS:
		return HEARTS_SYMBOL;
	case Suit::SPADES:
		return SPADES_SYMBOL;
	}
}

void printCard(Card card)
{
	std::cout << getRankString(card.rank) << getSuitString(card.suit);
}

int compareCards(Card c1, Card c2, Suit trump)
{
	if (c1.suit == trump && c2.suit != trump) return 1;
	if (c1.suit != trump && c2.suit == trump) return -1;

	if (c1.suit == c2.suit)return ((int)c1.rank) > ((int)c2.rank) ? 1 : -1;
	return 1;
}