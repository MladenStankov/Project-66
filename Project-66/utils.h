#pragma once
#include "card.h"

unsigned int generateRandomNumber(unsigned int from, unsigned int to);

void swapCards(Card& c1, Card& c2);

// Compares two strings until it reaches null ptr or a whitespace
bool compareWords(const char* str1, const char* str2);

// Removes all unnecessary whitespaces from a string and makes all alpha characters lowercase
void cleanString(char* str);

char* getNextWord(char* str);