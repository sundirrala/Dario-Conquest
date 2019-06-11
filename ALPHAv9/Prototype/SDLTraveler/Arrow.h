#pragma once
#include "SDL.h"

class Arrow
{
private:
	SDL_Rect source = { 288,96,64,96 };
	SDL_Rect dest = { 220, 610, 128,96 };
	int count = 0;

public:
	Arrow();

	void Update();

	void SetX(int);

	SDL_Rect GetSrc()
	{
		return source;
	}

	SDL_Rect GetDst()
	{
		return dest;
	}

	~Arrow();
};

