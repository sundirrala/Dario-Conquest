#pragma once
#include "SDL.h"



class Health
{
private:
	SDL_Rect source = { 32,0, 22, 22 };
	SDL_Rect dest = { 0,32,64,64 };

	bool full = true;

public:

	Health(int x)
	{
		dest.x = 70 * x;
	}

	void dmg()
	{
		source.x = 64;
	}

	bool getDmg()
	{
		return full;
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
