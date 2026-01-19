/**
*  
* Solution to course project # 66
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Mladen Stankov
* @idnumber 3MI0600676
* @compiler GCC
*
* <Implementation of file saving/loading logic>
*
*/

#include "files.h"
#include "utils.h"
#include <fstream>
#include <iostream>

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

	for (int i = 0; i < history.size; i++)
	{
		const Round& r = history.history[i];
		writeIndent(file, indentLevel + 1);
		file << "{" << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"status\": " << (int)r.status << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		if(r.status != RoundStatus::NOT_STARTED)
			file << "\"trump\": " << (int)r.trump << "," << std::endl;
		else 
			file << "\"trump\": " << "null" << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		if(r.status != RoundStatus::NOT_STARTED)
			file << "\"bottom_card\": {\"suit\": " << (int)r.bottomCard.suit << ", \"rank\": " << (int)r.bottomCard.rank << "}," << std::endl;
		else 
			file << "\"bottom_card\": null," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"is_closed\": " << (r.isClosed ? "true" : "false") << "," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		file << "\"player_who_closed\": ";
		if(r.playerWhoClosed) file << "\"" << r.playerWhoClosed->name << "\""; else file << "null";
		file << "," << std::endl;

		// Deck
		writeIndent(file, indentLevel + 2);
		if(r.status != RoundStatus::NOT_STARTED)
			file << "\"deck_top_index\": " << r.deck.topCardIndex << "," << std::endl;
		else 
			file << "\"deck_top_index\": null," << std::endl;
		
		writeIndent(file, indentLevel + 2);
		if(r.status != RoundStatus::NOT_STARTED)
			file << "\"deck_cards\": [";
		else 
			file << "\"deck_cards\": null," << std::endl;
		
		if(r.status != RoundStatus::NOT_STARTED)
		{
			for (int j = 0; j < MAX_DECK_SIZE; j++)
			{
				file << "{\"suit\": " << (int)r.deck.cards[j].suit << ", \"rank\": " << (int)r.deck.cards[j].rank << "}";
				if (j < MAX_DECK_SIZE - 1)
					file << ", ";
			}
			file << "]," << std::endl;
		}

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

// Helper functions for parsing
void skipWhitespace(std::ifstream& file)
{
	while (file.good())
	{
		char c = file.peek();
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ',' || c == ':')
		{
			file.get();
		}
		else
		{
			break;
		}
	}
}

bool matchLiteral(std::ifstream& file, const char* str)
{
	skipWhitespace(file);
	std::streampos pos = file.tellg();
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (file.get() != str[i])
		{
			file.seekg(pos);
			return false;
		}
	}
	return true;
}

bool matchKey(std::ifstream& file, const char* key)
{
	skipWhitespace(file);
	if (file.peek() != '"') return false;
	
	std::streampos pos = file.tellg();
	if (file.get() != '"') {
		file.seekg(pos);
		return false; 
	}
	
	for (int i = 0; key[i] != '\0'; ++i)
	{
		if (file.get() != key[i])
		{
			file.seekg(pos);
			return false;
		}
	}
	
	if (file.get() != '"') {
		file.seekg(pos);
		return false;
	}
	
	return true;
}

int readInt(std::ifstream& file)
{
	skipWhitespace(file);
	int val = 0;
	file >> val;
	return val;
}

bool readBool(std::ifstream& file)
{
	skipWhitespace(file);
	if (matchLiteral(file, "true")) return true;
	if (matchLiteral(file, "false")) return false;
	return false;
}

char* readString(std::ifstream& file)
{
	skipWhitespace(file);
	if (matchLiteral(file, "null")) return nullptr;

	if (file.peek() != '"') return nullptr;
	file.get(); // consume opening quote

	char buffer[256];
	file.get(buffer, 256, '"');
	
	if (file.peek() == '"') file.get(); // consume closing quote

	char* str = new char[strLen(buffer) + 1];
	strCopy(str, buffer);
	
	return str;
}

void loadGameSettings(Game& game, std::ifstream& file)
{
	matchKey(file, "settings");
	matchLiteral(file, "{");
	
	matchKey(file, "status");
	game.status = (GameStatus)readInt(file);
	
	matchKey(file, "target_points");
	game.settings.targetPoints = readInt(file);
	
	matchKey(file, "non_trump_marriage");
	game.settings.nonTrumpMarriagePoints = readInt(file);
	
	matchKey(file, "trump_marriage");
	game.settings.trumpMarriagePoints = readInt(file);
	
	matchKey(file, "show_points");
	game.settings.showPlayerPoints = readBool(file);
	
	matchKey(file, "last_trick_bonus");
	game.settings.lastTrickBonusPoints = readBool(file);
	
	matchLiteral(file, "}");
}

void loadCard(Card& card, std::ifstream& file)
{
	matchLiteral(file, "{");
	matchKey(file, "suit");
	card.suit = (Suit)readInt(file);
	matchKey(file, "rank");
	card.rank = (Rank)readInt(file);
	matchLiteral(file, "}");
}

