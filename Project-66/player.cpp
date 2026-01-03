#include "player.h"
#include "card.h"
#include "game.h"
#include "round.h"
#include "utils.h"
#include <iostream>

Player initPlayer(const char* name)
{
	PlayerHand newPlayerHand = { {}, 0 };
	Player newPlayer = {name, newPlayerHand, 0, 0, false };

	return newPlayer;
}

void addCardToHand(Player& player, Card card, Suit* trump)
{
	if (player.hand.cardCount < 6)
	{
		player.hand.hand[player.hand.cardCount++] = card;
	}

	if (trump != nullptr)
	{
		sortHand(player, *trump);
	}
}

void printHand(const Player& player)
{
	std::cout << "{ ";
	for (int i = 0; i < player.hand.cardCount; i++)
	{
		printCard(player.hand.hand[i]);
		if(i != player.hand.cardCount - 1)
			std::cout << " , ";
	}
	std::cout << " }";
}

void removeCardFromHand(Player& player, size_t index)
{
	if (index >= player.hand.cardCount) return;

	for (size_t i = index; i < player.hand.cardCount - 1; i++)
	{
		player.hand.hand[i] = player.hand.hand[i + 1];
	}
	player.hand.cardCount--;
}

void playCard(Round& round, Player& player, int cardIndex)
{
	if (cardIndex < 0 || cardIndex >= player.hand.cardCount)
	{
		std::cout << "Invalid card index." << std::endl;
		return;
	}

	if (player.playedThisTurn)
	{
		std::cout << "You have already played a card this turn." << std::endl;
		return;
	}

	Card playedCard = player.hand.hand[cardIndex];
	removeCardFromHand(player, cardIndex);

	std::cout << player.name << " played ";
	printCard(playedCard);
	std::cout << std::endl;

	player.playedThisTurn = true;

	Trick& currentTrick = round.currentTrick;

	if (currentTrick.leadPlayer == nullptr)
	{
		// First card in the trick
		currentTrick.leadPlayer = &player;
		currentTrick.leadPlayerCard = playedCard;
	}
	else
	{
		// Second card in the trick
		currentTrick.otherPlayer = &player;
		currentTrick.otherPlayerCard = playedCard;

		// Evaluate trick
		bool leadWins = beats(currentTrick.leadPlayerCard, currentTrick.otherPlayerCard, round.trump);
		
		Player* winner = leadWins ? currentTrick.leadPlayer : currentTrick.otherPlayer;
		Player* loser = leadWins ? currentTrick.otherPlayer : currentTrick.leadPlayer;

		currentTrick.winner = winner;

		std::cout << winner->name << " wins the trick!";
		
		unsigned int points = getCardValue(currentTrick.leadPlayerCard) + getCardValue(currentTrick.otherPlayerCard);
		std::cout << " (+" << points << " points)";
		std::cout << std::endl;
		std::cout << std::endl;

		winner->currentRoundPoints += points;
		
		round.lastTrick = currentTrick;
		round.currentTrick = {};

		if (round.deck.topCardIndex < MAX_DECK_SIZE)
		{
			if (round.deck.topCardIndex < MAX_DECK_SIZE)
			{
				Card c = round.deck.cards[round.deck.topCardIndex++];
				addCardToHand(*winner, c, &round.trump);
			}
			if (round.deck.topCardIndex < MAX_DECK_SIZE)
			{
				Card c = round.deck.cards[round.deck.topCardIndex++];
				addCardToHand(*loser, c, &round.trump);
			}
		}

		winner->isLeading = true;
		loser->isLeading = false;
		
		winner->playedThisTurn = false;
		loser->playedThisTurn = false;
	}
}

bool isRed(Suit s)
{
	return s == Suit::DIAMONDS || s == Suit::HEARTS;
}

// This ensures Separated red and black suits
int getSuitPriority(Suit s, Suit trump)
{
	if (s == trump) return 0;
	
	// Hardcoded preference to ensure proper alternation
	switch (trump)
	{
		case Suit::CLUBS:
			if (s == Suit::DIAMONDS) return 1;
			if (s == Suit::SPADES) return 2;
			if (s == Suit::HEARTS) return 3;
			break;
		case Suit::DIAMONDS:
			if (s == Suit::CLUBS) return 1;
			if (s == Suit::HEARTS) return 2;
			if (s == Suit::SPADES) return 3;
			break;
		case Suit::HEARTS:
			if (s == Suit::SPADES) return 1;
			if (s == Suit::DIAMONDS) return 2;
			if (s == Suit::CLUBS) return 3;
			break;
		case Suit::SPADES:
			if (s == Suit::HEARTS) return 1;
			if (s == Suit::CLUBS) return 2;
			if (s == Suit::DIAMONDS) return 3;
			break;
	}
}

void sortHand(Player& player, const Suit& trump)
{
	if(player.hand.cardCount < 2) return;

	for (size_t i = 0; i < player.hand.cardCount; i++)
	{
		for (size_t j = 0; j < player.hand.cardCount - 1; j++)
		{
			Card& c1 = player.hand.hand[j];
			Card& c2 = player.hand.hand[j + 1];

			int p1 = getSuitPriority(c1.suit, trump);
			int p2 = getSuitPriority(c2.suit, trump);

			bool swap = false;

			if (p1 > p2)
			{
				swap = true;
			}
			else if (p1 == p2)
			{
				if (getCardValue(c1) > getCardValue(c2))
				{
					swap = true;
				}
			}

			if (swap)
			{
				swapCards(c1, c2);
			}
		}
	}
}