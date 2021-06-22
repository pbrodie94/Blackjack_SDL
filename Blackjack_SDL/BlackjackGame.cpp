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
	this->playerSplitHand = false;

	this->audioRate = 22050;
	this->audioChannels = 2;
	this->audioBuffers = 640;
	this->audioFormat = AUDIO_S16SYS;

	gameState = GameState::Menu;

	Initialize();
}

BlackjackGame::~BlackjackGame()
{
	delete t_instructionsText;
	delete t_bettingPot;
	delete t_playerChips;
	delete t_playerCardValue;
	delete t_dealerCardValue;
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(cardTexture);
	SDL_DestroyTexture(cardFaceTexture);
	SDL_DestroyTexture(cardBackTexture);
	SDL_DestroyTexture(dealerTexture);
	delete s_dealer;

	delete playerHands[0];
	delete playerHands[1];
	delete dealerHand;

	activeHands.clear();
	activeText.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void BlackjackGame::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		cerr << "Unable to initialize SDL -> " << SDL_GetError() << endl;
		throw 1;
	}

	atexit(SDL_Quit);

	window = SDL_CreateWindow("Blackjack", 100, 100, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		cerr << "SDL Create Window Error -> " << SDL_GetError() << endl;
		throw 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		cerr << "SDL_CreateRenderer Error -> " << SDL_GetError() << endl;
		throw 1;
	}

	if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
	{
		cerr << "Failed to open audio " << SDL_GetError() << endl;
		throw 1;
	}

	if (TTF_Init() < 0)
	{
		cerr << "TTF error: " << TTF_GetError() << endl;
		throw 1;
	}

	LoadResources();
}

void BlackjackGame::LoadResources()
{
	this->bgTexture = IMG_LoadTexture(renderer, "Images/GameBoard.png");
	if (!bgTexture)
	{
		cerr << "Could not load GameBoard Texture." << endl;
	}
	this->cardTexture = IMG_LoadTexture(renderer, "Images/Card_Face.png");
	if (!cardTexture)
	{
		cerr << "Could not load Card Texture." << endl;
	}
	this->cardFaceTexture = IMG_LoadTexture(renderer, "Images/Card_SuitNums.png");
	if (!cardFaceTexture)
	{
		cerr << "Could not load Card Face Texture." << endl;
	}
	this->cardBackTexture = IMG_LoadTexture(renderer, "Images/Card_Back.png");
	if (!cardBackTexture)
	{
		cerr << "Could not load Card Back Texture." << endl;
	}
	this->dealerTexture = IMG_LoadTexture(renderer, "Images/Dealer_Idle.png");
	if (!dealerTexture)
	{
		cerr << "Could not load Dealer Texture." << endl;
	}

	this->music = Mix_LoadMUS("Audio/SBTS.mp3");
	if (this->music == nullptr)
	{
		cerr << "Failed to load music." << endl;
	}
	else {
		Mix_PlayMusic(this->music, -1);
	}

	this->t_instructionsText = new TextRenderer(renderer);
	this->t_instructionsText->SetText("Press Space to Start", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
	this->t_instructionsText->SetXPosition(t_instructionsText->GetXPosition() - t_instructionsText->width / 2);
	activeText.push_back(t_instructionsText);

	s_dealer = new Sprite(dealerTexture, SCREENWIDTH / 2, 50, renderer);
	s_dealer->SetWidth(69);
	s_dealer->SetHeight(76);
	s_dealer->SetXPosition(s_dealer->GetXPosition() - s_dealer->GetWidth() / 2);
	//s_dealer->visible = false;

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
		PollEvent();

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

			EndRound();

			break;

		case GameState::GameIsOver:

			GameOver(keys);

			break;
		}

		//Draw the background before anything else
		//SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

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
	t_playerChips->visible = true;
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
	s_dealer->visible = true;

	StartRound();
}

void BlackjackGame::StartRound()
{
	//Reinitiialize player and dealer hands
	playerHands[0]->ResetHand();
	playerHands[1]->ResetHand();
	dealerHand->ResetHand();

	playerSplitHand = false;

	gameState = GameState::Betting;
}

