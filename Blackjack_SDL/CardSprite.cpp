#include "CardSprite.h"

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer) 
{
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetRectWidth(width);
	this->SetRectHeight(height);

	hidden = true;
}

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetRectWidth(width);
	this->SetRectHeight(height);

	//Set the card to be the inputted value
	InitFaceSprites(cardFace, 1, 4);
}

CardSprite::CardSprite(int num, int suit, int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetRectWidth(width);
	this->SetRectHeight(height);

	//Set the card to be the inputted value
	InitFaceSprites(cardFace, num, suit);
}

CardSprite::~CardSprite()
{
	if (cardNumber != nullptr)
	{
		delete (cardNumber);
	}

	if (cardNumber2 != nullptr)
	{
		delete (cardNumber2);
	}

	if (cardSuit != nullptr)
	{
		delete (cardSuit);
	}

	if (cardSuit2 != nullptr)
	{
		delete (cardSuit2);
	}
}

void CardSprite::InitFacePositions(int xy)
{
	cardNumer1Pos.x = width - xy;
	cardNumer1Pos.y = xy;

	cardSuit1Pos.x = width - xy;
	cardSuit1Pos.y = xy * 2;

	cardNumer2Pos.x = xy;
	cardNumer2Pos.y = height - xy;

	cardSuit2Pos.x = xy * 2;
	cardSuit2Pos.y = height - xy;
}

void CardSprite::UnHide(SDL_Texture* card, SDL_Texture* cardFace, int num, int suit)
{
	SetTexture(card);
	InitFaceSprites(cardFace, num, suit);

	hidden = false;
}

void CardSprite::InitFaceSprites(SDL_Texture* cardFace, int num, int suit)
{
	int xy = 12;
	InitFacePositions(xy);

	cardNumber = new Sprite(cardFace, this->xPosition + cardNumer1Pos.x, this->yPosition + cardNumer1Pos.y, renderer);
	cardNumber2 = new Sprite(cardFace, this->xPosition + cardNumer2Pos.x, this->yPosition + cardNumer2Pos.y, renderer);
	cardSuit = new Sprite(cardFace, this->xPosition + cardSuit1Pos.x, this->yPosition + cardSuit1Pos.y, renderer);
	cardSuit2 = new Sprite(cardFace, this->xPosition + cardSuit2Pos.x, this->yPosition + cardSuit2Pos.y, renderer);

	cardNumber->SetWidth(6);
	cardNumber->SetHeight(6);
	cardSuit->SetWidth(6);
	cardSuit->SetHeight(6);
	cardNumber2->SetWidth(6);
	cardNumber2->SetHeight(6);
	cardSuit2->SetWidth(6);
	cardSuit2->SetHeight(6);

	cardNumber->SetRectWidth(xy);
	cardNumber->SetRectHeight(xy);
	cardSuit->SetRectWidth(xy);
	cardSuit->SetRectHeight(xy);
	cardNumber2->SetRectWidth(xy);
	cardNumber2->SetRectHeight(xy);
	cardSuit2->SetRectWidth(xy);
	cardSuit2->SetRectHeight(xy);

	if (suit > 2)
	{
		//Red card
		cardNumber->SetRow(1);
		cardNumber2->SetRow(1);
		cardSuit->SetRow(1);
		cardSuit->SetRow(1);
	}
	else {
		//Black card
		cardNumber->SetRow(0);
		cardNumber2->SetRow(0);
		cardSuit->SetRow(0);
		cardSuit->SetRow(0);
	}

	cardNumber->SetFrame(num - 1);
	cardNumber2->SetFrame(num - 1);

	cardSuit->SetFrame(suit + 13);
	cardSuit2->SetFrame(suit + 13);
}

void CardSprite::Draw()
{
	Sprite::Draw();

	if (!hidden)
	{
		cardSuit->Draw();
		cardNumber->Draw();
	}
}