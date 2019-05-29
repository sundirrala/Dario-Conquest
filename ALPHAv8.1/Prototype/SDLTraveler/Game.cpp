#include "Game.h"
using namespace std;

Game::Game()
{
}




void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickUpdate();
	cout << SDL_NumJoysticks();

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller1 = SDL_GameControllerOpen(i);
			cout << "SUCCESS! HUZZAH!";
		}
		else cout << "FAIL! FUFFAH!";
	}

pWindow = SDL_CreateWindow("It's Dario's Conquest, motherfucker! Prepare to face your doom! [not affiliated with DOOM.]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);


	credit = new Credits(pRenderer);

	levels[0] = new Level(pRenderer, "SunshineStart.png", 0, 1, pfSX0, pfSY0);
	levels[0]->GetPlats(floor);

	ScoreManager::GetInstance(pRenderer)->Render(pRenderer);


	pSurface = IMG_Load("dariosprites.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (pTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("EyeDeath.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	eTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("Goomba.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	gTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("Goomblast.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	bTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("gameOver.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	goTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (goTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("eyeBeam.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	lTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);


	pSurface = IMG_Load("Logo3.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	sTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);


	SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 255);
	SDL_RenderClear(pRenderer);

	// Okay,  now let's try inputs.

	Mix_VolumeMusic(100);
	Mix_Volume(-1, 128);

	AudioManager::GetInstance()->Music1();

}

void Game::HandleEvents()
{

	while (SDL_PollEvent(&event))
	{
		
		// CONTROLLER CONTROLS ===================================================================================================================
		if (CreditsOn == true)
		{
			
			if (event.type == SDL_KEYDOWN) 
			{
				
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					CreditsOn = false;	
				}
			}
		}


		if (event.type == SDL_CONTROLLERAXISMOTION)
		{
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value > 10000)
					{
						flip = SDL_FLIP_NONE;
						player.moveR();

					}
					else if (event.caxis.value < -10000)
					{
						flip = SDL_FLIP_HORIZONTAL;
						player.moveL();

					}
					else //if (event.caxis.value > -10000 && event.caxis.value < 10000)
					{
						player.stop();
					}
				}
				if (event.caxis.axis == 1)
				{
					if (event.caxis.value > 10000)
					{
						if (currentLevel == 0) // For Pipes in Start screen 
						{
							if (player.getY() < 630 && player.GetGround())
							{
								if (player.getX() < 600 && player.getX() > 300)
								{
									levels[0]->StartGame();
									player.reset();
									cout << "LEVEL LOAD SUCCESS" << (player.getX() < 600 && player.getX() > 300);
								}
								else if (player.getX() < 300)
								{
									CreditsOn = true;

								}
								else gameOn = false;
							}
						}
					}

				}
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
				{
					if (!bullet.GetBallistic())
					{
						bullet.fire(player.getX(), (player.getY() + 15), flip);
						//Mix_PlayChannel(1, sFire, 0);

						AudioManager::GetInstance()->Fire();
					}

				}

			}

		}

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{

			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
			{
				gameOn = false;
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				player.moveL();
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				player.moveR();
				flip = SDL_FLIP_NONE;
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				player.onSprint();
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				if (CreditsOn == true)
				{
					CreditsOn = false;
				}
				if (player.newJump() == true)
				{
					//Mix_PlayChannel(3, sJump, 0);

					AudioManager::GetInstance()->Jump();
				}
				
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				if (!bullet.GetBallistic())
				{
					bullet.fire(player.getX(), (player.getY() + 15), flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);

					AudioManager::GetInstance()->Slash();
					player.melee();

				}
			}

		}

		if (event.type == SDL_CONTROLLERBUTTONUP)
		{

			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				player.Lstop();
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				player.Rstop();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				player.offSprint();
			}

		}

		// KEYBOARD CONTROLS =====================================================================================================================
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				player.moveL();
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				player.moveR();
				flip = SDL_FLIP_NONE;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				if (currentLevel == 0) // For Pipes in Start screen 
				{
					if (player.getY() < 630 && player.GetGround())
					{
						if (player.getX() < 600 && player.getX() > 300)
						{
							levels[0]->StartGame();
							player.reset();
							cout << "LEVEL LOAD SUCCESS" << (player.getX() < 600 && player.getX() > 300);
						}
						else if (player.getX() < 300)
						{
							CreditsOn = true;

						}
						else gameOn = false;
					}
				}
			}



			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameOn = false;
			}

			if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_w)
			{
				if (player.newJump() == true)
				{
					//Mix_PlayChannel(3, sJump, 0);

					AudioManager::GetInstance()->Jump();
				}
			}
			if (event.key.keysym.sym == SDLK_j)
			{
				if (!bullet.GetBallistic())
				{
					bullet.fire(player.getX(), (player.getY() + 15), flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
			}
			if (event.key.keysym.sym == SDLK_k)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);

					AudioManager::GetInstance()->Slash();
					player.melee();

				}
			}

			// SPRINT TOGGLE ON/OFF ====================================================

			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				if (player.GetSprint())
				{
					player.offSprint();
				}
				else if (!player.GetSprint())
				{
					player.onSprint();
				}
			}


		}

		// MOUSE CONTROL ===============================================================

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (!bullet.GetBallistic())
				{
					bullet.fire(player.getX(), (player.getY() + 15), flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);

					AudioManager::GetInstance()->Slash();
					player.melee();

				}
			}

		}

		// STOPS PLAYER MOVEMENT IF KEY IS LIFTED AFTER BEING PRESSED

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				player.Lstop();
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				player.Rstop();
			}
		}

	}

}

