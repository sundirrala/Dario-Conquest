#include "AudioManager.h"

AudioManager* AudioManager::AudioMan;

AudioManager::AudioManager()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	Mix_AllocateChannels(16);

	sMusic = Mix_LoadMUS("Dario-SongBG_1.wav");
	sJump = Mix_LoadWAV("jump.wav");
	sFire = Mix_LoadWAV("fire.wav");
	sPlat = Mix_LoadWAV("splat.wav");
	sBoom = Mix_LoadWAV("boom.wav");
	sCrackle = Mix_LoadWAV("buzz.wav");
	sSlash = Mix_LoadWAV("Slash.wav");

	Mix_VolumeMusic(100);
	Mix_Volume(-1, 128);	

}

AudioManager* AudioManager::GetInstance()
{
	if (AudioMan == nullptr)
	{
		AudioMan = new AudioManager;

	}
	return AudioMan;
}

void AudioManager::Music1()
{
	Mix_PlayMusic(sMusic, -1);
}
void AudioManager::Jump()
{
	Mix_PlayChannel(3, sJump, 0);
}
void AudioManager::Fire()
{
	Mix_PlayChannel(1, sFire, 0);
}
void AudioManager::Splat()
{
	Mix_PlayChannel(5, sPlat, 0);
}
void AudioManager::Boom()
{
	Mix_PlayChannel(2, sBoom, 0);

}
void AudioManager::Crackle()
{
	Mix_PlayChannel(4, sCrackle, 0);
}
void AudioManager::Slash()
{
	Mix_PlayChannel(1, sSlash, 0);
}

AudioManager::~AudioManager()
{
}
