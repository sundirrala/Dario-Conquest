#pragma once
#include "SDL.h"
#include "Player.h"
#include "BulletManager.h"
#include "Platform.h"
#include "Enemy.h"
#include "Goomba.h"
#include "EyeBeam.h"
#include "Eyesplosion.h"
#include "Door.h"
//#include "Goomblast.h"
#include <string>
#include "SDL_image.h"
#include "ScoreManager.h"
//#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Beer.h"
#include "AudioManager.h"
#include "ScrollManager.h"
#include <ctime>

class Level
{
private:
	SDL_Texture* backGround = nullptr;
	SDL_Texture* pf1 = nullptr;
	SDL_Surface* bgSurface = nullptr;
	SDL_Rect cameraRect = { 0, 0, 1024, 768 }; // The render window where everything gets displayed, is able to move and have things move through it in scrolling section
	Beer* beer = nullptr;
	Platform* plat[20];
	Enemy* eye[20] = { nullptr };
	Eyesplosion* eyeBoom[20] = { nullptr };
	int popCount[20];
	EyeBeam* beam[20] = { nullptr };
	Goomba* goom[20] = { nullptr };
	Goomblast* goomBoom[20] = { nullptr };
	int boomCount[20] = { 0 };
	// Stuff for le door
	Door door;
	SDL_Texture* dTexture;
	int levelWidth, levelHeight; // This gets set to the height and width of whatever level the player is on
	bool levelAdvance = false;
	bool beerTaken = false;

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

	SDL_Rect textR = { 170, 40 ,100,50 };
	SDL_Rect textR2 = { 64,50,100, 25 };

public:
	void StartGame() 
	{
		//kills = 1;
		levelAdvance = true;
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
		backGround = SDL_CreateTextureFromSurface(pRend, bgSurface); // converts the background from an sdl surface to an sdl texture
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
		// Door stuff
		bgSurface = IMG_Load("Door_Sprite.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		dTexture = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (dTexture == nullptr)
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

		SDL_QueryTexture(backGround, NULL, NULL, &levelWidth, &levelHeight); // gets the height and width of the texture

		ScrollManager::GetScroll()->SetLimits(levelWidth);
	}

	void GetPlats(Platform* pf[])
	{
		for (int i = 0; i < 20; i++)
		{
			pf[i] = plat[i];
		}
	}

	int Update(SDL_Renderer* pRend, SDL_Rect p, SDL_Rect s ,bool slash)
	{
		// Door stuffs
		if (kills == endScore)
		{
			door.SetOpen(true);
			if (beer == nullptr && beerTaken == false)
			{
				beer = new Beer(pRend);
			}
			
		}
		if (door.GetOpen() == true && SDL_HasIntersection(&door.GetDst(), &p))
		{
			// Selecting random plat and spawns door on it
			int platSelect = rand() % 20;
			door.SetDst(plat[platSelect]->getX(), plat[platSelect]->getY());
			SDL_RenderCopy(pRend, dTexture, &door.GetSrc(), &door.GetDst());
			levelAdvance = true;
		}
		/* NEW FUNCHION PART does following changes the color to black 
		and white when the player finshes the level think of as a loading sceen  */

		if (levelAdvance == true)// moveing to next level 
		{
			
				// seting a new colour for the window 
				SDL_SetRenderDrawColor(pRend, 0, 0, 0, 0);
				// clearing the sceen 
				SDL_RenderClear(pRend);
				// drawing the colour black 
				SDL_RenderPresent(pRend);
				AudioManager::GetInstance()->Death();
				
				SDL_Delay(2000);
				/* NOTE having a image for the nice for the player */
		}
		
			
		

		playerDamage = 0;
		removeBullet = false;

		// SCROLLING:
		// Allows for scrolling based off dario

		int offSetX = ScrollManager::GetScroll()->OffX(); 
		int offSetY = ScrollManager::GetScroll()->OffY(); 

		cameraRect.x = 0 - offSetX; 
		cameraRect.y = 0 - offSetY; 
		
		// Keeps the camera from scrolling past the level


		if (cameraRect.x < 0)
		{
			cameraRect.x = 0;
		}
		if (cameraRect.y < 0)
		{
			cameraRect.y = 0;
		}





		// Stops the camera from scrolling once it reaches the edge of the level

		if (cameraRect.x + cameraRect.w >= levelWidth)
		{
			cameraRect.x = levelWidth - 1024;
			
		}
		if (cameraRect.y + cameraRect.h >= levelHeight)
		{
			cameraRect.y = levelHeight - 768;
		}

		// Door scroll

		door.Scroll(offSetX, 0);
/*
		if (p.x > 600)
		{
			offSetX = 600 - p.x;
		}
*/
		// "SCROLLING" her

		// SCROLLING PLATFORMS
		for (Platform* pf : plat)
		{
			pf->Scroll(offSetX, 0);
		}

		//SCROLLING GOOMBAS
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				goom[i]->Scroll(offSetX, 0);
			}
			if (goomBoom[i] != nullptr)
			{
				goomBoom[i]->Scroll(offSetX, 0);
			}
		}