void Game::Update()
{
	if (currentLevel != 0)
	{
		if (levels[currentLevel]->Update(pRenderer, platformer, bullet.getDst(), player.getEdst(), player.GetSlash()) == 1)
		{
			player.dmg();
		}
	}
	if (levels[currentLevel]->GetRemoveBullet())
	{
		bullet.remove();
	}
	for (Platform* p : floor)
	{
		if (SDL_HasIntersection(&platformer, &p->getDst()))
		{
			if (player.getYvel() > 0 && (p->getY() - player.getY()) > 20)
			{
				player.fallStop();
				player.setY(p->getTop());

			}
		}
	}

	grounded = 0;
	for (Platform* p : floor)
	{
		if (SDL_HasIntersection(&platformer, &p->getDst()))
		{
			grounded++;
		}
	}
	if (grounded == 0)
	{
		player.setGround(false);
	}

	player.update(flip);
	platformer.y = player.getY() + 2;
	platformer.x = player.getX();

	if (player.getHp() == 0)
	{
		gameOn = false;
	}

	bullet.update();

	if (bullet.getEdge() == true)
	{
		bullet.remove();
	}

	if (player.getY() > 760)
	{
		gameOn = false;
	}

	if (levels[currentLevel]->advance())
	{
		player.reset();
		if (currentLevel < 3)
		{
			delete(levels[currentLevel]);
			levels[currentLevel] = nullptr;
			currentLevel++;
			if (currentLevel == 1)
			{
				levels[1] = new Level(pRenderer, "stage1.png", 2, 2, pfX0, pfY0);

				levels[1]->GetPlats(floor);

			}
			if (currentLevel == 2)
			{
				levels[2] = new Level(pRenderer, "level2bg.png", 4, 4, pfX1, pfY1);

				levels[2]->GetPlats(floor);

			}
			if (currentLevel == 3)
			{

				levels[3] = new Level(pRenderer, "level3bg.png", 6, 6, pfX2, pfY2);

				levels[3]->GetPlats(floor);
			}
		}
		else
		{
			gameOn = false;
		}

	}

	SDL_RenderClear(pRenderer);


}

