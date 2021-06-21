#pragma once

#include "Definitions.h"

class Sprite
{
private:
	void Load(const char* fileName);


protected:
	SDL_Renderer* renderer;
	SDL_Texture* image;
	SDL_Rect rect;

	int xPosition;;
	int yPosition;

public:

	Sprite(SDL_Texture* texture, int xPos, int yPos, SDL_Renderer* renderer);
	~Sprite();

	virtual void Draw();

	void SetFrame(Uint16 frame);
	void SetRow(Uint16 row);

	void SetWidth(int width);
	void SetHeight(int height);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void SetTexture(SDL_Texture* texture);

	SDL_Texture* GetImage();

	Uint16 GetCurrentFrame();
	Uint16 GetCurrentRow();

	int GetHeight();
	int GetWidth();
	int GetXPosition();
	int GetYPosition();

	bool visible;
};

