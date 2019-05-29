#pragma once
#include "SDL.h"
#include <ctime>
#include <iostream>


class Enemy
{
private:
	//int hp;
	//int maxHp;

	double xVel = 0;
	double yVel = 0;

	SDL_Rect source;
	SDL_Rect dest;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int onTarget = 0;
	bool alive = false;
	// Created for overlap
	bool overLap;

public:

	// Work on trying to fix overlap
	//bool GetOverLap(Enemy& E)
	//{
	//	if (E.getDst == E.getDst);
	//}
	
	

	Enemy()
	{
		source = { 192, 96, 44, 44 };
		dest = {-100, -100, 44, 44 };
	}
	
	void Spawn()
	{	
			alive = true;
			dest = { (rand() % 1024), 0, 44, 44 };	
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

	int GetOnTarget()
	{
		return onTarget;
	}

	void update(int x, int y)
	{
		if (alive) 
		{

			if (dest.y - y < 30 && dest.y - y > -30)
			{
				onTarget = 1;
			}
			else
			{
				onTarget = 0;
			}

			dest.x += xVel;
			dest.y += yVel;


			if (x > dest.x)
			{
				xVel = 1;
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (x < dest.x)
			{
				xVel = -1;
				flip = SDL_FLIP_NONE;
			}
			else
			{
				xVel = 0;
			}

			if (y - 10 > dest.y)
			{
				yVel = 1;
			}
			else if (y - 10 < dest.y)
			{
				yVel = -1;
			}
			else
			{
				yVel = 0;
			}

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

	int getX()
	{
		return dest.x;
	}
	int getY()
	{
		return dest.y;
	}

};
