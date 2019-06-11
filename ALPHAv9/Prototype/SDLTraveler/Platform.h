#pragma once
#include "SDL.h"
#include "GameObject.h"

class Platform : public GameObject
{
private:
	
public:
	Platform()
	{
		rSrc = { 0, 0,  536, 114 };
		rDst = {-100, -100, 128, 30 };

		ObjInit();
	}
	Platform(int x, int y)
	{
		rSrc = { 0, 0, 128, 32 };
		rDst = { x, y, 128, 32 };

		ObjInit();
	}
	void setPlatform(int x, int y)
	{
		rDst.x = x;
		rDst.y = y;

		ObjInit();
	}

	int getTop()
	{
		return (rDst.y - 37);
	}

	int getY()
	{
		return rDst.y;
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}
	SDL_Rect getDst()
	{
		return rDst;
	}
};

