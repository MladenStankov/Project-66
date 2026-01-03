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
    Player player1 = initPlayer("Player1");
    Player player2 = initPlayer("Player2");

    Round* history = new Round[settings.targetPoints];
    RoundsHistory roundsHistory = { history };
    GameStatus status = GameStatus::NOT_STARTED;

    Game newGame = { player1, player2, settings, roundsHistory, status };

    return newGame;
}

void startGame(Game& game)
{
    changeGameStatus(game, GameStatus::IN_BETWEEN_ROUNDS);
    game.roundsHistory.history = new Round[game.settings.targetPoints];
    game.roundsHistory.size = 1;
}

void printRoundsHistory(const Game& game)
{
    for (size_t i = 0; i < game.roundsHistory.size; i++)
    {
        Round r = game.roundsHistory.history[i];
        if (r.status == RoundStatus::ENDED)
        {
            std::cout << "Round " << i + 1 << ": " << std::endl;
            std::cout << "Winner - "
                << r.conclusion.winner->name
                << " (+" << r.conclusion.accumulatedPoints << ")" << std::endl;;

            std::cout << r.conclusion.winner->name << ": "
                << r.conclusion.winnerPoints << " points" << std::endl;

            std::cout << r.conclusion.loser->name << ": "
                << r.conclusion.loserPoints << " points " << std::endl;

            printSeparatingLine();
        }
        else
        {
            std::cout << "Round " << i + 1 << ": Not started" << std::endl;
        }
    }
}

Player& getLeadingPlayer(Game& game)
{
    if (game.player1.isLeading == true) return game.player1;
    else return game.player2;
}

Player& getNonLeadingPlayer(Game& game)
{
    if (game.player1.isLeading == false) return game.player1;
    else return game.player2;
}

Player& getThePlayerThatIsOnTurn(Game& game)
{
    Player& leadingPlayer = getLeadingPlayer(game);
    if (leadingPlayer.playedThisTurn == false) return leadingPlayer;

    Player& nonLeadingPlayer = getNonLeadingPlayer(game);
    if (nonLeadingPlayer.playedThisTurn == false) return nonLeadingPlayer;
}

void changeGameStatus(Game& game, const GameStatus& status)
{
    game.status = status;
}

Round& getCurrentRound(Game& game)
{
    size_t roundHistorySize = game.roundsHistory.size;
    return game.roundsHistory.history[roundHistorySize - 1];
}

void printGameInfo(const Game& game)
{
    std::cout << "Current Round: #" << game.roundsHistory.size << std::endl;

    std::cout << game.player1.name << " round wins: " << game.player1.overallPoints << std::endl;
    std::cout << game.player2.name << " round wins: " << game.player2.overallPoints << std::endl;
}