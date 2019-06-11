#pragma once
#include "SDL.h"


class Goomblast
{
private:
	SDL_Rect source = { 0,0,192,192 };
	SDL_Rect dest = { 0,0,192,192 };

	int frame = 0;
	int frameSkip = 0;

public:

	Goomblast(int x, int y)
	{
		dest.x = x - 73;
		dest.y = y - 130;
	}

	SDL_Rect getSrc()
	{
		return source;
	}
	SDL_Rect getDst()
	{
		return dest;
	}


	void update()
	{
		frameSkip++;

		if (frameSkip % 3 == 0)
		{
			frame++;
			source.x = frame * 192;
		}

	}

};

