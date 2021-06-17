#include "CardSprite.h"

CardSprite::CardSprite(int width, int height, SDL_Renderer* renderer)
	: Sprite("Images/Card_Face.png", width, height, renderer) 
{
	//Set the card to be ace of spades
	this->cardNumber = new Sprite("Images/Card_SuitNums.png", width, height, renderer);
	this->cardSuit = new Sprite("Images/Card_SuitNums.png", width, height, renderer);
}

CardSprite::CardSprite(int num, int suit, int width, int height, SDL_Renderer* renderer)
	: Sprite("Images/Card_Face.png", width, height, renderer) 
{
	//Set the card to be the inputted value
	this->cardNumber = new Sprite("Images/Card_SuitNums.png", width, height, renderer);
	this->cardSuit = new Sprite("Images/Card_SuitNums.png", width, height, renderer);
}

void CardSprite::Draw()
{
	Sprite::Draw();

	cardSuit->Draw();
	cardNumber->Draw();
}