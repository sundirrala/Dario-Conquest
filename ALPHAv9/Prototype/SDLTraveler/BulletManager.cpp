#include "BulletManager.h"

BulletManager* BulletManager::clip = nullptr;

BulletManager::BulletManager()
{
}


BulletManager* BulletManager::GetClip()
{
	if (clip == nullptr)
	{
		clip = new BulletManager;
		return clip;
	}
	return clip;
}

void BulletManager::spawn(int a, int x, int y, SDL_RendererFlip f)
{
	bullet[a].fire(x, y, f);
}

void BulletManager::update(int a)
{
	bullet[a].update();
}

void BulletManager::remove(int a)
{
	bullet[a].remove();
}

SDL_Rect BulletManager::GetDest(int a)
{
	return bullet[a].getDst();
}

SDL_Rect BulletManager::GetSrc(int a)
{
	return bullet[a].getSrc();
}

SDL_RendererFlip BulletManager::GetFlip(int a)
{
	return bullet[a].getFlip();
}


bool BulletManager::GetBallistic(int a)
{
	return bullet[a].GetBallistic();
}

bool BulletManager::GetEdge(int a)
{
	return bullet[a].getEdge();
}

BulletManager::~BulletManager()
{
}
