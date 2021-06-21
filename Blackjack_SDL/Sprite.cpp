#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, int xPos, int yPos, SDL_Renderer* renderer)
{
	this->renderer = renderer;

	xPosition = xPos;
	yPosition = yPos;
	
	rect.x = 0;
	rect.y = 0;

	visible = true;
	
	this->image = texture;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	if (this->visible)
	{
		SDL_Rect dest = { xPosition, yPosition, rect.w, rect.h };

		SDL_RenderCopy(renderer, image, &rect, &dest);
	}
}

void Sprite::SetFrame(Uint16 frame)
{
	if (!rect.w)
		return;

	rect.x = rect.w * frame;
}

void Sprite::SetRow(Uint16 row)
{
	if (!rect.h)
		return;

	rect.y = rect.h * row;
}

void Sprite::SetWidth(int width)
{
	this->rect.w = width;
}

void Sprite::SetHeight(int height)
{
	this->rect.h = height;
}

void Sprite::SetXPosition(int x)
{
	this->xPosition = x;
}

void Sprite::SetYPosition(int y)
{
	this->yPosition = y;
}

void Sprite::SetTexture(SDL_Texture* texture)
{
	image = texture;
}

Uint16 Sprite::GetCurrentFrame()
{
	if (!rect.w)
		return 0;

	return rect.x / rect.w;
}

Uint16 Sprite::GetCurrentRow()
{
	if (!rect.h)
		return 0;

	return rect.y / rect.h;
}

SDL_Texture* Sprite::GetImage()
{
	return this->image;
}

int Sprite::GetHeight()
{
	return this->rect.h;
}

int Sprite::GetWidth()
{
	return this->rect.w;
}

int Sprite::GetXPosition()
{
	return this->xPosition;
}

int Sprite::GetYPosition()
{
	return this->yPosition;
}
