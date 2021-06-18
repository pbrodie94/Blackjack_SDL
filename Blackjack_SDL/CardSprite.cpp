#include "CardSprite.h"

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer) 
{
	this->SetWidth(24);
	this->SetHeight(32);
}

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(24);
	this->SetHeight(32);

	//Set the card to be the inputted value
	this->cardNumber = new Sprite(cardFace, xPos, yPos, renderer);
	this->cardSuit = new Sprite(cardFace, xPos, yPos, renderer);
}

CardSprite::CardSprite(int num, int suit, int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(24);
	this->SetHeight(32);

	//Set the card to be the inputted value
	this->cardNumber = new Sprite(cardFace, xPos, yPos, renderer);
	this->cardSuit = new Sprite(cardFace, xPos, yPos, renderer);
}

void CardSprite::Draw()
{
	Sprite::Draw();

	//cardSuit->Draw();
	//cardNumber->Draw();
}