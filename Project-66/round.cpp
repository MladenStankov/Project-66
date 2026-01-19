/**
*  
* Solution to course project # 66
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Mladen Stankov
* @idnumber 3MI0600676
* @compiler Visual Studio
*
* <Implementation of Round logic>
*
*/
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
		for (int i = 0; i < 3; ++i)
		{
			addCardToHand(leadingPlayer, round.deck.cards[round.deck.topCardIndex++], nullptr);
		}

		for (int i = 0; i < 3; ++i)
		{
			addCardToHand(nonLeadingPlayer, round.deck.cards[round.deck.topCardIndex++], nullptr);
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
	unsigned int index = 0;
	unsigned int roundHistorySize = game.roundsHistory.size;
	Round& currentRound = game.roundsHistory.history[roundHistorySize - 1];

	for (int s = 0; s < TOTAL_SUITS; ++s)
	{
		for (int r = 0; r < TOTAL_RANKS; ++r)
		{
			currentRound.deck.cards[index].suit = Suit(s + 1);
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

	shuffleDeck(currentRound.deck);

	initialDeal(currentRound, game);

	currentRound.bottomCard = currentRound.deck.cards[currentRound.deck.topCardIndex];
	currentRound.trump = currentRound.deck.cards[currentRound.deck.topCardIndex].suit;

	// Swap bottom card with the last card so it is drawn last
	swapCards(currentRound.deck.cards[currentRound.deck.topCardIndex], currentRound.deck.cards[MAX_DECK_SIZE - 1]);

	sortHand(game.player1, currentRound.trump);
	sortHand(game.player2, currentRound.trump);

	currentRound.status = RoundStatus::STARTED;

	return currentRound;
}

void printLastTrick(const Round& round)
{
	const Trick trick = round.lastTrick;

	std::cout << trick.leadPlayer->name << ": ";
	printCard(trick.leadPlayerCard);
	std::cout << " (lead)" << std::endl;

	std::cout << trick.nonLeadPlayer->name << ": ";
	printCard(trick.nonLeadCard);
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

void printRoundInfo(const Game& game, const Round& round)
{
	if (game.settings.showPlayerPoints)
	{
		std::cout << game.player1.name << " current round points: " << game.player1.currentPoints << std::endl;
		std::cout << game.player2.name << " current round points: " << game.player2.currentPoints << std::endl;
	}
	printTrumpSuit(round);
	printBottomCard(round);
	std::cout << "Cards left in deck: " << MAX_DECK_SIZE - round.deck.topCardIndex << std::endl;
}

void changeRoundState(Round& round, RoundStatus status)
{
	round.status = status;
}

bool switchNine(Round& round, Player& player)
{
	unsigned int index = 0;
	if (findCardInHand(player, round.trump, Rank::NINE, index) == true)
	{
		swapCards(player.hand.hand[index], round.bottomCard);
		sortHand(player, round.trump);

		return true;
	}
	else return false;
}

bool announceMarriage(Game& game, Round& round, Player& player, Suit suit)
{
	unsigned int temp;
	if (!findCardInHand(player, suit, Rank::KING, temp) || !findCardInHand(player, suit, Rank::QUEEN, temp))
		return false;

	player.hasMarriage = true;
	player.marriageSuit = suit;

	if (suit == round.trump) player.currentPoints += game.settings.trumpMarriagePoints;
	else player.currentPoints += game.settings.nonTrumpMarriagePoints;

	return true;
}

void cleanupRound(Round& round, Game& game, Player* winner, Player* loser, int accumulatedGamePoints)
{
	winner->isLeading = true;
	winner->gamePoints += accumulatedGamePoints;
	winner->currentPoints = 0;
	winner->playedThisTurn = false;
	winner->hasMarriage = false;

	loser->isLeading = false;
	loser->currentPoints = 0;
	loser->playedThisTurn = false;
	loser->hasMarriage = false;

	game.status = GameStatus::IN_BETWEEN_ROUNDS;
	game.roundsHistory.history[game.roundsHistory.size - 1] = round;
	game.roundsHistory.size++;

	// Deleting the current hand
	winner->hand = {}, loser->hand = {};
}

void createConclusion(Round& round, Player* winner, Player* loser, int accumulatedGamePoints)
{
	round.conclusion.loser = loser;
	round.conclusion.winner = winner;
	round.conclusion.loserPoints = loser->currentPoints;
	round.conclusion.winnerPoints = winner->currentPoints;
	round.conclusion.accumulatedPoints = accumulatedGamePoints;
}

void printRoundConclusion(const Round& round, unsigned int roundNumber)
{
	std::cout << "Round " << roundNumber << " ended." << std::endl;
	printSeparatingLine();
	if (round.playerWhoClosed)
	{
		std::cout << round.playerWhoClosed->name << " closed the game!" << std::endl;
	}

	std::cout << round.conclusion.winner->name << " wins the round! (+" << round.conclusion.accumulatedPoints << " game points)" << std::endl;
	std::cout << "Round Points" << std::endl;
	std::cout << round.conclusion.winner->name << ": " << round.conclusion.winnerPoints << " | " << round.conclusion.loser->name << ": " << round.conclusion.loserPoints << std::endl;
	std::cout << "Starting Round " << roundNumber + 1 << "." << std::endl << std::endl;
}

void endRound(Round& round, Game& game, Player* stopper)
{
	round.status = RoundStatus::ENDED;

	Player* winner = nullptr;
	Player* loser = nullptr;
	int accumulatedGamePoints = 0;

	if (stopper != nullptr)
	{
		if (stopper->currentPoints >= 66)
		{
			winner = stopper;
			loser = (stopper == &game.player1) ? &game.player2 : &game.player1;
			accumulatedGamePoints = (loser->currentPoints >= 33) ? 1 : 2;
		}
		else
		{
			loser = stopper;
			winner = (stopper == &game.player1) ? &game.player2 : &game.player1;
			accumulatedGamePoints = 3;
		}
	}
	else
	{
		if (round.playerWhoClosed != nullptr)
		{
			if (round.playerWhoClosed->currentPoints >= 66)
			{
				winner = round.playerWhoClosed;
				loser = (winner == &game.player1) ? &game.player2 : &game.player1;
				accumulatedGamePoints = (loser->currentPoints >= 33) ? 1 : 2;
			}
			else
			{
				loser = round.playerWhoClosed;
				winner = (loser == &game.player1) ? &game.player2 : &game.player1;
				accumulatedGamePoints = 3;
			}
		}
		else
		{
			winner = (game.player1.currentPoints >= game.player2.currentPoints) ? &game.player1 : &game.player2;
			loser = (game.player1.currentPoints < game.player2.currentPoints) ? &game.player1 : &game.player2;
			accumulatedGamePoints = (loser->currentPoints >= 33) ? 1 : 2;
		}
	}

	createConclusion(round, winner, loser, accumulatedGamePoints);

	printRoundConclusion(round, game.roundsHistory.size);

	cleanupRound(round, game, winner, loser, accumulatedGamePoints);

	if (winner->gamePoints >= game.settings.targetPoints)
	{
		game.status = GameStatus::ENDED;
		std::cout << winner->name << " reached the target points!" << std::endl;
	}
}