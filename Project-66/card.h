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
* <Header file for Card Enums and Structs>
*
*/
#pragma once

// Constants
constexpr char CLUBS_SYMBOL[] = "\xE2\x99\xA3";
constexpr char DIAMONDS_SYMBOL[] = "\xE2\x99\xA6";
constexpr char HEARTS_SYMBOL[] = "\xE2\x99\xA5";
constexpr char SPADES_SYMBOL[] = "\xE2\x99\xA0";

constexpr unsigned int TOTAL_SUITS = 4;
constexpr unsigned int TOTAL_RANKS = 6;

// Playing cards French-Suit
enum class Suit {
    CLUBS=1,
    DIAMONDS=2,
    HEARTS=3,
    SPADES=4,
};

// Eligible card ranks for game 66
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

// Returns the string value of the Rank
const char* getRankString(const Rank&);

// Returns the string Value of the Suit
const char* getSuitString(const Suit&);

// Prints out to the console the suit and rank of the Card
void printCard(const Card& card);

// Returns whether the first Card beats the second Card
bool beats(const Card& c1, const Card& c2, const Suit& trump);

// Returns the value of the card (points)
unsigned int getCardValue(const Card& card);