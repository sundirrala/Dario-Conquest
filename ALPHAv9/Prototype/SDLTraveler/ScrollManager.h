#pragma once
class ScrollManager
{
private:
	static ScrollManager* Scroller;
	ScrollManager();

	int offSetX = 0;
	int offSetY = 0;

public:
	static ScrollManager* GetScroll();
	void Reset()
	{
		offSetX = 0;
	}

	int OffX()
	{
		return offSetX;
	}

	int OffY()
	{
		return offSetY;
	}

	void Scroll(int x)
	{
		offSetX += x;
	}

	~ScrollManager();
};

