#pragma once
#include "SDL.h"
#include "Player.h"
#include "bullet.h"
#include "Platform.h"
#include "Enemy.h"
#include "Goomba.h"
#include "EyeBeam.h"
#include "Eyesplosion.h"
//#include "Goomblast.h"
#include <string>
#include "SDL_image.h"
#include "ScoreManager.h"
//#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "AudioManager.h"
#include <ctime>
#include <chrono>
class Level
{
private:
	SDL_Texture* backGround = nullptr;
	SDL_Texture* pf1 = nullptr;
	SDL_Surface* bgSurface = nullptr;
	SDL_Rect screenRect = { 0, 0, 1024, 768 };

	Platform* plat[20];
	Enemy* eye[20] = { nullptr };
	Eyesplosion* eyeBoom[20] = { nullptr };
	int popCount[20];
	EyeBeam* beam[20] = { nullptr };
	Goomba* goom[20] = { nullptr };
	Goomblast* goomBoom[20] = { nullptr };
	int boomCount[20] = { 0 };

	int startTime;
	int MAXEYES = 0;
	int MAXGOOMS = 0;

	int endScore = 0;
	int kills = 0;

	int playerDamage = 0;
	bool removeBullet = false;

	const char* num = "000";
	int iNum = 0;
	std::string newNum;

	const char* num2 = "SCORE:";
	int iNum2 = 0;
	std::string newNum2;

	TTF_Font* font1 = nullptr;
	SDL_Color white = { 0,0,0 };
	SDL_Surface* lSurface = nullptr;
	SDL_Texture* tTexture = nullptr;
	SDL_Texture* tTexture2 = nullptr;

	//string numberText;

