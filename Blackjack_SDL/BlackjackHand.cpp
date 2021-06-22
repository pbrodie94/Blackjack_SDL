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
	SDL_DestroyTexture(cardTexture);
	SDL_DestroyTexture(cardFaceTexture);
	SDL_DestroyTexture(cardBackTexture);

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

		break;

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

void BlackjackHand::UnHideCards()
{
	for (int i = 0; i < cardSprites.size(); i++)
	{
		if (cardSprites[i]->hidden)
		{
			cardSprites[i]->UnHide(cardTexture, cardFaceTexture, cards[i].GetCardValue(), cards[i].GetCardSuit());
		}
	}
}

void BlackjackHand::SplitHand(BlackjackHand& otherHand)
{
	if (!canSplit)
		return;

	PlayingCard card = cards[1];
	PlayingCard card2 = cards[0];

	ResetHand();

	AddCard(card);
	otherHand.AddCard(card2);
}

void BlackjackHand::DisplayHand()
{
	if (numCards <= 0)
		return;

	//Access the cards in hand and draw them to screen with the cardsprite objects
	int offset = 20 * numCards - 1;

	if (!cards[numCards - 1].hidden)
	{
		cardSprites.push_back(new CardSprite(cards[numCards - 1].GetCardValue(), cards[numCards - 1].GetCardSuit(), startXPos - offset, startYPos, cardTexture, cardFaceTexture, renderer));
	}
	else {
		cardSprites.push_back(new CardSprite(startXPos - offset, startYPos, cardBackTexture, renderer));
	}
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
	for (CardSprite* cs : cardSprites)
	{
		delete (cs);
		cs = nullptr;
	}

	cardSprites.clear();
}