void Game::Render()
{

	for (int i = 0; i < 20; i++)
	{
		SDL_RenderCopy(pRenderer, pTexture, &floor[i]->getSrc(), &floor[i]->getDst());
	}

	levels[currentLevel]->Render(pRenderer, pTexture, gTexture, eTexture, bTexture, lTexture);

	SDL_RenderCopyEx(pRenderer, pTexture, &bullet.getSrc(), &bullet.getDst(), 0, NULL, bullet.getFlip());

	// HEARTS 
	if (currentLevel != 0)
	{
		if (player.getHp() == 3)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR3, &hpDR3);
		}
		else if (player.getHp() == 2)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR2, &hpDR2);
		}
		else if (player.getHp() == 1)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR1, &hpDR1);
		}
	}

	if (player.GetSlash())
	{
		SDL_RenderCopyEx(pRenderer, pTexture, &player.getEsrc(), &player.getEdst(), 0, NULL, flip);
	}

	// SCORE 
	if (currentLevel != 0)
	{
		ScoreManager::GetInstance(pRenderer)->Render(pRenderer);
	}



	if (player.GetFlicker() == false)
	{
		SDL_RenderCopyEx(pRenderer, pTexture, &player.getBsrc(), &player.getBdst(), 0, NULL, flip);

		SDL_RenderCopyEx(pRenderer, pTexture, &player.getSrc(), &player.getDst(), 0, NULL, flip);
	}

	if (CreditsOn == true)
	{
		SDL_RenderClear(pRenderer);
		credit->Render(pRenderer, pTexture, gTexture);
		credit->Update();
	}

	SDL_RenderPresent(pRenderer);
}

bool Game::Start()
{
	Logo logo;
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	bool choice = false;

	bool playAgain = true;

	int LEFT = 220;
	int RIGHT = 650;

	int xVal = 100;
	while (choice == false)
	{
		logo.update();

		SDL_RenderClear(pRenderer); //clear the screen to draw color
		SDL_RenderCopy(pRenderer, sTexture, NULL, &logo.getDst());
		SDL_RenderPresent(pRenderer); // draw anew

		if (logo.getDst().y > 768)
		{
			choice = true;
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
				{
					choice = true;
				}

			}

			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					choice = true;
				}

			}

			if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value < -10000)
					{
						arrow.SetX(LEFT);
						playAgain = true;
					}
					if (event.caxis.value > 10000)
					{
						arrow.SetX(RIGHT);
						playAgain = false;
					}
				}
			}

		}

	}
	return playAgain;

}

bool Game::Over()
{

	bool choice = false;
	bool playAgain = true;

	int LEFT = 220;
	int RIGHT = 650;

	int xVal = 100;
	while (choice == false)
	{
		arrow.Update();

		SDL_RenderClear(pRenderer);
		SDL_RenderCopy(pRenderer, goTexture, NULL, NULL);
		SDL_RenderCopy(pRenderer, pTexture, &arrow.GetSrc(), &arrow.GetDst());
		SDL_RenderPresent(pRenderer);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
				{
					choice = true;
				}

			}

			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					choice = true;
				}

			}

			if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value < -10000)
					{
						arrow.SetX(LEFT);
						playAgain = true;
					}
					if (event.caxis.value > 10000)
					{
						arrow.SetX(RIGHT);
						playAgain = false;
					}
				}
			}

		}

	}
	return playAgain;

}

void Game::Reset()
{
	currentLevel = 0;
	player.reset();
	player.hpReset();

	levels[0] = new Level(pRenderer, "SunshineStart.png", 0, 1, pfSX0, pfSY0);
	levels[0]->GetPlats(floor);
	levels[1] = new Level(pRenderer, "stage1.png", 2, 2, pfX0, pfY0);
	levels[2] = new Level(pRenderer, "level2bg.png", 4, 4, pfX1, pfY1);
	levels[3] = new Level(pRenderer, "level3bg.png", 6, 6, pfX2, pfY2);

	gameOn = true;

	ScoreManager::GetInstance(pRenderer)->Reset(pRenderer);

}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyTexture(pTexture);
	SDL_DestroyTexture(eTexture);
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(goTexture);
	SDL_DestroyTexture(tTexture);
	SDL_DestroyTexture(tTexture2);
	SDL_DestroyTexture(bTexture);
	SDL_Quit();

}


Game::~Game()
{
}
