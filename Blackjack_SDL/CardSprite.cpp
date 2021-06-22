#include "CardSprite.h"

CardSprite::CardSprite(SDL_Texture* card, SDL_Texture* cardFace, SDL_Texture* cardBack, SDL_Renderer* renderer)
	: Sprite(card, 0, 0, renderer)
{
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetRectWidth(width);
	this->SetRectHeight(height);

	this->card = card;
	this->cardFace = cardFace;
	this->cardBack = cardBack;

	cardNumber = new Sprite(cardFace, 0, 0, renderer);
	cardNumber2 = new Sprite(cardFace, 0, 0, renderer);
	cardSuit = new Sprite(cardFace, 0, 0, renderer);
	cardSuit2 = new Sprite(cardFace, 0, 0, renderer);

	cardNumber->SetWidth(5);
	cardNumber->SetHeight(5);
	cardSuit->SetWidth(5);
	cardSuit->SetHeight(5);
	cardNumber2->SetWidth(5);
	cardNumber2->SetHeight(5);
	cardSuit2->SetWidth(5);
	cardSuit2->SetHeight(5);

	cardNumber->SetRectWidth(nsSize);
	cardNumber->SetRectHeight(nsSize);
	cardSuit->SetRectWidth(nsSize);
	cardSuit->SetRectHeight(nsSize);
	cardNumber2->SetRectWidth(nsSize);
	cardNumber2->SetRectHeight(nsSize);
	cardSuit2->SetRectWidth(nsSize);
	cardSuit2->SetRectHeight(nsSize);
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

void CardSprite::SetCard(int num, int suit, int x, int y, bool hidden)
{
	this->visible = true;
	cardNumber->visible = !hidden;
	cardNumber2->visible = !hidden;
	cardSuit->visible = !hidden;
	cardSuit2->visible = !hidden;
	this->SetXPosition(x);
	this->SetYPosition(y);

	//Set card number and suit
	if (!hidden)
	{
		this->SetTexture(card);
		SetFacePositions();

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
	else {
		this->SetTexture(cardBack);
	}
}

void CardSprite::SetFacePositions()
{
	cardNumer1Pos.x = xPosition + (width - nsSize);
	cardNumer1Pos.y = yPosition;

	cardSuit1Pos.x = xPosition + (width - nsSize);
	cardSuit1Pos.y = yPosition + (nsSize + 3);

	cardNumer2Pos.x = xPosition;
	cardNumer2Pos.y = yPosition + (height - nsSize);

	cardSuit2Pos.x = xPosition + (nsSize + 3);
	cardSuit2Pos.y = yPosition + (height - nsSize);

	cardNumber->SetXPosition(cardNumer1Pos.x);
	cardNumber->SetYPosition(cardNumer1Pos.y);

	cardNumber2->SetXPosition(cardNumer2Pos.x);
	cardNumber2->SetYPosition(cardNumer2Pos.y);

	cardSuit->SetXPosition(cardSuit1Pos.x);
	cardSuit->SetYPosition(cardSuit1Pos.y);

	cardSuit2->SetXPosition(cardSuit2Pos.x);
	cardSuit2->SetYPosition(cardSuit2Pos.y);
}

void CardSprite::UnHide(int num, int suit)
{
	hidden = false;
	SetCard(num, suit, this->xPosition, this->yPosition, false);
}

void CardSprite::Draw()
{
	if (visible)
	{
		Sprite::Draw();

		if (!hidden)
		{
			cardSuit->Draw();
			cardSuit2->Draw();
			cardNumber->Draw();
			cardNumber2->Draw();
		}
	}
}