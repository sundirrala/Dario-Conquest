#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <ctime>
#include <iostream>

class Goomba : public GameObject
{
private:
	

	int frame = 0;
	int frameCount = 0;

	int direction = 1;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int hp = 18;

	bool alive = false;

public:
	Goomba()
	{
		rSrc = { 0,0, 49, 67 };
		rDst = { 0,0, 49,67 };
		rDst.x = -100;
		rDst.y = -100;

		ObjInit();
	}

	Goomba(int x, int y)
	{
		rSrc = { 0,0, 49, 67 };
		rDst = { 0,0, 49,67 };

		rDst.x = x;
		rDst.y = y;

		ObjInit();
	}

	void Spawn()
	{
		//srand(time(NULL));
		alive = true;
		rDst = { rand() % 1024, 532, 49, 67 };

		ObjInit();
	}

	void Remove()
	{
		alive = false;
		rDst.x = -100;
		rDst.y = -100;
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
			baseX += direction;
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
			rSrc.x = frame * 64;


			if (baseX >= 980)
			{
				direction = -1;
			}

			if (baseX <= 0)
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
		return rDst.x;
	}
	int getY()
	{
		return rDst.y;
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
		return rSrc;
	}

	SDL_Rect getDst()
	{
		return rDst;
	}

	void damage(int dmg)
	{
		hp -= dmg;
	}

};

#pragma once
#include "SDL.h"


class Goomblast : public GameObject
{
private:
	
	int frame = 0;
	int frameSkip = 0;

public:

	Goomblast(int x, int y)
	{
		rSrc = { 0,0,192,192 };
		rDst = { 0,0,192,192 };


		rDst.x = x - 73;
		rDst.y = y - 130;
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}
	SDL_Rect getDst()
	{
		return rDst;
	}


	void update()
	{
		frameSkip++;

		if (frameSkip % 3 == 0)
		{
			frame++;
			rSrc.x = frame * 192;
		}

	}

};