void loadPlayer(Player& player, std::ifstream& file)
{
	matchLiteral(file, "{");
	
	matchKey(file, "name");
	player.name = readString(file);
	
	matchKey(file, "current_points");
	player.currentPoints = readInt(file);
	
	matchKey(file, "game_points");
	player.gamePoints = readInt(file);
	
	matchKey(file, "is_leading");
	player.isLeading = readBool(file);
	
	matchKey(file, "played_this_turn");
	player.playedThisTurn = readBool(file);
	
	matchKey(file, "has_marriage");
	player.hasMarriage = readBool(file);
	
	matchKey(file, "marriage_suit");
	player.marriageSuit = (Suit)readInt(file);
	
	matchKey(file, "hand_card_count");
	player.hand.cardCount = readInt(file);
	
	matchKey(file, "hand");
	matchLiteral(file, "[");
	
	for (int i = 0; i < player.hand.cardCount; i++)
	{
		loadCard(player.hand.hand[i], file);
	}
	matchLiteral(file, "]");
	
	matchLiteral(file, "}");
}

Player* resolvePlayer(const char* name, Player& p1, Player& p2)
{
	if (name == nullptr) return nullptr;
	if (compareWords(name, p1.name) == 0) return &p1;
	if (compareWords(name, p2.name) == 0) return &p2;
	return nullptr;
}

void loadTrick(Trick& trick, std::ifstream& file, Player& p1, Player& p2)
{
	matchLiteral(file, "{");
	
	matchKey(file, "lead_card");
	if (!matchLiteral(file, "null")) {
		loadCard(trick.leadPlayerCard, file);
	}
	
	matchKey(file, "non_lead_card");
	if (!matchLiteral(file, "null")) {
		loadCard(trick.nonLeadCard, file);
	}
	
	char* nameBuffer;
	
	matchKey(file, "lead_player");
	nameBuffer = readString(file);
	trick.leadPlayer = resolvePlayer(nameBuffer, p1, p2);
	if(nameBuffer) delete nameBuffer;
	
	matchKey(file, "non_lead_player");
	nameBuffer = readString(file);
	trick.nonLeadPlayer = resolvePlayer(nameBuffer, p1, p2);
	if(nameBuffer) delete nameBuffer;
	
	matchKey(file, "winner");
	nameBuffer = readString(file);
	trick.winner = resolvePlayer(nameBuffer, p1, p2);
	if(nameBuffer) delete nameBuffer;
	
	matchLiteral(file, "}");
}

void loadRoundsHistory(Game& game, std::ifstream& file)
{
	matchKey(file, "rounds_history");
	matchLiteral(file, "{");
	
	matchKey(file, "size");
	int size = readInt(file);
	game.roundsHistory.size = size;
	
	if (game.roundsHistory.history != nullptr) {
		delete game.roundsHistory.history; 
	}
	game.roundsHistory.history = new Round[size];
	
	matchKey(file, "history");
	matchLiteral(file, "[");
	
	for (int i = 0; i < size; i++)
	{
		Round& r = game.roundsHistory.history[i];
		matchLiteral(file, "{");
		
		matchKey(file, "status");
		r.status = (RoundStatus)readInt(file);
		
		matchKey(file, "trump");
		if (!matchLiteral(file, "null")) {
			r.trump = (Suit)readInt(file);
		}
		
		matchKey(file, "bottom_card");
		if (!matchLiteral(file, "null")) {
			loadCard(r.bottomCard, file);
		}
		
		matchKey(file, "is_closed");
		r.isClosed = readBool(file);
		
		matchKey(file, "player_who_closed");
		char* closerName = readString(file);
		r.playerWhoClosed = resolvePlayer(closerName, game.player1, game.player2);
		if(closerName) delete closerName;
		
		matchKey(file, "deck_top_index");
		if (!matchLiteral(file, "null")){
			r.deck.topCardIndex = readInt(file);
		}
		
		matchKey(file, "deck_cards");
		if (!matchLiteral(file, "null")) {
			matchLiteral(file, "[");
			for (int j = 0; j < MAX_DECK_SIZE; j++)
			{
				loadCard(r.deck.cards[j], file);
			}
			matchLiteral(file, "]");
		}
		
		matchKey(file, "current_trick");
		loadTrick(r.currentTrick, file, game.player1, game.player2);
		
		matchKey(file, "last_trick");
		loadTrick(r.lastTrick, file, game.player1, game.player2);
		
		matchKey(file, "conclusion");
		matchLiteral(file, "{");
		
		matchKey(file, "winner");
		char* winnerName = readString(file);
		r.conclusion.winner = resolvePlayer(winnerName, game.player1, game.player2);
		if(winnerName) delete winnerName;
		
		matchKey(file, "loser");
		char* loserName = readString(file);
		r.conclusion.loser = resolvePlayer(loserName, game.player1, game.player2);
		if(loserName) delete loserName;
		
		matchKey(file, "accumulated_points");
		r.conclusion.accumulatedPoints = readInt(file);
		
		matchKey(file, "winner_points");
		r.conclusion.winnerPoints = readInt(file);
		
		matchKey(file, "loser_points");
		r.conclusion.loserPoints = readInt(file);
		
		matchLiteral(file, "}"); // End conclusion
		
		matchLiteral(file, "}"); // End round
	}
	
	matchLiteral(file, "]"); // End history array
	
	matchLiteral(file, "}"); // End rounds_history object
}

bool loadGame(Game& game, const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return false;
	}

	// Root object
	if (!matchLiteral(file, "{")) return false;

	loadGameSettings(game, file);
	
	matchKey(file, "player1");
	loadPlayer(game.player1, file);
	
	matchKey(file, "player2");
	loadPlayer(game.player2, file);
	
	loadRoundsHistory(game, file);
	
	matchLiteral(file, "}");

	return true;
}