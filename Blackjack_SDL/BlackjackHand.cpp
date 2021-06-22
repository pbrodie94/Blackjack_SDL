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

	for (int i = 0; i < cardSprites.size(); i++)
	{
		if (cardSprites[i] != nullptr)
		{
			delete cardSprites[i];
		}
	}

	cardSprites.clear();
}

void BlackjackHand::AddCard(PlayingCard card)
{
	cards.push_back(card);
	numCards++;
	
	if (!card.hidden)
	{
		handValue += GetCardValue(card.GetCardValue());
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
	for (int i = 0; i < numCards; i++)
	{
		if (cards[i].hidden)
		{
			cardSprites[i]->UnHide(cards[i].GetCardValue(), cards[i].GetCardSuit());
			handValue += GetCardValue(cards[i].GetCardValue());
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

	if (cardSprites.size() < numCards)
	{
		cardSprites.push_back(new CardSprite(cardTexture, cardFaceTexture, cardBackTexture, renderer));
	}

	cardSprites[numCards - 1]->SetCard(cards[numCards - 1].GetCardValue(), cards[numCards - 1].GetCardSuit(), startXPos - offset, startYPos, cards[numCards - 1].hidden);
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

	//make card sprites invisible
	for (int i = 0; i < cardSprites.size(); i++)
	{
		cardSprites[i]->visible = false;
	}
}

int BlackjackHand::GetCardValue(int cardValue)
{
	int value = 0;

	switch (cardValue)
	{
	case 1:
		//Ace
		numAces++;

		value = 11;

		break;

	case 11:

	case 12:

	case 13:

		value = 10;

		break;

	default:

		value = cardValue;

		break;
	}

	return value;
}
