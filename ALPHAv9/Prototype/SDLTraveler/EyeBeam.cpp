#include "EyeBeam.h"


EyeBeam::EyeBeam(int x, int y, SDL_RendererFlip f)
{
	eDst.y = y - 32;

	
	rDst.y = y -16;
	
	if (f == SDL_FLIP_NONE)
	{
		flip = SDL_FLIP_HORIZONTAL;
		eDst.x = x;
		rDst.x = x;
	}
	else
	{
		flip = SDL_FLIP_NONE;
		eDst.x = x - 64;
		rDst.x = x - 1024;

	}

}

int EyeBeam::Update(int x, int y, SDL_RendererFlip f)
{
	iteration++;

	eDst.x = x;
	eDst.y = y - 9;

	rDst.x = x;
	rDst.y = y + 6;

	if (f == SDL_FLIP_NONE)
	{
		flip = SDL_FLIP_HORIZONTAL;
		eDst.x = x - 16;
		rDst.x = x - 1020;

	}
	else
	{
		flip = SDL_FLIP_NONE;
		eDst.x = x - 5;
		rDst.x = x + 38;
	}

	if (iteration % 3 == 0)
	{

		if (chargeCount < 6)
		{
			chargeCount++;
			eSrc.x = chargeCount * 64;
		}
		else
		{
			eSrc.y = 64;
			eSrc.x = 64 * waveCount;
			if (waveCount < 6)
			{
				waveCount++;
			}
			else
			{
				waveCount = 0;
			}


			if (flicker < 3)
			{
				flicker++;
			}
			else
			{
				flicker = 0;
			}
		}

	}

	rSrc.y = 160 + (64 * flicker);

	if (waveCount == 6)
	{
		loopCount++;
	}

	if (loopCount < 1)
	{
		return 0;
	}
	else if (loopCount < 20)
	{
		status = 1;
		return 1;
	}
	else
	{
		status = 2;
		return 2;
	}
}

EyeBeam::~EyeBeam()
{
}
