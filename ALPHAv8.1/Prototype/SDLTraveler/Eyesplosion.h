#pragma once
#include "SDL.h"


class Eyesplosion
{
private:
	SDL_Rect source = { 0,0,192,192 };
	SDL_Rect dest = { 0,0,192,192 };

	int frame = 0;
	int frameSkip = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;


public:

	Eyesplosion(int x, int y, SDL_RendererFlip f)
	{
		dest.x = x - 75;
		dest.y = y - 75;
		flip = f;
	}

	SDL_Rect getSrc()
	{
		return source;
	}
	SDL_Rect getDst()
	{
		return dest;
	}

	SDL_RendererFlip getFlip()
	{
		return flip;
	}

	void update()
	{
		frameSkip++;

		if (frameSkip % 3 == 0)
		{
			switch (frame)
			{
			case 0:
			{
				source.x = 0;
				source.y = 0;
				break;
			}
			case 1:
			{
				source.x = 192;
				source.y = 0;
				break;
			}
			case 2:
			{
				source.x = 0;
				source.y = 192;
				break;
			}
			case 3:
			{
				source.x = 256;
				source.y = 192;
				break;
			}
			case 4:
			{
				source.x = 192;
				source.y = 384;
				break;
			}
			case 5:
			{
				source.x = 384;
				source.y = 384;
				break;
			}
			case 6:
			{
				source.x = 384;
				source.y = 0;
				break;
			}


			}
			frame++;
		}
		/*
		if (frame < 6)
		{
			return 1;
			frame++;
		}
		else
			return 2;
		*/
	}

};
