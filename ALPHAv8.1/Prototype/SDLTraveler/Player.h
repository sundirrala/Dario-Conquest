#pragma once
#include "SDL.h"


class Player
{
private:
	int hp;
	int maxHp;
	int frame = 1;
	int frameSkip = 0;
	int dmgCount = 0;
	
	bool onGround = false;
	bool sprint = false;

	bool slash = false;
	int slashCount = 0;

	double xVel = 0;
	double yVel = 0;

	SDL_Rect source;
	SDL_Rect dest;

	SDL_Rect bSrc;
	SDL_Rect bDst;

	SDL_Rect eSrc;
	SDL_Rect eDst;

public:
	bool GetGround() {
		return onGround;
	}

	Player()
	{
		hp = 3;
		maxHp = 3;

		//source = { 0, 25, 32, 39 };
		//dest = { 510, 300, 32, 39 };

		source = { 0, 25, 32, 29 };
		dest = { 510, 300, 32, 29 };

		bSrc = { 0, 54, 32, 12 };
		bDst = { 0, 0, 32, 12 };


		eSrc = { 160, 192, 32, 64 };
		eDst = { 0, 0, 40, 64 };
	}

	bool GetSlash()
	{
		return slash;
	}


	SDL_Rect getBsrc()
	{
		return bSrc;
	}

	SDL_Rect getBdst()
	{
		return bDst;
	}

	SDL_Rect getEsrc()
	{
		return eSrc;
	}

	SDL_Rect getEdst()
	{
		return eDst;
	}

	bool GetSprint()
	{
		return sprint;
	}

	void setY(int y)
	{
		dest.y = y;
	}

	int getYvel()
	{
		return yVel;
	}

	void setGround(bool b)
	{
		onGround = b;
	}

	void update(SDL_RendererFlip f)
	{

		dest.x += xVel;
		dest.y += yVel;

		if (sprint)
		{
			dest.x += xVel;
			//dest.y += yVel;
		}

		bDst.x = dest.x;
		bDst.y = dest.y + 27;

		eDst.y = dest.y - 16;
		if (f == SDL_FLIP_NONE)
		{
			eDst.x = dest.x + 10;
		}
		else
		{
			eDst.x = dest.x - 20;
		}

		frameSkip++;

		if (onGround == false)
		{
			yVel += 0.5;
		}
		//else
		//{
		//	yVel = 0;
		//}

		if (yVel < 0)
		{
			frame = 5;
			//source.h = 41;
			//dest.h = 41;
		}
		else
		{
			//source.h = 39;
			//dest.h = 39;
			if (xVel == 0)
			{
				frame = 0;
			}
			else if (xVel != 0)
			{
				if (frameSkip % (sprint ? 1 : 3) == 0)
				{
					if (frame < 4)
					{
						frame++;
					}
					else
					{
						frame = 1;
					}
				}

			}
		}

		if (slashCount < 4)
		{
			if (frameSkip % 4 == 0)
			{
				slashCount++;
			}
		}
		else
		{
			slash = false;
		}
		//if (!slash)
		//{
			//source.x = 32 * frame;
			//bSrc.x = 32 * frame;
		//}
		if (slash)
		{
			source.x = 224 + slashCount * 32;
			eSrc.x = 32 * slashCount;
		}

		bSrc.x = 32 * frame;


		if (dmgCount > 1 && dmgCount < 25)
		{
			dmgCount++;
		}
		else
		{
			dmgCount = 1;
		}

	}

	int getHp()
	{
		return hp;
	}

	int getMaxHp()
	{
		return maxHp;
	}

	int getX()
	{
		return dest.x;
	}

	int getY()
	{
		return dest.y;
	}

	SDL_Rect getSrc()
	{
		return source;
	}
	
	SDL_Rect getDst()
	{
		return dest;
	}

	void moveL()
	{
		xVel = -5;
	}

	void moveR()
	{
		xVel = 5;
	}

	void moveUp()
	{
		dest.y -= 5;
	}

	void moveDown()
	{

		dest.y += 5;
	}

	void stop()
	{
		xVel = 0;
	}

	void Lstop()
	{
		if (xVel < 0)
		{
			xVel = 0;
		}
	}
	
	void Rstop()
	{
		if (xVel > 0)
		{
			xVel = 0;
		}
	}

	void onSprint()
	{
		//if (onGround)
		{
			sprint = true;
		}
	}

	void offSprint()
	{
		sprint = false;
	}

	bool newJump()
	{
		if (onGround == true)
		{
			onGround = false;
			yVel = -13;

			return true;
		}
		else
		{
			return false;
		}
	}

	void fallStop()
	{
		yVel = 0;
		onGround = true;
	}

	void dmg()
	{
		if (dmgCount == 1)
		{
			hp--;
			dmgCount++;
		}
		
	}

	bool GetFlicker()
	{
		if (dmgCount != 1)
		{
			if (dmgCount % 2 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else return false;
	}

	void melee()
	{
		slash = true;
		slashCount = 0;
	}

	void hpReset()
	{
		hp = 3;
	}
	void reset()
	{
		//hp = 3;

		yVel = 0;

		source = { 0, 25, 32, 29 };
		dest = { 510, 300, 32, 29 };

		bSrc = { 0, 54, 32, 12 };
		bDst = { 0, 0, 32, 12 };


		eSrc = { 160, 192, 32, 64 };
		eDst = { 0, 0, 40, 64 };

		stop();
	}

};
