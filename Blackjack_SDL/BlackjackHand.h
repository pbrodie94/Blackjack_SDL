#pragma once

#include <vector>

#include "Definitions.h"
#include "PlayingCard.h"

class BlackjackHand
{
private:
	void DisplayHand();

	vector<PlayingCard> cards;

	int numAces;
	int numCards;

	int startXPos;
	int startYPos;
	
	bool bust;
	bool blackJack;
	bool canSplit;

	vector<CardSprite*> cardSprites;
	SDL_Renderer* renderer;
	SDL_Texture* cardTexture;
	SDL_Texture* cardFaceTexture;
	SDL_Texture* cardBackTexture;

public:
	BlackjackHand() {}
	BlackjackHand(int xPos, int yPos, SDL_Renderer* renderer, SDL_Texture* card, SDL_Texture* cardBack, SDL_Texture* cardFace);
	~BlackjackHand();

	void AddCard(PlayingCard card);
	void SplitHand(BlackjackHand& otherHand);
	void UnHideCards();
	void DrawHand();
	void ResetHand();

	int GetNumCards() { return numCards; }

	bool GetIsBlackjack() { return blackJack; }
	bool GetIsBust() { return bust; }
	bool GetCanSplit() { return canSplit; }

	bool stand;
	int handValue;
};

