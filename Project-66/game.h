#pragma once
#include "card.h"
#include "round.h"
#include "player.h"

enum class GameStatus {
	NOT_STARTED = 1,
	IN_BETWEEN_ROUNDS = 2,
	IN_ROUND = 3,
	ENDED = 4
};

enum class GameSettingsType {
	TARGET_POINTS = 1,
	TRUMP_MARRIAGE_POINTS = 2,
	NON_TRUMP_MARRIAGE_POINTS = 3,
	SHOW_PLAYER_POINTS = 4,
	LAST_TRICK_BONUS_POINTS = 5,
};

struct GameSettings {	
	unsigned int targetPoints = 11;
	unsigned int nonTrumpMarriagePoints = 20, trumpMarriagePoints = 40;
	bool showPlayerPoints = false;
	bool lastTrickBonusPoints = true;
};

struct RoundsHistory {
	Round* history;
	size_t size = 0;
};

struct Game { 
	Player player1, player2;
	GameSettings settings;
	RoundsHistory roundsHistory;
	GameStatus status;
};

GameSettings initGameSettings();

void changeGameSettings(Game& game, GameSettingsType type, unsigned int value);

Game initGame(const GameSettings& settings);

void startGame(Game& game);

void changeGameStatus(Game& game, const GameStatus& status);

void playRound(Game& game);

void printRoundsHistory(const Game& game);

Player& getLeadingPlayer(Game& game);
Player& getNonLeadingPlayer(Game& game);
Player& getThePlayerThatIsOnTurn(Game& game);

Round& getCurrentRound(Game& game);
void printGameInfo(const Game& game);