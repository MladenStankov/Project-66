#include <iostream>
#include "card.h"
#include "console.h"

const char* getRankString(const Rank& rank)
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

const char* getSuitString(const Suit& suit)
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

void printCard(const Card& card)
{
	if (card.suit == Suit::CLUBS || card.suit == Suit::SPADES)
		setConsoleColor(Color::Gray);
	else setConsoleColor(Color::Red);

	std::cout << getRankString(card.rank) << getSuitString(card.suit);

	setConsoleColor(Color::White);
}

bool beats(const Card& c1, const Card& c2, const Suit& trump)
{
	if (c1.suit == trump && c2.suit != trump) return true;
	if (c1.suit != trump && c2.suit == trump) return false;

	if (c1.suit == c2.suit)return ((int)c1.rank) > ((int)c2.rank) ? true : false;
	return true;
}