#include <iostream>
#include <windows.h>
#include "console.h"
#include "utils.h"
#include "round.h"
#include "game.h"

bool getSuit(char* str, Suit& suit)
{
	if (compareWords(str, "hearts")) 
		suit = Suit::HEARTS;
	else if (compareWords(str, "diamonds")) 
		suit = Suit::DIAMONDS;
	else if (compareWords(str, "clubs")) 
		suit = Suit::CLUBS;
	else if (compareWords(str, "spades")) 
		suit = Suit::SPADES;
	else return false;
	return true;
}

void setConsoleColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
}

void showHelpCommand()
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
	std::cout << "> info (Shows the trump suit and bottom card and other info)" << std::endl;
	std::cout << "> history (Shows round history)" << std::endl;
	std::cout << "> status (Shows current status of the game)" << std::endl;

	std::cout << "> stop (The current player stops the round if he thinks he won)" << std::endl;
	std::cout << "> surrender (The other player wins the current round)" << std::endl;
	std::cout << "> surrender-forever (The game ends and the other player wins)" << std::endl
		;
	std::cout << "> save <name> (Saves the current game in a file with a <name>)" << std::endl;
	std::cout << "> load <name> (Loads a game file with a <name>)" << std::endl;
}

void showRulesCommand(const GameSettings& gameSettings)
{
	std::cout << "SANTASE (66)" << std::endl;
	std::cout << "Each player gets 6 cards. The Trump suit is chosen at random." << std::endl;
	std::cout << "Card values: Ace=11, 10=10, King=4, Queen=3, Jack=2, 9=0." << std::endl;

	std::cout << "A marriage (K+Q of the same suit) gives: " << gameSettings.nonTrumpMarriagePoints << " points, ";
	std::cout << "or " << gameSettings.trumpMarriagePoints << " if it's the trump suit." << std::endl;

	std::cout << "The first player to reach 66 points wins the round." << std::endl;
	std::cout << "The first player to win " << gameSettings.targetPoints << " round/s wins the game." << std::endl;
}

void startCommand(Game& game)
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
		
		printSeparatingLine();

		std::cout << "Leading player: " << getLeadingPlayer(game).name << std::endl;
		std::cout << "Non-Leading player: " << getNonLeadingPlayer(game).name << std::endl;

		printSeparatingLine();

		printRoundInfo(game, round);
	}
	else {
		std::cout << "Game is already in progress" << std::endl;
	}
}

void helperSettingsCommand(Game& game, int choice)
{
	switch (choice)
	{
		case 1:
		{
			int targetPoints;
			std::cout << "Type integer value for target points: ";
			std::cin >> targetPoints;
			changeGameSettings(game, GameSettingsType::TARGET_POINTS, targetPoints);
			break;
		}
		case 2:
		{
			int nonTrumpMarriagePoints, trumpMarriagePoints;
			std::cout << "Type integer value for non-trump marriage points: ";
			std::cin >> nonTrumpMarriagePoints;
			std::cout << "Type integer value for trump marriage points: ";
			std::cin >> trumpMarriagePoints;

			changeGameSettings(game, GameSettingsType::NON_TRUMP_MARRIAGE_POINTS, nonTrumpMarriagePoints);
			changeGameSettings(game, GameSettingsType::TRUMP_MARRIAGE_POINTS, trumpMarriagePoints);
			break;
		}
		case 3:
		{
			bool showPlayerPoints;
			std::cout << "Type value for showing player points (0/1): ";
			std::cin >> showPlayerPoints;
			changeGameSettings(game, GameSettingsType::SHOW_PLAYER_POINTS, showPlayerPoints);
			break;
		}
		case 4:
		{
			bool lastTrickBonusPoints;
			std::cout << "Type value for last trick bonus points (0/1): ";
			std::cin >> lastTrickBonusPoints;
			changeGameSettings(game, GameSettingsType::LAST_TRICK_BONUS_POINTS, lastTrickBonusPoints);
			break;
		}
		default: std::cout << "Unexpected choice" << std::endl; return;
	}
	std::cout << std::endl << "Successfully changed settings" << std::endl;
}

