#include "SDL.h"
#include "Game.h"
#define ROWS 24
#define COLS 32
using namespace std;

// Remember to include SDL2_image.lib in additional dependencies (under linker)
// Also remember to include zlib, libpng, SDL_image.dll in the same folder as main.

int main(int argc, char* args[])
{
	//Framerate stuff;
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;

	Game game;
	game.Init();

	bool gameOn = true;
	bool gameRunning = true;
	bool pausing = true;
	// Game stuff
	game.Start();

	while (gameRunning == true)
	{
		while (game.pausing == true)
		{

			while (game.endGame() == false)
			{
				//Framerate stuff;
				frameStart = SDL_GetTicks();

				game.HandleEvents();
				game.Update();
				game.Render();

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}


			}

			if (game.pauseGame == true)
			{
				game.Pause();
			}
		}
		//gameRunning = false;

		if (game.Over() == true)
		{

			game.Reset();
			//gameOn = true;
		}
		else
		{
			gameRunning = false;
		}

	}
	game.Clean();
	return 0;
}