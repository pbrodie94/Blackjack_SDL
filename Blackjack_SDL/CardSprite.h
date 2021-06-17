#pragma once

#include "Sprite.h"

class CardSprite : public Sprite
{
private:

	Sprite* cardSuit;
	Sprite* cardNumber;

public:

	CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Renderer* renderer);
	CardSprite(int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer);
	CardSprite(int num, int suit, int xPos, int yPos, SDL_Texture* texture, SDL_Texture* cardFace, SDL_Renderer* renderer);

	void Draw() override;

};

