#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "ScrollManager.h"

class Bullet : public GameObject
{
private:
	

	int xVel = 15;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	bool edge;
	bool ballistic = false;


public:
	Bullet()
	{
		rSrc = { 0, 0, 16, 7 };
		rDst = { -100,-100, 16, 7 };
		edge = false;
		ballistic = false;

		ObjInit();
	}

	Bullet(int x, int y, SDL_RendererFlip f)
	{
		rDst.x = x;
		rDst.y = y;
		rDst.w = 16;
		rDst.h = 7;

		edge = false;

		//flip = f;
		if (f == SDL_FLIP_HORIZONTAL)
		{
			flip = SDL_FLIP_HORIZONTAL;
			xVel = -15;
		}
		else
		{
			flip = SDL_FLIP_NONE;
			xVel = 15;
		}
		
		ObjInit();
	}

	void remove()
	{
		ballistic = false;
		rDst.y = -100;
		rDst.x = -100;
	}

	bool GetBallistic()
	{
		return ballistic;
	}

	void fire(int x, int y, SDL_RendererFlip f)
	{
		ballistic = true;
		rDst.x = x;
		rDst.y = y;
		rDst.w = 16;
		rDst.h = 7;

		edge = false;

		if (f == SDL_FLIP_HORIZONTAL)
		{
			flip = SDL_FLIP_HORIZONTAL;
			xVel = -15;
		}
		else
		{
			flip = SDL_FLIP_NONE;
			xVel = 15;
		}

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
		
		if (ballistic)
		{
			rDst.x += xVel;
			//baseX += xVel;
			//Scroll(ScrollManager::GetScroll()->OffX(), 0);

		}

		if (rDst.x <= 0 || rDst.x >= 1024)
		{
			remove();
		}
	}

	bool getEdge()
	{
		return edge;
	}

	int getX()
	{
		return rDst.x;
	}
	int getY()
	{
		return rDst.y;
	}

	~Bullet() {};
};
