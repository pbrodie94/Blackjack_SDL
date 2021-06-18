#include "PlayingCard.h"

PlayingCard::PlayingCard()
{
	this->cardNumber = 1;
	this->cardSuit = 1;
}

PlayingCard::PlayingCard(int num, int suit)
{
	this->cardNumber = num;
	this->cardSuit = suit;
}
