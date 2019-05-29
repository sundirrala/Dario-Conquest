#pragma once
#include "SDL.h"


class Logo
{
private:
	SDL_Rect src = { 0,0,1024,768 };
	SDL_Rect dst = { 0,-768,1024,768 };
	int count = 0;
public:
	SDL_Rect getSrc() { return src; }
	SDL_Rect getDst() { return dst; }

	void update()
	{
		count++;
		if (count % 2 == 0)//modulus slows down the speed of image movement. slow frame rate
		{
			dst.y+=4; //moves image on screen 
		}
		if (dst.y == 0)/*delays screen for 1 sec and continues moving image*/
		{
			SDL_Delay(100);
		}
	}

	//void render()
	//{
	//	SDL_RenderClear(pRenderer); //clear the screen to draw color
	//	SDL_RenderCopy(pRenderer, sTexture, NULL, &logo.getDst());
	//	SDL_RenderPresent(pRenderer); // draw anew
	//}
};


