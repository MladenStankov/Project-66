#pragma once

// Constants
constexpr char CLUBS_SYMBOL[] = "\xE2\x99\xA3";
constexpr char DIAMONDS_SYMBOL[] = "\xE2\x99\xA6";
constexpr char HEARTS_SYMBOL[] = "\xE2\x99\xA5";
constexpr char SPADES_SYMBOL[] = "\xE2\x99\xA0";

enum class Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
};

enum class Rank {
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

struct Card {
    Suit suit;
    Rank rank;
};

const char* getRankString(Rank);
const char* getSuitString(Suit);

// Prints out to the console the suit and rank of the Card
void printCard(Card card);

// Returns 1 if the first Card wins. Otherwise returns -1 if the second Card wins.
int compareCards(Card c1, Card c2, Suit trump);