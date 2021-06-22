#pragma once

#include <vector>
#include <random>

#include "PlayingCard.h"

class CardDeck
{
private:
	void ShuffleDeck();

	int numDecks;
	vector<PlayingCard> deck;

public:

	CardDeck();
	CardDeck(int numDecks);

	void CreateDeck();
	void SetNumberDecks(int decks);
	PlayingCard DrawCard();
	void DestroyDeck();

};

