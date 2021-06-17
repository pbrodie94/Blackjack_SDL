#pragma once

#include <vector>

#include "Definitions.h"
#include "PlayingCard.h"

class BlackjackHand
{
private:
	vector<PlayingCard> cards;

	int numAces;
	int numCards;

	int startXPos;
	int startYPos;

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
	void DisplayHand();
	void ResetHand();

	int GetNumCards() { return numCards; }

	bool stand;
	bool bust;
	bool blackJack;
	bool canSplit;
	int handValue;
};

