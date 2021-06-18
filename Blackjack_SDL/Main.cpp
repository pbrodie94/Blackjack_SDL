#include "BlackjackGame.h"

void DisplayInstructions();

int main(int argv, char** argc)
{
	try {
		BlackjackGame blackjackGame;
	}
	catch (int error)
	{
		return error;
	}

	cout << "Program ran successfully.\n" << endl;

	return 0;
}

void DisplayInstructions()
{
	//Display instructions
	cout << "\nBlackjack Instructions\n" << endl;

	cout << "The object of Blackjack is to get your hand's value as close to 21 as possible without going over as well as have a higher hand value than the dealer.\n" << endl;

	cout << "- The game begins with a round of betting. You may bet as much as you like provided you have enough chips" << endl;
	cout << "- The dealer will then deal two face up cards to you, and one face up and one face down card to the dealer" << endl;

	cout << "\nCard values are as follows: " << endl;
	cout << "- Numbered cards (2 - 9) are worth the amount that they display" << endl;
	cout << "- Ace can be 1 or 11. If the overall hand value is higher than 21 while the Ace is 11, its value becomes 1" << endl;
	cout << "- Face cards (Jack, Queen, King) are worth 10" << endl;
	cout << "- If you receive an Ace and a Face card on your starting hand, then you have a Blackjack!" << endl;

	cout << "\nDuring your turn you may perform the following actions:" << endl;
	cout << "- 'H' to Hit - Request another card. You may do this until you're at an acceptable value, or you exceed 21" << endl;
	cout << "- 'S' to Stand - When you're happy with your hand value, use stand" << endl;
	cout << "- 'D' to Double Down - If you're feeling good about your hand, you may double your bet and get one more card. This can only be done at the start of your turn." << endl;
	cout << "- 'P' to Split - If your intitial two cards are the same value (i.e. two Aces) you may split your hand into two and bet the same bet on the second" << endl;

	cout << "\nAt the end of the round:" << endl;
	cout << "- If your hand value is greater than the dealer, you win double your bet!" << endl;
	cout << "- If you get a Blackjack on your starting hand, you win your bet plus 1.5x your bet!" << endl;
	cout << "- If you and the dealer tie, this is known as a 'Push' and you will receive your bet back to play another round" << endl;
	cout << "- If your hand value is lesser than the dealer, or over 21, you lose the hand" << endl;

	cout << "\nGood Luck!\n" << endl;
}