	SDL_Rect textR = { 500, 40 ,100,50 };
	SDL_Rect textR2 = { 390,50,100, 25 };

public:
	void StartGame() 
	{
		kills = 1;
	}
	Level();
	Level(SDL_Renderer* pRend, const char* bgName, int MAXEYES, int MAXGOOMS, int platX[], int platY[])
	{
		srand(time(NULL));
		startTime = SDL_GetTicks();
		bgSurface = IMG_Load(bgName);
		if (bgSurface == nullptr)
		{
			std::cout << "BACKGROUND SURFACE FAIL!" << std::endl << std::endl;
		}
		backGround = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (backGround == nullptr)
		{
			std::cout << "BACKGROUND TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}

		bgSurface = IMG_Load("Level1Platform.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		pf1 = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (pf1 == nullptr)
		{
			std::cout << "PLATFORM TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}

		for (int i = 0; i < 20; i++)
		{
			plat[i] = new Platform;
			plat[i]->setPlatform(platX[i], platY[i]);
		}

		this->MAXEYES = MAXEYES;
		this->MAXGOOMS = MAXGOOMS;

		endScore = MAXEYES + MAXGOOMS;
	}

	void GetPlats(Platform* pf[])
	{
		for (int i = 0; i < 20; i++)
		{
			pf[i] = plat[i];
		}
	}

	int Update(SDL_Renderer* pRend, SDL_Rect p, SDL_Rect b, SDL_Rect s, bool slash)
	{
		playerDamage = 0;
		removeBullet = false;
		// Delayed spawn
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] == nullptr)
			{
				if (SDL_GetTicks() > startTime + (i * 3000))
				{
					eye[i] = new Enemy;
					eye[i]->Spawn();
				}
			}
		}
		// Update for Eye
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				eye[i]->update(p.x, p.y);
			}
		}
		// Delayed Goomba spawn
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] == nullptr)
			{
				if (SDL_GetTicks() > startTime + (i * 3000))
				{
					goom[i] = new Goomba(-100, -100);
					goom[i]->Spawn();
				}
			}
		}
		// Update for Gooms
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				if (goom[i]->GetAlive())
				{
					goom[i]->update();

					if (SDL_HasIntersection(&p, &goom[i]->getDst()))
					{
						playerDamage = 1;
					}
				}
			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				if (eye[i]->GetAlive())
				{
					eye[i]->update(p.x, p.y);

					if (SDL_HasIntersection(&p, &eye[i]->getDst()))
					{
						playerDamage = 1;
					}

					if (eye[i]->GetOnTarget() == 1)
					{
						if (!beam[i])
						{
							beam[i] = new EyeBeam(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
						}
					}

				}
			}
		}

		if (slash)
		{
			for (int i = 0; i < MAXGOOMS; i++)
			{
				if (goom[i] != nullptr)
				{
					if (goom[i]->GetAlive())
					{
						if (SDL_HasIntersection(&goom[i]->getDst(), &s))
						{
							goom[i]->damage(1);
							//GoombaHP--;
							//delete(bullet);
							//bullet = nullptr;

							AudioManager::GetInstance()->Crackle();
							//Mix_PlayChannel(4, sCrackle, 0);

							if (goom[i]->GetHP() == 0)
							{
								goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
								boomCount[i] = 0;

								goom[i]->Remove();
								kills++;
								ScoreManager::GetInstance(pRend)->AddScore(pRend);
								//bullet = nullptr;

							}
						}
					}
				}

				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (SDL_HasIntersection(&eye[i]->getDst(), &s))
						{
							eyeBoom[i] = new Eyesplosion(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
							popCount[i] = 0;

							//Mix_PlayChannel(2, sBoom, 0);

							AudioManager::GetInstance()->Boom();

							eye[i]->Remove();

							kills++;
							ScoreManager::GetInstance(pRend)->AddScore(pRend);
							//delete(bullet);
							//bullet = nullptr;


							if (iNum < 999)
							{
								iNum++;
								if (iNum < 10)
								{
									newNum = "00" + std::to_string(iNum);
								}
								else if (iNum < 100)
								{
									newNum = "0" + std::to_string(iNum);
								}
								else
								{
									newNum = std::to_string(iNum);
								}
								num = newNum.c_str();

								/*
								lSurface = TTF_RenderText_Solid(font1, num, white);
								if (lSurface == NULL)
									std::cout << "SURFACE FAIL \n\n";
								// Maybe free the texture somehow?
								tTexture = SDL_CreateTextureFromSurface(pRend, lSurface);
								if (tTexture == NULL)
									std::cout << "TEXTURE FAIL \n\n";
								SDL_FreeSurface(lSurface);
								*/
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				if (eye[i]->GetAlive())
				{
					if (SDL_HasIntersection(&b, &eye[i]->getDst()))
					{
						eyeBoom[i] = new Eyesplosion(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
						popCount[i] = 0;

						//Mix_PlayChannel(2, sBoom, 0);

						AudioManager::GetInstance()->Boom();

						eye[i]->Remove();
						kills++;
						removeBullet = true;

						ScoreManager::GetInstance(pRend)->AddScore(pRend);
						if (iNum < 999)
						{
							iNum++;
							if (iNum < 10)
							{
								newNum = "00" + std::to_string(iNum);
							}
							else if (iNum < 100)
							{
								newNum = "0" + std::to_string(iNum);
							}
							else
							{
								newNum = std::to_string(iNum);
							}
							num = newNum.c_str();

							/*
							lSurface = TTF_RenderText_Solid(font1, num, white);
							if (lSurface == NULL)
								std::cout << "SURFACE FAIL \n\n";
							// Maybe free the texture somehow?
							tTexture = SDL_CreateTextureFromSurface(pRend, lSurface);
							if (tTexture == NULL)
								std::cout << "TEXTURE FAIL \n\n";
							SDL_FreeSurface(lSurface);
							*/
						}

					}
				}
			}
		}


		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				if (goom[i]->GetAlive())
				{
					if (SDL_HasIntersection(&b, &goom[i]->getDst()))
					{
						goom[i]->damage(6);

						removeBullet = true;

						//Mix_PlayChannel(4, sCrackle, 0);

						AudioManager::GetInstance()->Crackle();

						if (goom[i]->GetHP() <= 0)
						{
							goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
							boomCount[i] = 0;

							goom[i]->Remove();
							kills++;
							ScoreManager::GetInstance(pRend)->AddScore(pRend);
							//bullet = nullptr;

							if (iNum < 999)
							{
								iNum++;
								if (iNum < 10)
								{
									newNum = "00" + std::to_string(iNum);
								}
								else if (iNum < 100)
								{
									newNum = "0" + std::to_string(iNum);
								}
								else
								{
									newNum = std::to_string(iNum);
								}
								num = newNum.c_str();

								/*
								lSurface = TTF_RenderText_Solid(font1, num, white);
								if (lSurface == NULL)
									std::cout << "SURFACE FAIL \n\n";
								// Maybe free the texture somehow?
								tTexture = SDL_CreateTextureFromSurface(pRend, lSurface);
								if (tTexture == NULL)
									std::cout << "TEXTURE FAIL \n\n";
								SDL_FreeSurface(lSurface);
								*/
							}


						}
					}
				}
			}
		}

		for (int i = 0; i < MAXGOOMS; i++) {
			if (goomBoom[i])
			{
				goomBoom[i]->update();
				boomCount[i]++;

				if (boomCount[i] == 30)
				{
					//Mix_PlayChannel(5, sPlat, 0);

					AudioManager::GetInstance()->Splat();

				}
				if (boomCount[i] == 60)
				{
					delete(goomBoom[i]);
					goomBoom[i] = nullptr;

				}

			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			if (eyeBoom[i])
			{
				eyeBoom[i]->update();
				popCount[i]++;

				if (popCount[i] == 24)
				{
					delete(eyeBoom[i]);
					eyeBoom[i] = nullptr;

				}

			}
		}

		/*
		if (player.getY() >= -37 + floor[0].getTop())
		{
			player.fallStop();
			player.setY(-37 + floor[0].getTop());
		}
		*/
		for (int i = 0; i < MAXEYES; i++)
		{
			if (beam[i])
			{
				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (beam[i]->Update(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip()) == 1)
						{
							if (SDL_HasIntersection(&beam[i]->GetrDst(), &p))
							{
								playerDamage = 1;
							}
						}
						if (beam[i]->GetStatus() == 2)
						{
							delete(beam[i]);
							beam[i] = nullptr;
						}
					}
					else
					{
						delete(beam[i]);
						beam[i] = nullptr;
					}
				}
			}
		}
		return playerDamage;
	}

	void Render(SDL_Renderer* pRen, SDL_Texture* eyeText, SDL_Texture* goomText, SDL_Texture* eyePopText,
		SDL_Texture* goomBlastText, SDL_Texture* eyeBeamText)
	{
		SDL_RenderCopy(pRen, backGround, &screenRect, NULL);
		if (MAXEYES > 0) 
		{
			for (int i = 8; i < 20; i++)
			{
				SDL_RenderCopy(pRen, pf1, &plat[i]->getSrc(), &plat[i]->getDst());
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eyeBoom[i])
			{
				SDL_RenderCopyEx(pRen, eyePopText, &eyeBoom[i]->getSrc(), &eyeBoom[i]->getDst(), 0, NULL, eyeBoom[i]->getFlip());
			}
		}
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goomBoom[i])
			{
				SDL_RenderCopyEx(pRen, goomBlastText, &goomBoom[i]->getSrc(), &goomBoom[i]->getDst(), 0, NULL, SDL_FLIP_NONE);
			}
		}
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				if (goom[i]->GetAlive())
				{
					SDL_RenderCopyEx(pRen, goomText, &goom[i]->getSrc(), &goom[i]->getDst(), 0, NULL, goom[i]->getFlip());
				}
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				if (eye[i]->GetAlive())
				{
					SDL_RenderCopyEx(pRen, eyeText, &eye[i]->getSrc(), &eye[i]->getDst(), 0, NULL, eye[i]->getFlip());
				}
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (beam[i])
			{
				SDL_RenderCopyEx(pRen, eyeBeamText, &beam[i]->GeteSrc(), &beam[i]->GeteDst(), 0, NULL, beam[i]->GetFlip());

				if (beam[i]->GetStatus() == 1)
				{
					SDL_RenderCopyEx(pRen, eyeBeamText, &beam[i]->GetrSrc(), &beam[i]->GetrDst(), 0, NULL, beam[i]->GetFlip());
				}
			}
		}

		SDL_RenderCopy(pRen, tTexture, NULL, &textR);
		SDL_RenderCopy(pRen, tTexture2, NULL, &textR2);
	}

	bool advance()
	{
		if (kills == endScore)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int GetRemoveBullet()
	{
		return removeBullet;
	}

	~Level();
};

