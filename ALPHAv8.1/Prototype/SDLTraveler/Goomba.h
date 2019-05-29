#pragma once
#include "SDL.h"
#include <ctime>
#include <iostream>

class Goomba
{
private:
	SDL_Rect source = { 0,0, 49, 67 };
	SDL_Rect dest = { 0,0, 49,67 };

	int frame = 0;
	int frameCount = 0;

	int direction = 1;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int hp = 18;

	bool alive = false;

public:
	Goomba()
	{
		dest.x = -100;
		dest.y = -100;
	}

	Goomba(int x, int y)
	{
		dest.x = x;
		dest.y = y;
	}

	void Spawn()
	{
		//srand(time(NULL));
		alive = true;
		dest = { rand() % 1024, 532, 49, 67 };
	}

	void Remove()
	{
		alive = false;
		dest.x = -100;
		dest.y = -100;
	}

	bool GetAlive()
	{
		return alive;
	}

	void update()
	{
		if (alive) 
		{
			frameCount++;
			dest.x += direction;
			if (frameCount % 2 == 0)
			{
				if (frame < 9)
				{
					frame++;
				}
				else
				{
					frame = 0;
				}
			}
			source.x = frame * 64;


			if (dest.x >= 980)
			{
				direction = -1;
			}

			if (dest.x <= 0)
			{
				direction = 1;
			}

		}
/*
		if (hp <= 0)
		{
			Remove();
		}
*/
	}

	int getX()
	{
		return dest.x;
	}
	int getY()
	{
		return dest.y;
	}
	int GetHP()
	{
		return hp;
	}

	SDL_RendererFlip getFlip()
	{
		return flip;
	}

	SDL_Rect getSrc()
	{
		return source;
	}

	SDL_Rect getDst()
	{
		return dest;
	}

	void damage(int dmg)
	{
		hp -= dmg;
	}

};

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

