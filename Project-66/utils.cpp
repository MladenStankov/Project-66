#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void toLowercase(char& c)
{
    if (c >= 'A' && c <= 'Z')c = 'a' + (c - 'A');
}

unsigned int generateRandomNumber(unsigned int from, unsigned int to)
{
	if (to == 0) return 0;

	return (rand() % to) + from;
}

void swapCards(Card& c1, Card& c2)
{
	Card temp = c1;
	c1 = c2;
	c2 = temp;
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool compareWords(const char* str1, const char* str2)
{
	if (!str1 || !str2) return false;

	while ((*str1 != '\0' && !isWhitespace(*str1)) && (*str2 != '\0' && !isWhitespace(*str2))
        && *str1++ == *str2++);

	if ((*str1 == '\0' || isWhitespace(*str1)) && (*str2 == '\0' || isWhitespace(*str2)))
        return true;
	else return false;
}

void cleanString(char* str) {
    if (!str) return;

    int readIndex = 0;
    int writeIndex = 0;

    while (str[readIndex] != '\0' && isWhitespace(str[readIndex])) {
        readIndex++;
    }

    while (str[readIndex] != '\0') {
        if (!isWhitespace(str[readIndex])) {
            toLowercase(str[readIndex]);
            str[writeIndex++] = str[readIndex];
        }
        else {
            if (writeIndex > 0 && !isWhitespace(str[writeIndex - 1])) {
                str[writeIndex++] = ' ';
            }
        }
        readIndex++;
    }
    if (writeIndex > 0 && isWhitespace(str[writeIndex - 1])) {
        writeIndex--;
    }

    str[writeIndex] = '\0';
}

char* getNextWord(char* str)
{
    if (isWhitespace(*str))
    {
        while (isWhitespace(*str))str++;
        return str;
    }
    else
    {
        while (!isWhitespace(*str))str++;
        while (isWhitespace(*str))str++;
        return str;
    }
}

int customAtoi(char* str)
{
	int result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return result;
}

void printSeparatingLine()
{
	std::cout << "--------------------------------" << std::endl;
}
