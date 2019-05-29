#pragma once
#include "SDL_mixer.h"
class AudioManager
{
private:
	AudioManager();

	static AudioManager* AudioMan;

	Mix_Music* sMusic = nullptr;

	Mix_Chunk* sJump = nullptr;
	Mix_Chunk* sFire = nullptr;
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

	void Jump();
	
	void Fire();
	
	void Splat();
	
	void Boom();
	
	void Crackle();
	
	void Slash();
	
	~AudioManager();
};

