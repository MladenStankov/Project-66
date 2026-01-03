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

bool playCard(Round& round, Player& player, int cardIndex)
{
	if (cardIndex < 0 || cardIndex >= player.hand.cardCount)
	{
		std::cout << "Invalid card index." << std::endl;
		return true;
	}

	if (player.playedThisTurn)
	{
		std::cout << "You have already played a card this turn." << std::endl;
		return true;
	}

	if (player.hasMarriage)
	{
		Card c = player.hand.hand[cardIndex];
		if (c.suit != player.marriageSuit || (c.rank != Rank::KING && c.rank != Rank::QUEEN))
		{
			Card kingCard = { c.suit, Rank::KING }, queenCard = { c.suit, Rank::QUEEN };
			std::cout << "You must play the";
			printCard(queenCard);
			std::cout << " or ";
			printCard(kingCard);
			std::cout << std::endl;

			return true;
		}
		player.hasMarriage = false;
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
		currentTrick.nonLeadPlayer = &player;
		currentTrick.nonLeadCard = playedCard;

		// Evaluate trick
		bool leadWins = beats(currentTrick.leadPlayerCard, currentTrick.nonLeadCard, round.trump);
		
		Player* winner = leadWins ? currentTrick.leadPlayer : currentTrick.nonLeadPlayer;
		Player* loser = leadWins ? currentTrick.nonLeadPlayer : currentTrick.leadPlayer;

		currentTrick.winner = winner;

		std::cout << winner->name << " wins the trick!";
		
		unsigned int points = getCardValue(currentTrick.leadPlayerCard) + getCardValue(currentTrick.nonLeadCard);
		std::cout << " (+" << points << " points)";
		std::cout << std::endl;
		std::cout << std::endl;

		winner->currentRoundPoints += points;
		
		round.lastTrick = currentTrick;
		round.currentTrick = {};

		if (round.deck.topCardIndex < MAX_DECK_SIZE)
		{
			Card c1 = round.deck.cards[round.deck.topCardIndex++];
			addCardToHand(*winner, c1, &round.trump);

			Card c2 = round.deck.cards[round.deck.topCardIndex++];
			addCardToHand(*loser, c2, &round.trump);
		}
		else if (winner->hand.cardCount == 0)
		{
			winner->currentRoundPoints += 10;
			std::cout << "Last hand for " << winner->name << " (+10 points)" << std::endl << std::endl;
			return false;
		}

		winner->isLeading = true;
		loser->isLeading = false;
		
		winner->playedThisTurn = false;
		loser->playedThisTurn = false;

		if(round.status == RoundStatus::STARTED)
		{
			changeRoundState(round, RoundStatus::IN_MIDDLE);
		}

		return true;
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

bool findCardInHand(Player& player, const Suit& suit, const Rank& rank, size_t& index)
{
	for (size_t i = 0; i < player.hand.cardCount; i++)
	{
		if (player.hand.hand[i].suit == suit && player.hand.hand[i].rank == rank)
		{
			index = i;
			return true;
		}
	}
	return false;
}

