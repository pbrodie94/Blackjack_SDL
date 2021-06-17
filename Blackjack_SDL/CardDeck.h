#pragma once

#include <vector>
#include <random>

#include "PlayingCard.h"

class CardDeck
{
private:
	void CreateDeck();
	void ShuffleDeck();

	int numDecks;
	vector<PlayingCard> deck;

public:

	CardDeck();
	CardDeck(int numDecks);

	PlayingCard DrawCard();
	void DestroyDeck();

};

