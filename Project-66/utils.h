/**
*  
* Solution to course project # 66
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Mladen Stankov
* @idnumber 3MI0600676
* @compiler Visual Studio
*
* <Header file for utility functions>
*
*/
#pragma once
#include "card.h"
#include "player.h"

unsigned int generateRandomNumber(unsigned int from, unsigned int to);

void swapCards(Card& c1, Card& c2);

// Compares two strings until it reaches null ptr or a whitespace
bool compareWords(const char* str1, const char* str2);

void strCopy(char* dest, const char* src);

// Removes all unnecessary whitespaces from a string and makes all alpha characters lowercase
void cleanString(char* str);

char* getNextWord(char* str);

int customAtoi(char* str);
void printSeparatingLine();
unsigned int strLen(const char* str);