void BlackjackGame::TakeBet(const Uint8* keys)
{
	t_instructionsText->visible = true;
	t_instructionsText->SetText("Enter your bet with number keys then press enter.", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
	t_instructionsText->SetXPosition(t_instructionsText->GetXPosition() - t_instructionsText->width / 2);

	//Display betting text
	if (t_betText == nullptr)
	{
		t_betText = new TextRenderer(renderer);
		activeText.push_back(t_betText);
	}

	t_betText->visible = true;
	string betText = "Bet: " + to_string(bet);
	t_betText->SetText(betText.c_str(), SCREENHEIGHT / 2, SCREENWIDTH / 2, 15);

	//take in numeric input in update loop
	if (event.type == SDL_KEYDOWN)
	{
		const char* key = SDL_GetKeyName(event.key.keysym.sym);
		char k = key[strlen(key) - 1];

		if (isdigit(k))
		{
			betString += k;
			bet = stoi(betString);
		}

		//Check for enter press
		if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2)
		{
			if (bet > 0 && bet <= playerChips)
			{
				playerChips -= bet;
				bettingPot += bet;

				UpdateChips();

				bet = 0;
				betString = "";

				t_betText->visible = false;

				DealCards();
			}
			else {
				if (bet > playerChips)
				{
					if (t_messageText == nullptr)
					{
						t_messageText = new TextRenderer(renderer);
						activeText.push_back(t_messageText);
					}

					t_messageText->SetText("You don't have enough chips, please try again.", SCREENWIDTH / 2, SCREENHEIGHT / 2 - 30, 20);
					t_messageText->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
					t_messageText->visible = true;

					bet = 0;
				}
				else if (bet <= 0)
				{
					if (t_messageText == nullptr)
					{
						t_messageText = new TextRenderer(renderer);
						activeText.push_back(t_messageText);
					}

					t_messageText->SetText("Bet must be greater than 0, please try again.", SCREENWIDTH / 2, SCREENHEIGHT / 2 - 30, 20);
					t_messageText->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
					t_messageText->visible = true;

					bet = 0;
				}
			}
		}
		else if (event.key.keysym.sym == SDLK_BACKSPACE)
		{
			bet = 0;
			betString = "0";
		}

	}
}

void BlackjackGame::DealCards()
{
	playerHands[0]->AddCard(deck.DrawCard());
	dealerHand->AddCard(deck.DrawCard());
	playerHands[0]->AddCard(deck.DrawCard());
	dealerHand->AddCard(deck.DrawCard());

	gameState = GameState::PlayersTurn;

	if (t_dealerCardValue == nullptr)
	{
		t_dealerCardValue = new TextRenderer(renderer);
		activeText.push_back(t_dealerCardValue);
	}

	if (t_playerCardValue == nullptr)
	{
		t_playerCardValue = new TextRenderer(renderer);
		activeText.push_back(t_playerCardValue);
	}

	UpdateText();
}

