#pragma once
#include "SDL.h"
class GameObject
{
public:

	SDL_Rect rSrc = { 0,0,0,0 };
	SDL_Rect rDst = { 0,0,0,0 };

	int baseX = 0;
	int baseY = 0;

	int offX = 0;
	int offY = 0;


	void Scroll(int x, int y)
	{
		rDst.x = baseX + x;
		rDst.y = baseY + y;
	}

	void Scroll(int x)
	{
		offX += x;
		rDst.x = baseX + offX;
	}

	void ObjInit()
	{
		baseX = rDst.x;
		baseY = rDst.y;
	}

	SDL_Rect GetDst()
	{
		return rDst;
	}

	GameObject();
	~GameObject();
};

