#pragma once
#include "SDL_mixer.h"
class AudioManager
{
private:
	AudioManager();

	static AudioManager* AudioMan;

	Mix_Music* sMusic = nullptr;
	Mix_Music* sForest = nullptr;
	Mix_Music* sCombat = nullptr;
	Mix_Music* sDeath = nullptr;
	Mix_Music* sAlien = nullptr;
	Mix_Chunk* sJump = nullptr;
	Mix_Chunk* sFire = nullptr;
	Mix_Chunk* sFire2 = nullptr;
	Mix_Chunk* sPlat = nullptr;
	Mix_Chunk* sBoom = nullptr;
	Mix_Chunk* sCrackle = nullptr;
	Mix_Chunk* sSlash = nullptr;


public:
	static AudioManager* GetInstance();
	/*{
		if (AudioMan == nullptr)
		{
			AudioMan = new AudioManager;
			
		}
		return AudioMan;
	}
*/


	void Music1();

	void Music2();

	void Alien();

	void Forest();

	void Death();

	void Jump();
	
	void Fire();

	void Fire2();
	
	void Splat();
	
	void Boom();
	
	void Crackle();
	
	void Slash();
	
	~AudioManager();
};

