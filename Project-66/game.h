#pragma once
#include "card.h"
#include "player.h"
#include "round.h"

enum class GameSettingsType {
	TARGET_POINTS = 1,
	MARRIAGE_POINTS = 2,
	SHOW_PLAYER_POINTS = 3,
	LAST_TRICK_BONUS_POINTS = 4,
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
};

GameSettings initGameSettings();

void changeGameSettings(GameSettings& settings, GameSettingsType type, const char* value);

Game initGame(const GameSettings& settings);

void processCommand(Game& game, const char* command);
void playRound(Game& game);

void printRoundsHistory(const Game& game);