		//SCROLLING EYES
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				eye[i]->Scroll(offSetX, 0);
			}
			if (eyeBoom[i] != nullptr)
			{
				eyeBoom[i]->Scroll(offSetX, 0);
			}
			if (beam[i] != nullptr)
			{
				beam[i]->Scroll(offSetX, 0);
			}
		}

		if (beer)
		{
			beer->Scroll(offSetX, 0);
		}

		// END SCROLL STUFF

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
						AudioManager::GetInstance()->Punch();
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
						AudioManager::GetInstance()->Burn();
					}

					if (eye[i]->GetOnTarget() == 1 && eye[i]->GetOnScreen())
					{
						if (!beam[i])
						{
							beam[i] = new EyeBeam(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
							AudioManager::GetInstance()->Laser();
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
							int chance;
							chance = rand() % 2 + 1;
							cout << chance << endl;

							if (chance == 1 || 0)
							{
								goom[i]->damage(0);
								Mix_HaltChannel(4);
								AudioManager::GetInstance()->Clang();
							}

							else if (chance == 2);
							{
								goom[i]->damage(1);
								AudioManager::GetInstance()->Crackle();
								//GoombaHP--;
								//delete(bullet);
								//bullet = nullptr;
							}

							//Mix_PlayChannel(4, sCrackle, 0);

							if (goom[i]->GetHP() == 0)
							{
								goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
								boomCount[i] = 0;

								goom[i]->Remove();
								kills++;
								ScoreManager::GetInstance(pRend)->AddScore(pRend,1);
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
							ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
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
			for (int b = 0; b < 3; b++)
			{


				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (SDL_HasIntersection(&BulletManager::GetClip()->GetDest(b), &eye[i]->getDst()))
						{
							eyeBoom[i] = new Eyesplosion(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
							popCount[i] = 0;

							//Mix_PlayChannel(2, sBoom, 0);

							AudioManager::GetInstance()->Boom();

							eye[i]->Remove();
							kills++;
							BulletManager::GetClip()->remove(b);
							//removeBullet = true;

							ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
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


		for (int i = 0; i < MAXGOOMS; i++)
		{
			for (int b = 0; b < 3; b++)
			{
				if (goom[i] != nullptr)
				{
					if (goom[i]->GetAlive())
					{
						if (SDL_HasIntersection(&BulletManager::GetClip()->GetDest(b), &goom[i]->getDst()))
						{
							goom[i]->damage(6);

							BulletManager::GetClip()->remove(b);
							//removeBullet = true;

							//Mix_PlayChannel(4, sCrackle, 0);

							AudioManager::GetInstance()->Crackle();

							if (goom[i]->GetHP() <= 0)
							{
								goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
								boomCount[i] = 0;

								goom[i]->Remove();
								kills++;
								ScoreManager::GetInstance(pRend)->AddScore(pRend, 1);
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
							if (SDL_HasIntersection(&beam[i]->GetbDst(), &p))
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
						Mix_HaltChannel(8);
					}
				}
			}
		}


		if (beer)
		{
			beer->Update();
			if (SDL_HasIntersection(&p, &beer->GetDst()))
			{
				playerDamage = 3;
				delete(beer);
				beer = nullptr;
				beerTaken = true;
			}
		}

		return playerDamage;
	}

	void Render(SDL_Renderer* pRen, SDL_Texture* eyeText, SDL_Texture* goomText, SDL_Texture* eyePopText,
		SDL_Texture* goomBlastText, SDL_Texture* eyeBeamText)
	{
		SDL_RenderCopy(pRen, backGround, &cameraRect, NULL);
		if (MAXGOOMS > 0) 
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
					SDL_RenderCopyEx(pRen, eyeBeamText, &beam[i]->GetbSrc(), &beam[i]->GetbDst(), 0, NULL, beam[i]->GetFlip());
				}
			}
		}

		if (beer)
		{
			beer->Render(pRen);
		}

		SDL_RenderCopy(pRen, tTexture, NULL, &textR);
		SDL_RenderCopy(pRen, tTexture2, NULL, &textR2);
		if (door.GetOpen() == true)
		{
			SDL_RenderCopy(pRen, dTexture, &door.GetSrc(), &door.GetDst());
		}
		door.animate();
	}

	bool advance()
	{
		return levelAdvance;
	}

	int GetRemoveBullet()
	{
		return removeBullet;
	}

	~Level();
};

