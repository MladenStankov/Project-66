#pragma once
#include "files.h"
#include <fstream>

void writeIndent(std::ofstream& file, int level)
{
	for (int i = 0; i < level; i++) file << "\t";
}

void saveGameSettings(const Game& game, std::ofstream& file, int indentLevel)
{
	writeIndent(file, indentLevel);
	file << "\"settings\": {" << std::endl;

	writeIndent(file, indentLevel + 1);
	file << "\"status\": " << (int)game.status << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"target_points\": " << game.settings.targetPoints << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"non_trump_marriage\": " << game.settings.nonTrumpMarriagePoints << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"trump_marriage\": " << game.settings.trumpMarriagePoints << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"show_points\": " << (game.settings.showPlayerPoints ? "true" : "false") << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"last_trick_bonus\": " << (game.settings.lastTrickBonusPoints ? "true" : "false") << std::endl;
	
	writeIndent(file, indentLevel);
	file << "}" << std::endl;
}

void savePlayer(const Player& player, std::ofstream& file, int indentLevel)
{
	writeIndent(file, indentLevel);
	file << "{" << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"name\": \"" << player.name << "\"," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"current_points\": " << player.currentPoints << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"game_points\": " << player.gamePoints << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"is_leading\": " << (player.isLeading ? "true" : "false") << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"played_this_turn\": " << (player.playedThisTurn ? "true" : "false") << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"has_marriage\": " << (player.hasMarriage ? "true" : "false") << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"marriage_suit\": " << (int)player.marriageSuit << "," << std::endl;

	//Hand
	writeIndent(file, indentLevel + 1);
	file << "\"hand_card_count\": " << player.hand.cardCount << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"hand\": [";
	for (int i = 0; i < player.hand.cardCount; i++)
	{
		file << "{\"suit\": " << (int)player.hand.hand[i].suit << ", \"rank\": " << (int)player.hand.hand[i].rank << "}";
		if (i < player.hand.cardCount - 1) 
			file << ", ";
	}
	file << "]" << std::endl;
	
	writeIndent(file, indentLevel);
	file << "}" << std::endl;
}

void saveTrick(const char* name, const Trick& trick, std::ofstream& file, int indentLevel)
{
	writeIndent(file, indentLevel);
	file << "\"" << name << "\": {" << std::endl;
	
	if(trick.leadPlayer)
	{
		writeIndent(file, indentLevel + 1);
		file << "\"lead_card\": {\"suit\": " << (int)trick.leadPlayerCard.suit << ", \"rank\": " << (int)trick.leadPlayerCard.rank << "}," << std::endl;
	}
	else
	{
		writeIndent(file, indentLevel + 1);
		file << "\"lead_card\": null," << std::endl;
	}

	if(trick.nonLeadPlayer)
	{
		writeIndent(file, indentLevel + 1);
		file << "\"non_lead_card\": {\"suit\": " << (int)trick.nonLeadCard.suit << ", \"rank\": " << (int)trick.nonLeadCard.rank << "}," << std::endl;
	}
	else
	{
		writeIndent(file, indentLevel + 1);
		file << "\"non_lead_card\": null," << std::endl;
	}

	writeIndent(file, indentLevel + 1);
	file << "\"lead_player\": ";
	if(trick.leadPlayer) file << "\"" << trick.leadPlayer->name << "\""; else file << "null";
	file << "," << std::endl;

	writeIndent(file, indentLevel + 1);
	file << "\"non_lead_player\": ";
	if(trick.nonLeadPlayer) file << "\"" << trick.nonLeadPlayer->name << "\""; else file << "null";
	file << "," << std::endl;

	writeIndent(file, indentLevel + 1);
	file << "\"winner\": ";
	if(trick.winner) file << "\"" << trick.winner->name << "\""; else file << "null";
	file << std::endl;

	writeIndent(file, indentLevel);
	file << "}" << std::endl;
}