void BlackjackGame::PlayerTurn(const Uint8* keys)
{
	if (!playerSplitHand && playerHands[0]->stand)
	{
		//Turn over
		t_instructionsText->visible = false;
		gameState = GameState::DealersTurn;
		return;
	}
	else if (playerSplitHand && playerHands[0]->stand && playerHands[1]->stand) {
		t_instructionsText->visible = false;
		gameState = GameState::DealersTurn;
		return;
	}

	string turnMessage = "Press 'H' to Hit, 'S' to Stand";

	if (playerHands[0]->GetNumCards() == 2 && !playerSplitHand)
	{
		turnMessage += ", 'D' to double down";
	}

	if (playerHands[0]->GetCanSplit() && !playerSplitHand)
	{
		turnMessage += ", 'P' to split";
	}

	turnMessage += ".";

	t_instructionsText->visible = true;
	t_instructionsText->SetText(turnMessage.c_str(), SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
	t_instructionsText->SetXPosition(t_instructionsText->GetXPosition() - t_instructionsText->width / 2);

	if (playerSplitHand)
	{
		string handMessage = "";

		if (!playerHands[0]->stand)
		{
			handMessage = "Playing hand one.";
		}
		else {
			handMessage = "Playing hand two.";
		}

		if (t_messageText == nullptr)
		{
			t_messageText = new TextRenderer(renderer);
			activeText.push_back(t_messageText);
		}

		t_messageText->SetText(handMessage.c_str(), SCREENWIDTH / 2, SCREENHEIGHT / 2 - 30, 20);
		t_messageText->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
		t_messageText->visible = true;
	}

	//Get player input
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_h:
			//Hit

			if (!playerHands[0]->stand)
			{
				playerHands[0]->AddCard(deck.DrawCard());
			}
			else {
				playerHands[1]->AddCard(deck.DrawCard());
			}

			UpdateText();
			return;
			break;

		case SDLK_s:
			//Stand
			if (!playerHands[0]->stand)
			{
				playerHands[0]->stand = true;
			}
			else {
				playerHands[1]->stand = true;
			}

			if (t_messageText != nullptr)
			{
				t_messageText->visible = false;
			}

			return;
			break;
		case SDLK_d:
			if (!playerSplitHand && playerHands[0]->GetNumCards() == 2)
			{
				//Double down
				if (playerChips >= bettingPot)
				{
					playerChips -= bettingPot;
					bettingPot *= 2;
					UpdateChips();
					playerHands[0]->AddCard(deck.DrawCard());
					playerHands[0]->stand = true;
				}
			}

			return;
			break;

		case SDLK_p:
			if (playerHands[0]->GetCanSplit() && !playerSplitHand && playerChips >= bettingPot)
			{
				//Split
				playerHands[0]->SplitHand(*playerHands[1]);
				playerSplitHand = true;
				playerChips -= bettingPot;
				bettingPot *= 2;
				playerHands[0]->AddCard(deck.DrawCard());
				playerHands[1]->AddCard(deck.DrawCard());
				UpdateText();
			}

			return;
			break;
		}
	}
}

void BlackjackGame::DealerTurn()
{
	if (dealerHand->GetIsBlackjack() || dealerHand->stand || dealerHand->GetIsBust())
	{
		//Dealer turn over
		EndGame();

		gameState = GameState::EndOfRound;

		return;
	}
	
	if (dealerHand->handValue > 17 || dealerHand->handValue > playerHands[0]->handValue)
	{
		dealerHand->stand = true;
		return;
	}

	//Dealer hits
	dealerHand->AddCard(deck.DrawCard());
}

