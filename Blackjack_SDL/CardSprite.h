#pragma once

#include "Sprite.h"

class CardSprite : public Sprite
{
private:
	struct Vector2 {
		int x;
		int y;
	};

	Sprite* cardSuit;
	Sprite* cardSuit2;
	Sprite* cardNumber;
	Sprite* cardNumber2;

	int width = 48;
	int height = 64;

	Vector2 cardNumer1Pos;
	Vector2 cardNumer2Pos;
	Vector2 cardSuit1Pos;
	Vector2 cardSuit2Pos;

	void InitFacePositions(int xy);
	void InitFaceSprites(SDL_Texture* cardFace, int num, int suit);

public:

	CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer);
	CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer);
	CardSprite(int num, int suit, int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer);
	~CardSprite();

	void UnHide(SDL_Texture* card, SDL_Texture* cardFace, int num, int suit);
	void Draw() override;

	bool hidden = false;

};

