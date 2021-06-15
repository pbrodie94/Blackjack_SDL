#pragma once

#include "Definitions.h"

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void SetText(const char* message, int xPos, int yPos, int size);

	void Draw();

	bool visible;

	int width;
	int height;
private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
	SDL_Colour colour;


	int xPos;
	int yPos;
	char* message;
};

