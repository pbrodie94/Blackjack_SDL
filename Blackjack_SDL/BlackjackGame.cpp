#include "BlackjackGame.h"

BlackjackGame::BlackjackGame()
{
	this->SCREENWIDTH = 640;
	this->SCREENHEIGHT = 480;

	this->deltaT = 75;
	this->updatedTime = 0;

	this->endGame = false;

	this->playerChips = 2000;
	this->bettingPot = 0;
	this->bet = 0;

	gameState = GameState::Menu;

	Initialize();
}

BlackjackGame::~BlackjackGame()
{
	delete text;
	delete t_instructionsText;
	delete t_bettingPot;
	delete t_playerChips;
	delete t_playerCardValue;
	delete t_dealerCardValue;
	delete bgTexture;
	delete cardTexture;
	delete cardFaceTexture;
	delete cardBackTexture;

	delete playerHands[0];
	delete playerHands[1];
	delete dealerHand;

	/*for (int i = 0; i < activeHands.size(); i++)
	{
		delete (activeHands[i]);
		activeHands[i] = nullptr;
	}

	for (int i = 0; i < activeText.size(); i++)
	{
		delete (activeText[i]);
		activeText[i] = nullptr;
	}

	activeHands.clear();
	activeText.clear();*/

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

	window = SDL_CreateWindow("Blackjack", 100, 100, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
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
	this->t_instructionsText = new TextRenderer(renderer);

	this->text->SetText("Press space to start.", 100, 100, 24);
	this->t_instructionsText->SetText("Press Space to Start", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
	activeText.push_back(text);
	activeText.push_back(t_instructionsText);

	SDL_RenderClear(renderer);

	playerHands[0] = new BlackjackHand(SCREENWIDTH - 100, SCREENHEIGHT - 100, renderer, cardTexture, cardBackTexture, cardFaceTexture);
	playerHands[1] = new BlackjackHand(SCREENWIDTH - 100, SCREENHEIGHT - 130, renderer, cardTexture, cardBackTexture, cardFaceTexture);
	dealerHand = new BlackjackHand(SCREENWIDTH - 100, 150, renderer, cardTexture, cardBackTexture, cardFaceTexture);

	activeHands.push_back(playerHands[0]);
	activeHands.push_back(playerHands[1]);
	activeHands.push_back(dealerHand);

	deck.SetNumberDecks(8);
	deck.CreateDeck();

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

				if (gameState == GameState::Betting)
				{
					const char* key = SDL_GetKeyName(event.key.keysym.sym);
					char k = key[strlen(key) - 1];
					
					if (isdigit(k))
					{
						betString += k;
						bet = stoi(betString);
					}
					
				}

				break;
			}
		}
		
		//Draw the background before anything else
		SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

		const Uint8* keys = SDL_GetKeyboardState(nullptr);

		switch (BlackjackGame::gameState)
		{

		case GameState::Menu:

			MainMenu(keys);

			break;

		case GameState::Betting:

			TakeBet(keys);

			break;

		case GameState::PlayersTurn:

			PlayerTurn(keys);

			break;

		case GameState::DealersTurn:

			DealerTurn();

			break;

		case GameState::EndOfRound:

			EndGame(keys);

			break;

		case GameState::GameIsOver:

			GameOver(keys);

			break;
		}

		//Draw other game pieces to screen
		DrawElements();

		SDL_RenderPresent(renderer);

		updatedTime = SDL_GetTicks();
	}
}

void BlackjackGame::MainMenu(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_SPACE])
	{
		this->text->SetText("Start Game");

		StartGame();
	}
}

void BlackjackGame::StartGame()
{
	//Show player chips
	playerChips = 2000;
	
	if (t_playerChips == nullptr)
	{
		t_playerChips = new TextRenderer(renderer);
	}
	t_playerChips->SetText("Chips: 0", 50, SCREENHEIGHT - 100, 15);
	activeText.push_back(t_playerChips);

	//Show pot text
	bettingPot = 0;

	if (t_bettingPot == nullptr)
	{
		t_bettingPot = new TextRenderer(renderer);
	}
	t_playerChips->SetText("Pot: 0", 50, 250, 15);
	activeText.push_back(t_bettingPot);

	UpdateChips();

	//Show dealer

	StartRound();
}

void BlackjackGame::StartRound()
{
	//Reinitiialize player and dealer hands
	playerHands[0]->ResetHand();
	playerHands[1]->ResetHand();
	dealerHand->ResetHand();

	gameState = GameState::Betting;
}

void BlackjackGame::TakeBet(const Uint8* keys)
{
	t_instructionsText->SetText("Enter your bet with number keys then press enter.", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);

	//Display betting text
	if (t_betText == nullptr)
	{
		t_betText = new TextRenderer(renderer);
		activeText.push_back(t_betText);
	}

	//take in numeric input in update loop

	string betText = "Bet: " + to_string(bet);
	t_betText->SetText(betText.c_str(), SCREENHEIGHT / 2, SCREENWIDTH / 2, 15);

	//Check for enter press
	if (keys[SDL_SCANCODE_RETURN] || keys[SDL_SCANCODE_RETURN2])
	{
		if (bet > 0 && bet <= playerChips)
		{
			playerChips -= bet;
			bettingPot += bet;

			UpdateChips();

			bet = 0;
			betString = "";

			t_betText->visible = false;
			activeText.erase(remove(activeText.begin(), activeText.end(), t_betText), activeText.end());

			DealCards();
		}
	}
}

void BlackjackGame::DealCards()
{
	playerHands[0]->AddCard(deck.DrawCard());

	gameState = GameState::PlayersTurn;
}

void BlackjackGame::PlayerTurn(const Uint8* keys)
{

}

void BlackjackGame::DealerTurn()
{

}

void BlackjackGame::EndGame(const Uint8* keys)
{

}

void BlackjackGame::GameOver(const Uint8* keys)
{

}

void BlackjackGame::UpdateChips()
{
	string chipsText = "Chips: " + to_string(playerChips);
	//t_playerChips->SetText(chipsText.c_str());
	t_playerChips->SetText(chipsText.c_str(), 50, SCREENHEIGHT - 100, 15);

	string potText = "Pot: " + to_string(bettingPot);
	//t_bettingPot->SetText(potText.c_str());
	t_bettingPot->SetText(potText.c_str(), 50, 250, 15);
}

void BlackjackGame::DrawElements()
{
	if (activeText.size() > 0)
	{
		for (int i = 0; i < activeText.size(); i++)
		{
			if (activeText[i]->visible)
			{
				activeText[i]->Draw();
			}
		}
	}

	if (activeHands.size() > 0)
	{
		for (int i = 0; i < activeHands.size(); i++)
		{
			activeHands[i]->DrawHand();
		}
	}
}