#include "game.h"
#include "utils.h"
#include "player.h"

GameSettings initGameSettings()
{
    GameSettings newGameSettings = {};

    return newGameSettings;
}

Game initGame(const GameSettings& settings)
{
    Player player1 = initPlayer("Player1"), player2 = initPlayer("Player2");

    Round* history = new Round[settings.targetPoints];
    RoundsHistory roundsHistory = { history };
    Game newGame = { player1, player2, settings, roundsHistory };

    return newGame;
}

void printRoundsHistory(const Game& game)
{
    for (size_t i = 0; i < game.roundsHistory.size; i++)
    {
        Round r = game.roundsHistory.history[i];
        if (r.state == RoundState::ENDED)
        {
            std::cout << "Round " << i + 1 << ": ";
            std::cout << "Winner - "
                << r.conclusion.winner->name
                << "(+" << r.conclusion.accumulatedPoints << ") |";

            std::cout << r.conclusion.winner->name << ": "
                << r.conclusion.winnerPoints << "points | ";

            std::cout << r.conclusion.loser->name << ": "
                << r.conclusion.loserPoints << "points | ";
        }
        else
        {
            std::cout << "Round " << i + 1 << ": Ongoing";
        }
    }
}