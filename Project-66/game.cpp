#include "game.h"
#include "utils.h"

void initGame(Game& game)
{
    size_t index = 0;
    for (size_t suit = 0; suit < 4; ++suit) {
        for (size_t rank = 0; rank < 6; rank++) {
            game.deck[index].suit = (Suit)suit;
            game.deck[index].rank = (Rank)rank;
            index++;
        }
    }

    game.topCardIndex = 0;
    game.isStockClosed = false;

    shuffleDeck(game.deck);
    initialDealToPlayers(game.deck, game.topCardIndex, game.player1, game.player2);
    game.trumpCard = game.deck[game.topCardIndex++];
}

void shuffleDeck(Card deck[MAX_DECK_SIZE])
{
    for (size_t i = MAX_DECK_SIZE - 1; i >= 1; --i)
    {
        size_t j = generateRandomNumber(0, i);
        swapCards(deck[i], deck[j]);
    }
}

void initialDealToPlayers(Card deck[MAX_DECK_SIZE], size_t& topCardIndex, Player& player1, Player& player2)
{
    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(player1, deck[topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(player2, deck[topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(player1, deck[topCardIndex++]);
    }

    for (size_t i = 0; i < 3; ++i)
    {
        addCardToHand(player2, deck[topCardIndex++]);
    }
}