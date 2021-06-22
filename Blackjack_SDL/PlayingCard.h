#pragma once

#include "CardSprite.h"

class PlayingCard
{
private:
	int cardNumber; //The number on the card from 1 (Ace) to 13 (King)
	int cardSuit; //Numeric value to represent the suit (Spades, Clubs, Hearts, Diamonds)

public:

	PlayingCard(); //Initializes the card as Ace of Spades
	PlayingCard(int num, int suit); //Initializes the card's value

	int GetCardValue() { return cardNumber; } //Returns the card's number
	int GetCardSuit() { return cardSuit; }
	bool hidden;
};

