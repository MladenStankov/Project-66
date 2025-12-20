#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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