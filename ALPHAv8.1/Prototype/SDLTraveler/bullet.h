#pragma once
#include "SDL.h"


class Bullet
{
private:
	SDL_Rect source = { 0, 0, 16, 7 };
	SDL_Rect dest;

	int xVel = 15;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	bool edge;
	bool ballistic = false;


public:
	Bullet()
	{
		dest = { -100,-100, 16, 7 };
		edge = false;
		ballistic = false;
	}

	Bullet(int x, int y, SDL_RendererFlip f)
	{
		dest.x = -100;
		dest.y = -100;
		dest.w = 16;
		dest.h = 7;

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
		
	}

	void remove()
	{
		ballistic = false;
		dest.y = -100;
		dest.x = -100;
	}

	bool GetBallistic()
	{
		return ballistic;
	}

	void fire(int x, int y, SDL_RendererFlip f)
	{
		ballistic = true;
		dest.x = x;
		dest.y = y;
		//dest.w = 16;
		//dest.h = 7;

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
		if (ballistic)
		{
			dest.x += xVel;
		}

		if (dest.x <= 0 || dest.x >= 1024)
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
		return dest.x;
	}
	int getY()
	{
		return dest.y;
	}

	~Bullet() {};
};
