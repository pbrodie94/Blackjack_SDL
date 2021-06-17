#include "BlackjackGame.h"

BlackjackGame::BlackjackGame()
{
	this->deltaT = 75;
	this->updatedTime = 0;

	this->endGame = false;

	this->playerChips = 2000;

	gameState = GameState::Menu;

	Initialize();
}

BlackjackGame::~BlackjackGame()
{
	delete text;
	delete t_bettingPot;
	delete t_playerChips;
	delete t_playerCardValue;
	delete t_dealerCardValue;
	delete bgTexture;
	delete cardTexture;
	delete cardFaceTexture;
	delete cardBackTexture;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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

	LoadResources();
}

void BlackjackGame::LoadResources()
{
	this->bgTexture = IMG_LoadTexture(renderer, "Images/GameBoard.png");
	this->cardTexture = IMG_LoadTexture(renderer, "Images/Card_Face.png");
	this->cardFaceTexture = IMG_LoadTexture(renderer, "Images/Card_SuitNums.png");
	this->cardBackTexture = IMG_LoadTexture(renderer, "Images/Card_Back.png");

	this->text = new TextRenderer(renderer);

	this->text->SetText("Hello World!", 100, 100, 24);

	SDL_RenderClear(renderer);

	GameLoop();
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
		
		//Draw the background before anything else
		SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

		switch (BlackjackGame::gameState)
		{

		case GameState::Menu:

			MainMenu();

			break;

		case GameState::Betting:

			TakeBet();

			break;

		case GameState::PlayersTurn:

			PlayerTurn();

			break;

		case GameState::DealersTurn:

			DealerTurn();

			break;

		case GameState::EndOfRound:

			EndGame();

			break;

		case GameState::GameIsOver:

			GameOver();

			break;
		}

		if (text)
		{
			text->Draw();
		}

		SDL_RenderPresent(renderer);

		updatedTime = SDL_GetTicks();
	}
}

void BlackjackGame::StartRound()
{

}

void BlackjackGame::MainMenu()
{

}

void BlackjackGame::TakeBet()
{

}

void BlackjackGame::DealCards()
{

}

void BlackjackGame::PlayerTurn()
{

}

void BlackjackGame::DealerTurn()
{

}

void BlackjackGame::EndGame()
{

}

void BlackjackGame::GameOver()
{

}