#pragma once

#include "Definitions.h"

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Draw(const char* message, int xPos, int yPos, int size);

	bool visible;

private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
	SDL_Colour colour;

};

