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

	std::cout << "> start (Starts new round or starts the game)" << std::endl;
	std::cout << "> rules (Shows the current rules)" << std::endl;
	std::cout << "> settings (Change some rules of the game)" << std::endl;

	std::cout << "> hand (Shows your current hand, ordered by power and suit)" << std::endl;
	std::cout << "> play <index> (Plays a card with that <index> that is shows in the <hand> command. Starts from 0)" << std::endl;
	std::cout << "> switch-nine (Switch the your trump nine card with the card on the bottom of the deck)" << std::endl;
	std::cout << "> marriage <suit> (Announce marriage for a <suit>)" << std::endl;
	std::cout << "> close (Closes the deck)" << std::endl;

	std::cout << "> last-trick (Shows who won the last trick and what were the cards)" << std::endl;
	std::cout << "> trump (Shows the trump suit)" << std::endl;
	std::cout << "> bottom-card (Shows the bottom card, if it's there" << std::endl;
	std::cout << "> history (Shows round history)" << std::endl;
	std::cout << "> status (Shows current status of the game)" << std::endl;

	std::cout << "> stop (The current player stops the round if he thinks he won)" << std::endl;
	std::cout << "> surrender (The other player wins the current round)" << std::endl;
	std::cout << "> surrender-forever (The game ends and the other player wins)" << std::endl
		;
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
	system("CLS");

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
			Round& round = startRound(game);
			std::cout << "The Round started" << std::endl;
			std::cout << "Leading player: " << getLeadingPlayer(game).name << std::endl;
			std::cout << "Non-Leading player: " << getNonLeadingPlayer(game).name << std::endl;
			printRoundInfo(round);
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
		if (game.status != GameStatus::NOT_STARTED)
		{
			std::cout << "Game already started. Cannot change settings" << std::endl;
		}
		else
		{
		//showSettings(game.settings);
		}
	}
	else if (compareWords(command, "hand"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}

		Player& leadingPlayer = getLeadingPlayer(game);
		if (leadingPlayer.playedThisTurn == false)
		{
			std::cout << leadingPlayer.name << "`s hand (lead)" << std::endl;
			printHand(leadingPlayer);
		}
		else
		{
			Player& nonLeadingPlayer = getNonLeadingPlayer(game);
			std::cout << nonLeadingPlayer.name << "`s hand (non-lead)" << std::endl;

			printHand(nonLeadingPlayer);
		}
		std::cout << std::endl;
	}
	else if (compareWords(command, "play"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}

		char* nextArg = getNextWord(command);
		if (*nextArg == '\0')
		{
			std::cout << "Usage: play <index>" << std::endl;
			return;
		}
		int cardIndex = customAtoi(nextArg);

		Player& player = getThePlayerThatIsOnTurn(game);
		Round& currentRound = getCurrentRound(game);
		playCard(currentRound, player, cardIndex);
	}
	else if (compareWords(command, "switch-nine"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}

		//switchNine(game);
	}
	else if (compareWords(command, "marriage"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//marriage(game);
	}
	else if (compareWords(command, "last-trick"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//showLastTrick(game);
	}
	else if (compareWords(command, "trump"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//showTrump(game);
	}
	else if (compareWords(command, "bottom-card"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//something 
	}
	else if (compareWords(command, "history"))
	{
		if (game.status != GameStatus::IN_BETWEEN_ROUNDS)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//showHistory(game);
	}
	else if (compareWords(command, "status"))
	{
		if (game.status != GameStatus::IN_BETWEEN_ROUNDS)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//showStatus(game);
	}
	else if (compareWords(command, "stop"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//stop(game);
	}
	else if (compareWords(command, "surrender"))
	{
		if (game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//surrender(game);
	}
	else if (compareWords(command, "surrender-forever"))
	{
		if (game.status != GameStatus::IN_BETWEEN_ROUNDS || game.status != GameStatus::IN_ROUND)
		{
			std::cout << "Game is not in a round" << std::endl;
			return;
		}
		//surrenderForever(game);
	}
	else if (compareWords(command, "save"))
	{
		if (game.status == GameStatus::NOT_STARTED)
		{
			std::cout << "Game has not started" << std::endl;
			return;
		}
		//save(game);
	}
	else if (compareWords(command, "load"))
	{
		if (game.status != GameStatus::NOT_STARTED)
		{
			std::cout << "Game has started" << std::endl;
			return;
		}
		//load(game);
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

