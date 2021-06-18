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
	TextRenderer* text;
	TextRenderer* t_instructionsText;
	TextRenderer* t_playerChips;
	TextRenderer* t_bettingPot;
	TextRenderer* t_betText;
	TextRenderer* t_playerCardValue;
	TextRenderer* t_dealerCardValue;

	SDL_Event event;

	Uint32 deltaT;
	Uint32 updatedTime;

	int playerChips;
	int bettingPot;
	int bet;
	string betString;
	CardDeck deck;
	bool endGame;
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
	void EndGame(const Uint8* keys);
	void GameOver(const Uint8* keys);

	void UpdateChips();
	void DrawElements();

public:

	BlackjackGame();
	~BlackjackGame();
};

