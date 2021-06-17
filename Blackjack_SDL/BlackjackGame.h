#pragma once

#include "Definitions.h"

class BlackjackGame
{
private:

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* bgTexture;
	TextRenderer* text;

	SDL_Event event;

	Uint32 deltaT;
	Uint32 updatedTime;


	bool endGame;

public:

	BlackjackGame();

	void Initialize();
	void LoadResources();
	void GameLoop();
};

