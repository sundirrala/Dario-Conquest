#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Credits
{
private:
	SDL_Texture* CreditTexture;
	SDL_Texture* BeerTexture;

	SDL_Surface* CreditSurface;

	SDL_Rect DarioSrc = {0, 283, 32, 37};
	SDL_Rect DarioDes = {600, 668, 64, 74};

	SDL_Rect GoombaSrc = {0, 0, 49, 67};
	SDL_Rect GoombaDes = {150, 660, 49, 67 };

	SDL_Rect EyeballSrc = {192, 96, 44, 44};
	SDL_Rect EyeballDes = {375, 680, 44, 44};

	SDL_Rect BeerSrc = {0, 0, 32, 32};
	SDL_Rect BeerDes = {700, 480, 270, 270};

	int iteration = 0, cycle = 0;
	bool amimation = false;

public:  // Animation
	
	void Render(SDL_Renderer* p, SDL_Texture* g, SDL_Texture* d) 
	{
		SDL_RenderCopy(p, CreditTexture, NULL, NULL);
		SDL_RenderCopy(p, BeerTexture, &BeerSrc, &BeerDes);
		SDL_RenderCopy(p, g, &DarioSrc, &DarioDes);
		SDL_RenderCopy(p, d, &GoombaSrc, &GoombaDes);
		SDL_RenderCopy(p, g, &EyeballSrc, &EyeballDes);
		
	}
	void Update() 
	{
		cycle++;
		if (cycle % 5 == 0) {
			iteration++;
			BeerSrc.x = 32 * (iteration % 20);
			DarioSrc.x = 32 * (iteration % 4);
			if (amimation == false)
			{
				EyeballDes.y--;
			}
			else if (amimation == true)
			{
				EyeballDes.y++;
			}
			if (EyeballDes.y == 650)
			{
				amimation = true;
			}
		}
		GoombaSrc.x = 64 * (cycle % 10);
	}
	void End();

	Credits(SDL_Renderer* p) 
	{
		CreditSurface = IMG_Load("Beer.png");
		if (CreditSurface == NULL)
			std::cout << "SURFACE FAIL \n\n";
		BeerTexture = SDL_CreateTextureFromSurface(p, CreditSurface);
		if (BeerTexture == NULL)
			std::cout << "TEXTURE FAIL \n\n";
		SDL_FreeSurface(CreditSurface);

		CreditSurface = IMG_Load("Credits.png");
		if (CreditSurface == NULL)
			std::cout << "SURFACE FAIL \n\n";
		CreditTexture = SDL_CreateTextureFromSurface(p, CreditSurface);
		if (CreditTexture == NULL)
			std::cout << "TEXTURE FAIL \n\n";
		SDL_FreeSurface(CreditSurface);
	}
	~Credits();
};

