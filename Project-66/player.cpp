#include "player.h"
#include "card.h"
#include "game.h"
#include "round.h"
#include <iostream>

Player initPlayer(const char* name)
{
	PlayerHand newPlayerHand = { {}, 0 };
	Player newPlayer = {name, newPlayerHand, 0, 0, false };

	return newPlayer;
}

void addCardToHand(Player& player, Card card)
{
	if (player.hand.cardCount < 6)
	{
		player.hand.hand[player.hand.cardCount++] = card;
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
				addCardToHand(*winner, c);
			}
			if (round.deck.topCardIndex < MAX_DECK_SIZE)
			{
				Card c = round.deck.cards[round.deck.topCardIndex++];
				addCardToHand(*loser, c);
			}
		}

		winner->isLeading = true;
		loser->isLeading = false;
		
		winner->playedThisTurn = false;
		loser->playedThisTurn = false;
	}
}