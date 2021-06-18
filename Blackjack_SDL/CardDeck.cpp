#include "CardDeck.h"

CardDeck::CardDeck()
{
	this->numDecks = 1;

	CreateDeck();
}

CardDeck::CardDeck(int numDecks)
{
	this->numDecks = numDecks;

	CreateDeck();
}

void CardDeck::SetNumberDecks(int decks)
{
	if (decks > 0 && decks <= 8)
	{
		this->numDecks = decks;
	}
}

void CardDeck::CreateDeck()
{
	if (deck.size() > 0)
	{
		DestroyDeck();
	}

	//Loop through the number of decks
	for (int i = 0; i < numDecks; i++)
	{
		int suit = 1;
		int number = 1;

		//Loop through 52 for number of cards in the deck
		for (int j = 0; j < 52; j++)
		{
			//Loop through 1 to 13 to set the value of cards in a suit
			if (number <= 13)
			{
				//Add the cards to the deck with the number and suit values
				deck.push_back(PlayingCard(number, suit));

				//Increase the card value number
				number++;
			}
			else {
				//Once the value is above 13, set the number back to 1
				number = 1;

				//Increase the suit value
				suit++;
			}

		}
	}

	//Once the deck has been fully created, call the shuffle method
	ShuffleDeck();
}

PlayingCard CardDeck::DrawCard()
{
	//Card split debug code

	//PlayingCard card = PlayingCard(2, 2);
	//return card;

	PlayingCard card; //Create a black card object

	//If there's no cards left in the deck
	if (deck.size() < 1)
	{
		//Destroy the deck
		DestroyDeck();

		//Then recreate the deck
		CreateDeck();
	}

	//Draw the card from the back of the deck
	card = deck[deck.size() - 1];

	//Then erase the card
	deck.erase(deck.end() - 1);

	//Then return the card to the point that it was called
	return card;
}

void CardDeck::ShuffleDeck()
{
	//Set the randomize seed
	srand(time(NULL));
	//Randomly shuffle the deck
	random_shuffle(deck.begin(), deck.end());
}

void CardDeck::DestroyDeck()
{
	//Clear the deck when the deck's destroy method is called
	deck.clear();
}