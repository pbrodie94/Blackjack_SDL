#include "CardSprite.h"

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer) 
{
	this->SetWidth(width);
	this->SetHeight(height);

	hidden = true;

	InitFacePositions();
}

CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(width);
	this->SetHeight(height);

	//Set the card to be the inputted value
	InitFacePositions();
	InitFaceSprites(cardFace, 1, 1);
}

CardSprite::CardSprite(int num, int suit, int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer)
	: Sprite(texture, xPos, yPos, renderer)
{
	this->SetWidth(width);
	this->SetHeight(height);

	//Set the card to be the inputted value
	InitFacePositions();
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

void CardSprite::InitFacePositions()
{
	cardNumer1Pos.x = width - 5;
	cardNumer1Pos.y = 5;

	cardSuit1Pos.x = width - 5;
	cardSuit1Pos.y = 25;

	cardNumer2Pos.x = 5;
	cardNumer2Pos.y = height - 7;

	cardSuit2Pos.x = 25;
	cardSuit2Pos.y = height - 7;
}

void CardSprite::UnHide(SDL_Texture* card, SDL_Texture* cardFace, int num, int suit)
{
	SetTexture(card);
	InitFaceSprites(cardFace, num, suit);

	hidden = false;

}

void CardSprite::InitFaceSprites(SDL_Texture* cardFace, int num, int suit)
{
	cardNumber = new Sprite(cardFace, this->xPosition + cardNumer1Pos.x, this->yPosition + cardNumer1Pos.y, renderer);
	cardNumber2 = new Sprite(cardFace, this->xPosition + cardNumer2Pos.x, this->yPosition + cardNumer2Pos.y, renderer);
	cardSuit = new Sprite(cardFace, this->xPosition + cardSuit1Pos.x, this->yPosition + cardSuit1Pos.y, renderer);
	cardSuit2 = new Sprite(cardFace, this->xPosition + cardSuit2Pos.x, this->yPosition + cardSuit2Pos.y, renderer);

	int xy = 12;

	cardNumber->SetWidth(xy);
	cardNumber->SetHeight(xy);
	cardSuit->SetWidth(xy);
	cardSuit->SetHeight(xy);
	cardNumber2->SetWidth(xy);
	cardNumber2->SetHeight(xy);
	cardSuit2->SetWidth(xy);
	cardSuit2->SetHeight(xy);

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