#pragma once
#include "SDL.h"


class Platform
{
private:
	SDL_Rect source;
	SDL_Rect dest;


public:
	Platform()
	{
		source = { 0, 0,  536, 114 };
		dest = {-100, -100, 128, 30 };
	}
	Platform(int x, int y)
	{
		source = { 0, 0, 128, 32 };
		dest = { x, y, 128, 32 };

	}
	void setPlatform(int x, int y)
	{
		dest.x = x;
		dest.y = y;
	}

	int getTop()
	{
		return (dest.y - 37);
	}

	int getY()
	{
		return dest.y;
	}

	SDL_Rect getSrc()
	{
		return source;
	}
	SDL_Rect getDst()
	{
		return dest;
	}
};

