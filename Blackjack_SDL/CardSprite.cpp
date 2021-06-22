#include "CardSprite.h"

/*CardSprite::CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer)
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
}*/

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

	cardNumber->SetWidth(6);
	cardNumber->SetHeight(6);
	cardSuit->SetWidth(6);
	cardSuit->SetHeight(6);
	cardNumber2->SetWidth(6);
	cardNumber2->SetHeight(6);
	cardSuit2->SetWidth(6);
	cardSuit2->SetHeight(6);

	cardNumber->SetRectWidth(nsSize);
	cardNumber->SetRectHeight(nsSize);
	cardSuit->SetRectWidth(nsSize);
	cardSuit->SetRectHeight(nsSize);
	cardNumber2->SetRectWidth(nsSize);
	cardNumber2->SetRectHeight(nsSize);
	cardSuit2->SetRectWidth(nsSize);
	cardSuit2->SetRectHeight(nsSize);

	cardNumer1Pos.x = width - nsSize;
	cardNumer1Pos.y = nsSize;

	cardSuit1Pos.x = width - nsSize;
	cardSuit1Pos.y = nsSize * 2;

	cardNumer2Pos.x = nsSize;
	cardNumer2Pos.y = height - nsSize;

	cardSuit2Pos.x = nsSize * 2;
	cardSuit2Pos.y = height - nsSize;
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
	cardNumber->visible = hidden;
	cardNumber2->visible = hidden;
	cardSuit->visible = hidden;
	cardSuit2->visible = hidden;
	this->SetXPosition(x);
	this->SetYPosition(y);
	
	//Set card number and suit
	if (!hidden)
	{
		this->SetTexture(card);

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

void CardSprite::UnHide(int num, int suit)
{
	hidden = false;
	SetCard(num, suit, this->xPosition, this->yPosition, hidden);
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