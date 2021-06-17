#pragma once

#include "Sprite.h"

class CardSprite : public Sprite
{
private:

	Sprite* cardSuit;
	Sprite* cardNumber;

public:

	CardSprite(int width, int height, SDL_Renderer* renderer);
	CardSprite(int num, int suit, int width, int height, SDL_Renderer* renderer);

	void Draw() override;

};

