#pragma once
#include "SDL.h"
#include "GameObject.h"
class Door : public GameObject
{
private:
	int m_iFrame = 0, // Frame counter.
		m_iFrameMax = 4, // Number of frames to display each sprite.
		m_iSprite = 0, // Sprite counter.
		m_iSpriteMax = 4;
	bool open = false;
public:
	Door();
	Door(int x, int y);
	~Door();
	SDL_Rect GetSrc();
	void SetSrc(SDL_Rect a);
	SDL_Rect GetDst();
	void SetDst(int x, int y);

	bool GetOpen();
	void SetOpen(bool b);

	void animate();
};

