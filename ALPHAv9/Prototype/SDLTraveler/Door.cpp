#include "Door.h"


Door::Door()
{
	rSrc = { 0, 0,  60, 120 };
	rDst = { 100, 500, 60, 120 };

	ObjInit();
}

Door::Door(int x, int y)
{
	rSrc = { 0, 0,  60, 120 };
	rDst = { x, y, 60, 120 };

	ObjInit();
}


Door::~Door()
{
}

SDL_Rect Door::GetSrc()
{
	return rSrc;
}

void Door::SetSrc(SDL_Rect a)
{
	rSrc = a;
}

SDL_Rect Door::GetDst()
{
	return rDst;
}

void Door::SetDst(int x, int y)
{
	rDst.x = x;
	rDst.y = y;
}

bool Door::GetOpen()
{
	return open;
}

void Door::SetOpen(bool b)
{
	open = b;
}

void Door::animate()
{
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
		{
			m_iSprite = 0;
		}
		rSrc.x = m_iSprite * rSrc.w;
	}
	m_iFrame++;
}
