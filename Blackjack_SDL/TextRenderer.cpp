#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	this->visible = true;
}

TextRenderer::~TextRenderer()
{
	TTF_CloseFont(this->font);

	this->renderer = nullptr;
	this->texture = nullptr;
	this->surface = nullptr;
	this->font = nullptr;

	delete(this->renderer);
	delete(this->texture);
	delete(this->surface);
	delete(this->font);
}

void TextRenderer::SetText(const char* message)
{
	SDL_FreeSurface(this->surface);
	SDL_DestroyTexture(this->texture);

	this->surface = TTF_RenderText_Solid(this->font, message, this->colour);
	this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	this->width = this->surface->w;
	this->height = this->surface->h;

	this->rect = { this->xPos, this->yPos, this->width, this->height };
}

void TextRenderer::SetText(const char* message, int xPos, int yPos, int size)
{
	SDL_FreeSurface(this->surface);
	SDL_DestroyTexture(this->texture);

	this->font = TTF_OpenFont("Fonts/Sans.ttf", size);
	this->colour = { 255, 255, 255, 255 };

	this->xPos = xPos;
	this->yPos = yPos;

	this->surface = TTF_RenderText_Solid(this->font, message, this->colour);
	this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

	this->width = this->surface->w;
	this->height = this->surface->h;

	this->rect = { this->xPos, this->yPos, this->width, this->height };

}

void TextRenderer::Draw()
{
	if (this->visible)
	{
		SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);
	}
}

void TextRenderer::SetXPosition(int xPos)
{
	this->rect.x = xPos;
}

void TextRenderer::SetYPosition(int yPos)
{
	this->rect.y = yPos;
}