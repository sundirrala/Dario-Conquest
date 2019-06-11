#pragma once
#include "SDL.h"
#include "GameObject.h"


class Eyesplosion : public GameObject
{
private:
	

	int frame = 0;
	int frameSkip = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;


public:

	Eyesplosion(int x, int y, SDL_RendererFlip f)
	{
		rSrc = { 0,0,192,192 };
		rDst = { 0,0,192,192 };

		rDst.x = x - 75;
		rDst.y = y - 75;
		flip = f;

		ObjInit();
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}
	SDL_Rect getDst()
	{
		return rDst;
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
				rSrc.x = 0;
				rSrc.y = 0;
				break;
			}
			case 1:
			{
				rSrc.x = 192;
				rSrc.y = 0;
				break;
			}
			case 2:
			{
				rSrc.x = 0;
				rSrc.y = 192;
				break;
			}
			case 3:
			{
				rSrc.x = 256;
				rSrc.y = 192;
				break;
			}
			case 4:
			{
				rSrc.x = 192;
				rSrc.y = 384;
				break;
			}
			case 5:
			{
				rSrc.x = 384;
				rSrc.y = 384;
				break;
			}
			case 6:
			{
				rSrc.x = 384;
				rSrc.y = 0;
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
