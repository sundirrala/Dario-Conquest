#pragma once
#include "bullet.h"
#include "Enemy.h"
#include "Platform.h"
#include "Player.h"
#include "Eyesplosion.h"
#include "Goomba.h"
//#include "Goomblast.h"
#include "Health.h"
#include "Arrow.h"
#include "Eyebeam.h"
#include "Logo.h"
#include "AudioManager.h"
#include "Level.h"
#include "ScoreManager.h"
#include "Credits.h"

#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "SDL_ttf.h"
#include <string>


using namespace std;

class Game
{
private:
	Player player;
	Bullet* bullet[3] = { nullptr };
	Credits* credit;
	bool CreditsOn = false;

	Level* levels[4] = {nullptr};
	int currentLevel = 0;

	Arrow arrow;

	
	SDL_Rect hpSR1 = { 32, 0, 22, 22 };
	SDL_Rect hpSR2 = { 32, 0, 50, 22 };
	SDL_Rect hpSR3 = { 32, 0, 80, 22 };

	SDL_Rect hpDR1 = { 64, 64, 44, 44 };
	SDL_Rect hpDR2 = { 64, 64, 100, 44 };
	SDL_Rect hpDR3 = { 64, 64, 160, 44 };


	//SDL_Rect platformer = { 512, 400, 32, 37 };
	GameObject platformer;

	SDL_Rect i = { 0,0,0,0 };

	int grounded = 0;

	bool gameOn = true;

	// SDL stuff

	SDL_Window* pWindow = nullptr;
	SDL_Renderer* pRenderer = nullptr;
	SDL_Texture* pTexture = nullptr;
	SDL_Texture* eTexture = nullptr;
	SDL_Texture* gTexture = nullptr;
	SDL_Texture* bTexture = nullptr;
	SDL_Texture* goTexture = nullptr;
	SDL_Texture* lTexture = nullptr;
	SDL_Texture* sTexture = nullptr;
	SDL_Texture* pauseTexture = nullptr;
	SDL_Texture* pauseBGTexture = nullptr;

	SDL_Surface* pSurface = nullptr;

	Platform* floor[20];

	const char* num;
	int iNum = 0;
	string newNum;

	const char* num2;
	int iNum2 = 0;
	string newNum2;

	TTF_Font* font1 = nullptr;
	SDL_Color white = { 0,0,0 };
	SDL_Surface* tSurface = nullptr;
	SDL_Texture* tTexture = nullptr;
	SDL_Texture* tTexture2 = nullptr;

	//string numberText;

	SDL_Rect textR = { 500, 40 ,100,50 };
	SDL_Rect textR2 = { 390,50,100, 25 };
	
	SDL_GameController* controller1 = nullptr;
	SDL_Event event;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	//Mix_Music* sMusic = nullptr;

	//Mix_Chunk* sJump = nullptr;
	//Mix_Chunk* sFire = nullptr;
	//Mix_Chunk* sPlat = nullptr;
	//Mix_Chunk* sBoom = nullptr;
	//Mix_Chunk* sCrackle = nullptr;
	//Mix_Chunk* sSlash = nullptr;

	int pfSX0[20] = { 0, 128, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 126, 421, 747, 750, -100, -100, -100, -100, -100, -100, -100, -100 };
	int pfSY0[20] = { 768,768,768,768,768,768,768,768, 619, 619, 619, 200, -100, -100, -100, -100, -100, -100, -100, -100 };


	int pfX0[20] = { 0, 128, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 350, 550, 100, 850, 1024 + 350, 1024 + 550, 1024 + 100, 1024 + 850, 2048 + 350, 2048 + 550, 2048 + 100, 2048 + 750, };
	int pfY0[20] = { 594, 594, 594, 594, 594, 594, 594, 594, 440, 350, 500, 350, 440, 350, 500, 350,  440, 350, 500, 200, };

	int pfX1[20] = { 0, 128, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 350, 550, 100, 750, -100, -100, -100, -100, -100, -100, -100, -100 };
	int pfY1[20] = { 594, 594, 594, 594, 594, 594, 594, 594, 440, 350, 500, 200, -100, -100, -100, -100, -100, -100, -100, -100 };

	int pfX2[20] = { 0, 128, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 350, 550, 100, 750, -100, -100, -100, -100, -100, -100, -100, -100 };
	int pfY2[20] = { 594, 594, 594, 594, 594, 594, 594, 594, 440, 350, 500, 200, -100, -100, -100, -100, -100, -100, -100, -100 };




public:
	Game();

	bool pauseGame = false;
	
	bool pausing = true;

	void Init();

	void HandleEvents();

	void Update();

	void Render();

	void Clean();

	bool Over();

	bool Start();

	void Pause();

	void Reset();

	bool endGame()
	{
		if (gameOn == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	~Game();
};

