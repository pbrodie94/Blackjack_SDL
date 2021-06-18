#include "BlackjackHand.h"

BlackjackHand::BlackjackHand(int xPos, int yPos, SDL_Renderer* renderer, SDL_Texture* card, SDL_Texture* cardBack, SDL_Texture* cardFace)
{
	this->startXPos = xPos;
	this->startYPos = yPos;

	this->renderer = renderer;
	this->cardTexture = card;
	this->cardFaceTexture = cardFace;
	this->cardBackTexture = cardBack;

	numCards = 0;
	handValue = 0;
	stand = false;
	blackJack = false;
	bust = false;
	canSplit = false;
}

BlackjackHand::~BlackjackHand()
{
	delete renderer;
	delete cardTexture;
	delete cardFaceTexture;
	delete cardBackTexture;

	ResetHand();
}

void BlackjackHand::AddCard(PlayingCard card)
{
	cards.push_back(card);
	numCards++;
	
	int cardNum = card.GetCardValue();

	switch (cardNum)
	{
	case 1:
		//Ace
		numAces++;

		handValue += 11;

		if (handValue > 21)
		{
			handValue -= 10;
			numAces--;
		}
		break;

	case 11:

	case 12:

	case 13:

		handValue += 10;

	default:

		handValue += cardNum;

		break;
	}

	if (handValue > 21)
	{
		bust = true;
		stand = true;

		while (numAces > 0)
		{
			handValue -= 10;
			numAces--;

			if (handValue < 21)
			{
				bust = false;
				stand = false;
				break;
			}
		}
	}

	canSplit = false;

	if (numCards == 2)
	{
		if (cards[0].GetCardValue() == cards[1].GetCardValue())
		{
			canSplit = true;
		}

		if (handValue == 21)
		{
			blackJack = true;
			stand = true;
		}
	}

	DisplayHand();
}

void BlackjackHand::SplitHand(BlackjackHand& otherHand)
{
	if (!canSplit)
		return;

	otherHand.AddCard(cards.back());
	cards.pop_back();
}

void BlackjackHand::DisplayHand()
{
	if (numCards <= 0)
		return;

	//Access the cards in hand and draw them to screen with the cardsprite objects
	int offset = 10 * numCards - 1;

	if (!cards[numCards - 1].hidden)
	{
		cardSprites.push_back(new CardSprite(cards[numCards - 1].GetCardValue(), cards[numCards - 1].GetCardSuit(), startXPos + offset, startYPos, cardTexture, cardFaceTexture, renderer));
	}
	else {
		cardSprites.push_back(new CardSprite(startXPos + offset, startYPos, cardBackTexture, renderer));
	}

	//cardSprites.push_back(newSprite);
	

}

void BlackjackHand::DrawHand()
{
	if (numCards <= 0)
		return;

	for (int i = 0; i < cardSprites.size(); i++)
	{
		if (cardSprites[i]->visible && cardSprites[i] != nullptr)
		{
			cardSprites[i]->Draw();
		}
	}
}

void BlackjackHand::ResetHand()
{
	numCards = 0;
	handValue = 0;
	stand = false;
	blackJack = false;
	bust = false;
	canSplit = false;

	cards.clear();

	//delete the pointers
	for (int i = 0; i < cardSprites.size(); i++)
	{
		delete (cardSprites[i]);
		cardSprites[i] = nullptr;
	}

	cardSprites.clear();
}
