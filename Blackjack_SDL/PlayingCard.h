#pragma once

#include "CardSprite.h"

class PlayingCard
{
private:
	int cardNumber; //The number on the card from 1 (Ace) to 13 (King)
	int cardSuit; //Numeric value to represent the suit (Spades, Clubs, Hearts, Diamonds)

	CardSprite* cardSprite;

public:

	PlayingCard(int width, int height, SDL_Renderer* renderer); //Initializes the card as Ace of Spades
	PlayingCard(int num, int suit, int width, int height, SDL_Renderer* renderer); //Initializes the card's value

	void Draw();

	int GetCardValue(); //Returns the card's number
};

