#include "PlayingCard.h"

PlayingCard::PlayingCard(int width, int height, SDL_Renderer* renderer)
{ 
	this->cardSprite = new CardSprite(width, height, renderer);
}

PlayingCard::PlayingCard(int num, int suit, int width, int height, SDL_Renderer* renderer)
{
	this->cardNumber = num;
	this->cardSuit = suit;

	this->cardSprite = new CardSprite(num, suit, width, height, renderer);
}

void PlayingCard::Draw()
{
	this->cardSprite->Draw();
}