void saveRoundsHistory(const RoundsHistory& history, std::ofstream& file, int indentLevel)
{
	writeIndent(file, indentLevel);
	file << "\"rounds_history\": {" << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"size\": " << history.size << "," << std::endl;
	
	writeIndent(file, indentLevel + 1);
	file << "\"history\": [" << std::endl;

	for (size_t i = 0; i < history.size; i++)
	{
		const Round& r = history.history[i];
		writeIndent(file, indentLevel + 1);
		file << "{" << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"status\": " << (int)r.status << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"trump\": " << (int)r.trump << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"bottom_card\": {\"suit\": " << (int)r.bottomCard.suit << ", \"rank\": " << (int)r.bottomCard.rank << "}," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"is_closed\": " << (r.isClosed ? "true" : "false") << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"player_who_closed\": ";
		if(r.playerWhoClosed) file << "\"" << r.playerWhoClosed->name << "\""; else file << "null";
		file << "," << std::endl;

		// Deck
		writeIndent(file, indentLevel + 2);
		file << "\"deck_top_index\": " << r.deck.topCardIndex << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"deck_cards\": [";
		for (size_t j = 0; j < MAX_DECK_SIZE; j++)
		{
			file << "{\"suit\": " << (int)r.deck.cards[j].suit << ", \"rank\": " << (int)r.deck.cards[j].rank << "}";
			if (j < MAX_DECK_SIZE - 1)
				file << ", ";
		}
		file << "]," << std::endl;

		saveTrick("current_trick", r.currentTrick, file, indentLevel + 2);
		file << "," << std::endl;
		saveTrick("last_trick", r.lastTrick, file, indentLevel + 2);
		file << "," << std::endl;

		// Conclusion
		writeIndent(file, indentLevel + 2);
		file << "\"conclusion\": {" << std::endl;
		
		writeIndent(file, indentLevel + 3);
		file << "\"winner\": ";
		if(r.conclusion.winner) file << "\"" << r.conclusion.winner->name << "\""; else file << "null";
		file << "," << std::endl;

		writeIndent(file, indentLevel + 3);
		file << "\"loser\": ";
		if(r.conclusion.loser) file << "\"" << r.conclusion.loser->name << "\""; else file << "null";
		file << "," << std::endl;

		writeIndent(file, indentLevel + 3);
		file << "\"accumulated_points\": " << r.conclusion.accumulatedPoints << "," << std::endl;
		
		writeIndent(file, indentLevel + 3);
		file << "\"winner_points\": " << r.conclusion.winnerPoints << "," << std::endl;
		
		writeIndent(file, indentLevel + 3);
		file << "\"loser_points\": " << r.conclusion.loserPoints << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "}" << std::endl;

		writeIndent(file, indentLevel + 1);
		file << "}";
		if (i < history.size - 1)
			file << ",";
		file << std::endl;
	}
	writeIndent(file, indentLevel + 1);
	file << "]" << std::endl;
	
	writeIndent(file, indentLevel);
	file << "}" << std::endl;
}

bool saveGame(const Game& game, const char* fileName)
{
	std::ofstream file(fileName);

	if (!file.is_open()) {
		std::cout << "An error occurred when saving the game" << std::endl;
		return false;
	}

	file << "{" << std::endl;

	// Settings
	saveGameSettings(game, file, 1);
	file << "," << std::endl;

	// Players
	writeIndent(file, 1);
	file << "\"player1\": ";
	savePlayer(game.player1, file, 1);
	file << "," << std::endl;

	writeIndent(file, 1);
	file << "\"player2\": ";
	savePlayer(game.player2, file, 1);
	file << "," << std::endl;

	// Rounds History
	saveRoundsHistory(game.roundsHistory, file, 1);
	file << std::endl;

	file << "}" << std::endl;

	return true;
}

bool loadGame(Game& game, const char* fileName)
{
	return false;
}