void BlackjackGame::EndGame()
{
	//Check for win
	int winnings = 0;
	int handResult = CheckWin(0);
	int playerBet = bettingPot;

	string message = "";

	if (playerSplitHand)
	{
		playerBet /= 2;
	}

	switch (handResult)
	{
	case 0:
		//Lose
		//Display house wins

		if (playerHands[0]->handValue > 21)
		{
			message = "Bust! ";
		} 

		message += "House wins.";

		break;

	case 1:
		//Push, return bet
		//display push, bet returned
		
		playerChips += playerBet;

		message = "Push, bet returned.";

		break;

	case 2:
		//Win
		//Display you win!

		winnings = playerBet * 2;
		playerChips += winnings;

		message = "Win! " + to_string(winnings) + " chips.";

		break;

	case 3:
		//Blackjack win

		//Display Blackjack!

		winnings = playerBet + (playerBet * 1.5);
		playerChips += winnings;

		message = "Blackjack! " + to_string(winnings) + " chips won.";

		break;
	}

	if (t_messageText == nullptr)
	{
		t_messageText = new TextRenderer(renderer);
		activeText.push_back(t_messageText);
	}

	t_messageText->SetText(message.c_str(), SCREENWIDTH / 2, SCREENHEIGHT / 2 - 30, 20);
	t_messageText->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
	t_messageText->visible = true;

	if (playerSplitHand)
	{
		winnings = 0;
		handResult = CheckWin(1);

		switch (handResult)
		{
		case 0:
			//Lose
			//Display house wins

			message = "";

			if (playerHands[1]->handValue > 21)
			{
				message = "Bust! ";
			}

			message += "House wins.";

			break;

		case 1:
			//Push, return bet
			//display push, bet returned

			playerChips += playerBet;

			message = "Push, bet returned.";

			break;

		case 2:
			//Win
			//Display you win!

			winnings = playerBet * 2;
			playerChips += winnings;

			message = "Win! " + to_string(winnings) + " chips.";

			break;

		case 3:
			//Blackjack win

			//Display Blackjack!

			winnings = playerBet + (playerBet * 1.5);
			playerChips += winnings;

			message = "Blackjack! " + to_string(winnings) + " chips won.";

			break;
		}

		if (t_messageText2 == nullptr)
		{
			t_messageText2 = new TextRenderer(renderer);
			activeText.push_back(t_messageText2);
		}

		t_messageText2->SetText(message.c_str(), SCREENWIDTH / 2, SCREENHEIGHT / 2, 20);
		t_messageText2->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
		t_messageText2->visible = true;
	}

	bettingPot = 0;
	UpdateChips();

	t_instructionsText->SetText("Press Space to Continue.", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
	t_instructionsText->SetXPosition(t_instructionsText->GetXPosition() - t_instructionsText->width / 2);
	t_instructionsText->visible = true;
}

void BlackjackGame::EndRound()
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			//Continue
			t_playerCardValue->visible = false;
			if (t_playerOtherCardValue != nullptr)
			{
				t_playerOtherCardValue->visible = false;
			}
			t_dealerCardValue->visible = false;
			if (t_messageText2 != nullptr)
			{
				t_messageText2->visible = false;
			}

			if (playerChips > 0)
			{
				//Continue
				t_messageText->visible = false;
				StartRound();

				return;
			}

			//Game over
			t_messageText->SetText("Game Over.", SCREENWIDTH / 2, SCREENHEIGHT / 2, 20);
			t_messageText->SetXPosition(t_messageText->GetXPosition() - t_messageText->width / 2);
			t_messageText->visible = true;

			t_instructionsText->SetText("Press Space to Continue.", SCREENWIDTH / 2, SCREENHEIGHT - 50, 20);
			t_instructionsText->SetXPosition(t_instructionsText->GetXPosition() - t_instructionsText->width / 2);
			t_instructionsText->visible = true;

			gameState = GameState::GameIsOver;
		}
	}
}

void BlackjackGame::GameOver(const Uint8* keys)
{
	//Display game over 

	//Press space to play again or 
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			StartGame();
		}
	}
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

void BlackjackGame::UpdateText()
{
	string cardValue = to_string(dealerHand->handValue);
	t_dealerCardValue->SetText(cardValue.c_str(), 140, 100, 20);
	t_dealerCardValue->visible = true;

	cardValue = to_string(playerHands[0]->handValue);
	t_playerCardValue->SetText(cardValue.c_str(), 140, SCREENHEIGHT - 100, 20);
	t_playerCardValue->visible = true;

	if (playerSplitHand && playerHands[1]->GetNumCards() > 1)
	{
		cardValue = to_string(playerHands[1]->handValue);

		if (t_playerOtherCardValue == nullptr)
		{
			t_playerOtherCardValue = new TextRenderer(renderer);
			activeText.push_back(t_playerOtherCardValue);
		}

		t_playerOtherCardValue->SetText(cardValue.c_str(), 140, t_playerCardValue->GetYPosition() - 20, 20);
		t_playerOtherCardValue->visible = true;
	}
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

	s_dealer->Draw();
}

int BlackjackGame::CheckWin(int hand)
{
	//Return 0 for lose, 1 for push, 2 for win, 3 for blackjack win

	if (playerHands[hand]->GetIsBust())
	{
		//Lose
		return 0;
	}
	else if (dealerHand->handValue > playerHands[hand]->handValue && !dealerHand->GetIsBust())
	{
		//Lose
		return 0;

	}
	else {

		if (playerHands[hand]->handValue == dealerHand->handValue)
		{
			return 1;
		}
		else if (playerHands[hand]->handValue > dealerHand->handValue || dealerHand->GetIsBust())
		{
			//win
			if (playerHands[hand]->GetIsBlackjack())
			{
				return 3;
			}
			else {

				return 2;
			}
		}
	}
}

void BlackjackGame::PollEvent()
{
	if (SDL_PollEvent(&event))
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

		default:
			break;
		}
	}
}
