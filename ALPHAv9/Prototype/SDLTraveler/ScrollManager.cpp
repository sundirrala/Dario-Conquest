#include "ScrollManager.h"

ScrollManager* ScrollManager::Scroller = nullptr;

ScrollManager::ScrollManager()
{
}


ScrollManager* ScrollManager::GetScroll()
{
	if (Scroller == nullptr)
	{
		Scroller = new ScrollManager;
	}
	return Scroller;
}

ScrollManager::~ScrollManager()
{
}
