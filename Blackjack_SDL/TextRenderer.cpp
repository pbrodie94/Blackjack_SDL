#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Draw(const char* message, int xPos, int yPos, int size)
{
	this->font = TTF_OpenFont("Fonts/Sans.ttf", size);
	this->colour = { 255, 255, 255, 255 };

	this->surface = TTF_RenderText_Solid(this->font, message, this->colour);
	this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	int width = this->surface->w;
	int height = this->surface->h;

	this->rect = { xPos, yPos, width, height };

	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);

	SDL_FreeSurface(this->surface);
}