void settingsCommand(Game& game)
{
	if (game.status != GameStatus::NOT_STARTED)
	{
		std::cout << "Game already started. Cannot change settings" << std::endl;
		return;
	}
	
	std::cout << "1) Target points to win [" << game.settings.targetPoints << "]" << std::endl;

	std::cout << "2) Marriage points (non-trump/trump) [" 
		<< game.settings.nonTrumpMarriagePoints 
		<< "/" << game.settings.trumpMarriagePoints << "]" << std::endl;

	std::cout << "3) Show players' points [" << (game.settings.showPlayerPoints ? "on" : "off") << "]" << std::endl;
	std::cout << "4) Last trick +10 [" << (game.settings.lastTrickBonusPoints ? "on" : "off") << "]" << std::endl;


	while (true)
	{
		std::cout << "Enter number to change or 'back' to return: ";
		char input[MAX_COMMAND_LEN] = "";
		std::cin.getline(input, MAX_COMMAND_LEN);

		std::cout << std::endl;

		if (compareWords(input, "back")) return;
		else
		{
			int choice = customAtoi(input);
			if (choice < 1 || choice > 4)
			{
				std::cout << "Incorrect value" << std::endl;
				continue;
			}
			else
			{
				helperSettingsCommand(game, choice);
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				return;
			}
		}
	}

}

void handCommand(Game& game)
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

void playCommand(Game& game, char* command)
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
	if (playCard(game, currentRound, player, cardIndex) == false)
	{
		endRound(currentRound, game);
	}
}

void switchNineCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Round& round = getCurrentRound(game);
	if (round.status != RoundStatus::IN_MIDDLE)
	{
		std::cout << "Round must not be closed and you should have won atleast one turn" << std::endl;
		return;
	}

	Player& player = getThePlayerThatIsOnTurn(game);
	if (player.isLeading != true)
	{
		std::cout << "You must be leading to switch the nine" << std::endl;
		return;
	}

	Card bottomCard = round.bottomCard;
	Card nineTrump = { round.trump, Rank::NINE };

	if (switchNine(round, player) != true)
	{
		std::cout << "You dont have ";
		printCard(nineTrump);
		std::cout << std::endl;
		return;
	}

	std::cout << "You switched your ";
	printCard(nineTrump);
	std::cout << " with ";
	printCard(bottomCard);
	std::cout << std::endl;
}

void marriageCommand(Game& game, char* command)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Round& round = getCurrentRound(game);
	if (round.status != RoundStatus::IN_MIDDLE)
	{
		std::cout << "You should have won atleast one turn" << std::endl;
		return;
	}

	Player& player = getThePlayerThatIsOnTurn(game);
	if (player.isLeading != true)
	{
		std::cout << "You must be leading to switch the nine" << std::endl;
		return;
	}

	char* nextArg = getNextWord(command);
	if (*nextArg == '\0')
	{
		std::cout << "Usage: marriage <suit>" << std::endl;
		return;
	}

	Suit suit;
	if (getSuit(nextArg, suit) == false)
	{
		std::cout << "The <suit> argument must be one of these: { clubs, diamnonds, hearts, spades }" << std::endl;
		return;
	}

	if (announceMarriage(game, round, player, suit) != true)
	{
		std::cout << "You dont have a marriage of " << getSuitString(suit) << std::endl;
		return;
	}

	std::cout << "You announced a marriage of " << getSuitString(suit);
	int points = (suit == round.trump) ? game.settings.trumpMarriagePoints : game.settings.nonTrumpMarriagePoints;
	std::cout << " (+" << points << " points)" << std::endl;

	std::cout << "Now you must play either: ";

	Card kingCard = { suit, Rank::KING }, queenCard = { suit, Rank::QUEEN };
	printCard(queenCard);
	std::cout << " or ";
	printCard(kingCard);
	std::cout << std::endl;

}

void lastTrickCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}
	Round& round = getCurrentRound(game);
	if (round.status == RoundStatus::STARTED)
	{
		std::cout << "Round just started. There is no last trick yet" << std::endl;
		return;
	}

	printLastTrick(round);
}

void infoCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Round& round = getCurrentRound(game);

	std::cout << "Current Round Info:" << std::endl;
	printRoundInfo(game, round);

	printSeparatingLine();

	std::cout << "Game Info:" << std::endl;
	printGameInfo(game);
}

void historyCommand(Game& game)
{
	if (game.status != GameStatus::IN_BETWEEN_ROUNDS)
	{
		std::cout << "Round must be finished to show round history" << std::endl;
		return;
	}
	printRoundsHistory(game);
}

void stopCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Player& player = getThePlayerThatIsOnTurn(game);
	if (!player.isLeading)
	{
		std::cout << "You must be leading to stop the round" << std::endl;
		return;
	}

	Round& round = getCurrentRound(game);
	endRound(round, game, &player);
}

void closeCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Round& round = getCurrentRound(game);
	if (round.status != RoundStatus::IN_MIDDLE)
	{
		std::cout << "You should have won atleast one turn to close the game" << std::endl;
		return;
	}

	Player& player = getThePlayerThatIsOnTurn(game);
	if (!player.isLeading)
	{
		std::cout << "You must be leading to close the game" << std::endl;
		return;
	}

	if (round.isClosed)
	{
		std::cout << "The game is already closed" << std::endl;
		return;
	}
	
	if (round.deck.topCardIndex >= MAX_DECK_SIZE)
	{
		std::cout << "The deck is empty, you cannot close it" << std::endl;
		return;
	}

	round.isClosed = true;
	round.playerWhoClosed = &player;

	std::cout << player.name << " closed the game!" << std::endl;
}

void surrenderCommand(Game& game)
{
	if (game.status != GameStatus::IN_ROUND)
	{
		std::cout << "Game is not in a round" << std::endl;
		return;
	}

	Player& currentPlayer = getThePlayerThatIsOnTurn(game);

	std::cout << currentPlayer.name << " surrendered the round" << std::endl;

	Round& round = getCurrentRound(game);
	endRound(round, game, &currentPlayer);
}

void surrenderForeverCommand(Game& game)
{
	if (game.status == GameStatus::NOT_STARTED)
	{
		std::cout << "Game has not started" << std::endl;
		return;
	}
	changeGameStatus(game, GameStatus::ENDED);
	Player& playerSurrendered = getThePlayerThatIsOnTurn(game);
	Player gameWinner = playerSurrendered.isLeading ? getNonLeadingPlayer(game) : getLeadingPlayer(game);

	std::cout << playerSurrendered.name << " surrendered" << std::endl;
	std::cout << gameWinner.name << " wins the whole game. Congratulations!" << std::endl;
}

void processCommand(char* command, Game& game)
{
	system("CLS");

	if (compareWords(command, "help"))
	{
		showHelpCommand();
	}
	else if (compareWords(command, "start"))
	{
		startCommand(game);
	}
	else if (compareWords(command, "rules"))
	{
		showRulesCommand(game.settings);
	}
	else if (compareWords(command, "settings"))
	{
		settingsCommand(game);
	}
	else if (compareWords(command, "hand"))
	{
		handCommand(game);
	}
	else if (compareWords(command, "play"))
	{
		playCommand(game, command);
	}
	else if (compareWords(command, "switch-nine"))
	{
		switchNineCommand(game);
	}
	else if (compareWords(command, "marriage"))
	{
		marriageCommand(game, command);
	}
	else if (compareWords(command, "close"))
	{
		closeCommand(game);
	}
	else if (compareWords(command, "last-trick"))
	{
		lastTrickCommand(game);
	}
	else if (compareWords(command, "info"))
	{
		infoCommand(game);
	}
	else if (compareWords(command, "history"))
	{
		historyCommand(game);
	}
	else if (compareWords(command, "stop"))
	{
		stopCommand(game);
	}
	else if (compareWords(command, "surrender"))
	{
		surrenderCommand(game);
	}
	else if (compareWords(command, "surrender-forever"))
	{
		surrenderForeverCommand(game);
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

