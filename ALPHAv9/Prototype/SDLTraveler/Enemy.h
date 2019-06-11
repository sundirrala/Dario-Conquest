#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <ctime>
#include <iostream>


class Enemy : public GameObject
{
private:
	//int hp;
	//int maxHp;

	double xVel = 0;
	double yVel = 0;

	/*SDL_Rect rSrc;
	SDL_Rect rDst;*/
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int onTarget = 0;
	bool alive = false;
	// Created for overlap
	//bool overLap;

public:

	// Work on trying to fix overlap
	//bool GetOverLap(Enemy& E)
	//{
	//	if (E.getDst == E.getDst);
	//}
	
	

	Enemy()
	{
		rSrc = { 192, 96, 44, 44 };
		rDst = {-100, -100, 44, 44 };

		ObjInit();
	}
	
	void Spawn()
	{	
		alive = true;
		rDst = { (rand() % 1024), 0, 44, 44 };	
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

	int GetOnTarget()
	{
		return onTarget;
	}

	void update(int x, int y)
	{
		if (alive) 
		{

			if (rDst.y - y < 30 && rDst.y - y > -30)
			{
				onTarget = 1;
			}
			else
			{
				onTarget = 0;
			}

			//rDst.x += xVel;
			

			if (x > rDst.x + 10)
			{
				xVel = 1;
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (x < rDst.x - 10)
			{
				xVel = -1;
				flip = SDL_FLIP_NONE;
			}
			else
			{
				xVel = 0;
			}

			if (y - 10 > rDst.y)
			{
				yVel = 1;
			}
			else if (y - 10 < rDst.y)
			{
				yVel = -1;
			}
			else
			{
				yVel = 0;
			}

			baseX += xVel;
			baseY += yVel;

		}
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

	int getX()
	{
		return rDst.x;
	}
	int getY()
	{
		return rDst.y;
	}

};
