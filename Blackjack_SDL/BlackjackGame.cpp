#include "BlackjackGame.h"

BlackjackGame::BlackjackGame()
{
	this->deltaT = 75;
	this->updatedTime = 0;

	this->endGame = false;
}

void BlackjackGame::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Unable to initialize SDL -> " << SDL_GetError() << endl;
		throw - 1;
	}

	atexit(SDL_Quit);

	window = SDL_CreateWindow("Blackjack", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (!window)
	{
		cerr << "SDL Create Window Error -> " << SDL_GetError() << endl;
		throw -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		cerr << "SDL_CreateRenderer Error -> " << SDL_GetError() << endl;
		throw -1;
	}

	if (TTF_Init() < 0)
	{
		cerr << "TTF error: " << TTF_GetError() << endl;
		throw -1;
	}
}

void BlackjackGame::LoadResources()
{
	this->bgTexture = IMG_LoadTexture(renderer, "Images/GameBoard.png");

	this->text = new TextRenderer(renderer);

	this->text->SetText("Hello World!", 100, 100, 24);

	SDL_RenderClear(renderer);
}

void BlackjackGame::GameLoop()
{
	while (!endGame)
	{

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				endGame = true;
				break;

			case SDL_KEYDOWN:

				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					endGame = true;
				}

				break;
			}
		}

		const Uint8* keys = SDL_GetKeyboardState(nullptr);

		if (keys[SDL_SCANCODE_SPACE] && text != nullptr)
		{
			text->visible = false;

			delete text;
			text = nullptr;
		}

		SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

		if (text)
		{
			text->Draw();
		}

		SDL_RenderPresent(renderer);

		updatedTime = SDL_GetTicks();
	}

	delete text;
	delete bgTexture;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}