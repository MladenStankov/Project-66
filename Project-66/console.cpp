#include <iostream>
#include <windows.h>
#include "console.h"
#include "utils.h"
#include "round.h"
#include "game.h"

void setConsoleColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
}

void showHelp()
{
	std::cout << "> help" << std::endl;
	std::cout << "> start (Starts new round)" << std::endl;
	std::cout << "> rules (Shows the current rules)" << std::endl;
	std::cout << "> settings (Change some rules of the game)" << std::endl;
	std::cout << "> hand (Shows your current hand, ordered by power and suit)" << std::endl;
	std::cout << "> play <index> (Plays a card with that <index> that is shows in the <hand> command. Starts from 0)" << std::endl;
	std::cout << "> switch-nine (Switch the your trump nine card with the card on the bottom of the deck)" << std::endl;
	std::cout << "> marriage <suit> (Announce marriage for a <suit>)" << std::endl;
	std::cout << "> close (Closes the deck)" << std::endl;
	std::cout << "> last-trick (Shows who won the last trick and what were the cards)" << std::endl;
	std::cout << "> trump (Shows the trump suit)" << std::endl;
	std::cout << "> history (Shows round history)" << std::endl;
	std::cout << "> status (Shows current status of the game)" << std::endl;
	std::cout << "> stop (The current player stops the round if he thinks he won)" << std::endl;
	std::cout << "> surrender (The other player wins the current round)" << std::endl;
	std::cout << "> surrender-forever (The game ends and the other player wins)" << std::endl;
	std::cout << "> save <name> (Saves the current game in a file with a <name>)" << std::endl;
	std::cout << "> load <name> (Loads a game file with a <name>)" << std::endl;
}

void showRules(const GameSettings& gameSettings)
{
	std::cout << "SANTASE (66)" << std::endl;
	std::cout << "Each player gets 6 cards. The Trump suit is chosen at random." << std::endl;
	std::cout << "Card values: Ace=11, 10=10, King=4, Queen=3, Jack=2, 9=0." << std::endl;

	std::cout << "A marriage (K+Q of the same suit) gives:" << gameSettings.nonTrumpMarriagePoints << "points, ";
	std::cout << "or " << gameSettings.trumpMarriagePoints << " if it's the trump suit." << std::endl;

	std::cout << "The first player to reach 66 points wins the round." << std::endl;
	std::cout << "The first player to reach " << gameSettings.targetPoints << " rounds wins the game." << std::endl;
}

void processCommand(char* command, Game& game)
{
	if (compareWords(command, "help"))
	{
		showHelp();
	}
	else if (compareWords(command, "start"))
	{
		if (game.status == GameStatus::NOT_STARTED)
		{
			startGame(game);
			std::cout << "Game started. Type again start to start the first round." << std::endl;
		}
		else if (game.status == GameStatus::IN_BETWEEN_ROUNDS)
		{
			changeGameStatus(game, GameStatus::IN_ROUND);
			startRound(game);
			std::cout << "Round started" << std::endl;
		}
		else {
			std::cout << "Game is already in progress" << std::endl;
		}
	}
	else if (compareWords(command, "rules"))
	{
		showRules(game.settings);
	}
	else if (compareWords(command, "settings"))
	{
		//showSettings(game.settings);
	}
	else if (compareWords(command, "hand"))
	{
		Player& leadingPlayer = getLeadingPlayer(game);
		if (leadingPlayer.playedThisTrick == false)
		{
			printHand(leadingPlayer);
		}
		else
		{
			Player& nonLeadingPlayer = getNonLeadingPlayer(game);
			printHand(nonLeadingPlayer);
		}
	}
	else if (compareWords(command, "play"))
	{
		//playCard(game);
	}
	else if (compareWords(command, "switch-nine"))
	{
		//switchNine(game);
	}
	else if (compareWords(command, "marriage"))
	{
		//marriage(game);
	}
	else if (compareWords(command, "last-trick"))
	{
		//showLastTrick(game);
	}
	else if (compareWords(command, "trump"))
	{
		//showTrump(game);
	}
	else if (compareWords(command, "history"))
	{
		//showHistory(game);
	}
	else if (compareWords(command, "status"))
	{
		//showStatus(game);
	}
	else if (compareWords(command, "stop"))
	{
		//stop(game);
	}
	else if (compareWords(command, "surrender"))
	{
		//surrender(game);
	}
	else if (compareWords(command, "surrender-forever"))
	{
		//surrenderForever(game);
	}
	else if (compareWords(command, "save"))
	{
		//save(game);
	}
	else if (compareWords(command, "load"))
	{
		//load(game);
	}
	else if (compareWords(command, "help"))
	{
		showHelp();
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

