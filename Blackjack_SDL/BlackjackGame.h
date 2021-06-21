#pragma once

#include <string>
#include <vector>

#include "Definitions.h"
#include "CardDeck.h"
#include "BlackjackHand.h"

using namespace std;

class BlackjackGame
{
private:

	int SCREENWIDTH;
	int SCREENHEIGHT;

	vector<TextRenderer*> activeText;
	vector<BlackjackHand*> activeHands;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* cardTexture;
	SDL_Texture* cardFaceTexture;
	SDL_Texture* cardBackTexture;
	SDL_Texture* dealerTexture;
	TextRenderer* t_instructionsText;
	TextRenderer* t_messageText;
	TextRenderer* t_messageText2;
	TextRenderer* t_playerChips;
	TextRenderer* t_bettingPot;
	TextRenderer* t_betText;
	TextRenderer* t_playerCardValue;
	TextRenderer* t_playerOtherCardValue;
	TextRenderer* t_dealerCardValue;
	Sprite* s_dealer;

	SDL_Event event;

	Uint32 deltaT;
	Uint32 updatedTime;

	int playerChips;
	int bettingPot;
	int bet;
	string betString;
	CardDeck deck;
	bool endGame;
	bool playerSplitHand;
	BlackjackHand* playerHands[2];
	BlackjackHand* dealerHand;

	enum GameState {
		Menu,
		Betting,
		PlayersTurn,
		DealersTurn,
		EndOfRound,
		GameIsOver
	};

	GameState gameState;

	void Initialize();
	void LoadResources();
	void GameLoop();

	void MainMenu(const Uint8* keys);
	void StartGame();

	void StartRound();
	void TakeBet(const Uint8* keys);
	void DealCards();
	void PlayerTurn(const Uint8* keys);
	void DealerTurn();
	void EndGame();
	void EndRound();
	void GameOver(const Uint8* keys);

	void UpdateChips();
	void UpdateText();
	void DrawElements();

	int CheckWin(int hand);

	void PollEvent();
	string GetButtonDown();

public:

	BlackjackGame();
	~BlackjackGame();
};

