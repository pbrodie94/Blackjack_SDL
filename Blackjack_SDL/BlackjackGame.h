#pragma once

#include "Definitions.h"
#include "CardDeck.h"
#include "BlackjackHand.h"

class BlackjackGame
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* cardTexture;
	SDL_Texture* cardFaceTexture;
	SDL_Texture* cardBackTexture;
	TextRenderer* text;
	TextRenderer* t_playerChips;
	TextRenderer* t_bettingPot;
	TextRenderer* t_playerCardValue;
	TextRenderer* t_dealerCardValue;

	SDL_Event event;

	Uint32 deltaT;
	Uint32 updatedTime;

	int playerChips;
	int bettingPot;
	CardDeck deck;
	bool endGame;
	BlackjackHand playerHands[2];
	BlackjackHand dealerHand;

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

	void MainMenu();

	void StartRound();
	void TakeBet();
	void DealCards();
	void PlayerTurn();
	void DealerTurn();
	void EndGame();
	void GameOver();

public:

	BlackjackGame();
	~BlackjackGame();
};

