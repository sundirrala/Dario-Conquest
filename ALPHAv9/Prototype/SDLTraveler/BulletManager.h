#pragma once
#include "bullet.h"

class BulletManager
{
private:
	static BulletManager* clip;
	Bullet bullet[3];
	BulletManager();
	SDL_RendererFlip flip = SDL_FLIP_NONE;
public:
	static BulletManager* GetClip();

	void spawn(int a, int x, int y, SDL_RendererFlip f);
	void update(int a);
	void remove(int a);
	SDL_Rect GetDest(int a);
	SDL_Rect GetSrc(int a);
	SDL_RendererFlip GetFlip(int a);
	bool GetBallistic(int a);
	bool GetEdge(int a);

	~BulletManager();
};

