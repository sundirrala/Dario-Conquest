#pragma once
#include <iostream>
#include <string>
using namespace std;

class Sprite
{
protected:   // Public can be inherited, private cannot. Protected can be, but remains private thereafter.
	char m_cOutput;

public:
	char getC()
	{
		return m_cOutput;
	}
	void setC(char o)
	{
		m_cOutput = o;
	}
};

class Tile : public Sprite // public here means all members of Sprite become public in Tile.
{
private:
	bool m_blsObstacle;
	bool hazardTile;

	SDL_Rect source;
	SDL_Rect dest;


public:
	Tile()
	{
		m_blsObstacle = false;
		hazardTile = false;
	}
	bool isHazard()
	{
		return hazardTile;
	}
	void setHazard(bool h)
	{
		hazardTile = h;
	}

	bool IsObstacle()
	{
		return m_blsObstacle;
	}
	void SetObstacle(bool n)
	{
		m_blsObstacle = n;
	}
	void setTile(int sx1, int sy1, int dx1, int dy1)
	{
		//source = { sx1, sy1, 32, 32};
		//dest = { dx1, dy1, 32, 32};
		source.x = sx1;
		source.y = sy1;
		source.h = 32;
		source.w = 32;

		dest.x = dx1;
		dest.y = dy1;
		dest.h = 32;
		dest.w = 32;

	}

	SDL_Rect getSource()
	{
		return source;
	}
	SDL_Rect getDest()
	{
		return dest;
	}

};

class Player : public Sprite
{
private:
	int m_iX;
	int m_iY;
	bool isDead;

public:
	Player(int x, int y)
	{
		m_iX = x;
		m_iY = y;
		isDead = false;

		m_cOutput = '@';
	}
	bool getDead()
	{
		return isDead;
	}
	void death()
	{
		isDead = true;
	}
	int GetX()
	{
		return m_iX;
	}
	int GetY()
	{
		return m_iY;
	}
	void upX()
	{
		m_iX++;
	}
	void upY()
	{
		m_iY--;
	}
	void downX()
	{
		m_iX--;
	}
	void downY()
	{
		m_iY++;
	}
	void setPos(int x, int y)
	{
		m_iX = x;
		m_iY = y;
	}



};


class Door : public Tile
{
private:
	int m_iX;
	int m_iY;
	int toLevel;
	int destX;
	int destY;

public:
	Door()
	{
		m_cOutput = 'D';

		m_iX = 2000;
		m_iY = 2000;
		destX = 2000;
		destY = 2000;
	}

	void SetDoor(const int x, const int y, const int dX, const int dY, const int toLev)
	{
		m_iX = x;
		m_iY = y;
		destX = dX;
		destY = dY;
		toLevel = toLev;
	}
	int GetX()
	{
		return m_iX;
	}
	int GetY()
	{
		return m_iY;
	}
	int GetLevel()
	{
		return toLevel;
	}
	int GetDX()
	{
		return destX;
	}
	int GetDY()
	{
		return destY;
	}
};

class Level
{
private:
	int numDoors;
	Tile Map[24][32];
	Door mapDoors[3];

public:

	Level()
	{
		numDoors = 0;
	}
	void addDoor(const int x, const int y, const int dX, const int dY, const int toLev)
	{
		if (numDoors < 3) // Because 3 doors is the max. You can only add another if there are less than that.
		{
			mapDoors[numDoors].SetDoor(x, y, dX, dY, toLev);
			numDoors++;
		}
	}
	void setMap(int y, int x, char c) // I had to add this. I couldn't do it without this.
	{
		Map[y][x].setC(c);
	}
	void setObs(int y, int x, bool o)
	{
		Map[y][x].SetObstacle(o);
	}
	void setHaz(int y, int x, bool h)
	{
		Map[y][x].setHazard(h);
	}
	bool getObs(int y, int x)
	{
		return Map[y][x].IsObstacle();
	}
	bool getHaz(int y, int x)
	{
		return Map[y][x].isHazard();
	}
	char getTile(int y, int x)
	{
		return Map[y][x].getC();
	}
	int doorX(int d)
	{
		return mapDoors[d].GetX();
	}
	int doorY(int d)
	{
		return mapDoors[d].GetY();
	}
	char getDoorChar(int n)
	{
		return mapDoors[n].getC();
	}
	int getDoorX(int n)
	{
		return mapDoors[n].GetX();
	}
	int getDoorY(int n)
	{
		return mapDoors[n].GetY();
	}
	int getDoorDest(int n)
	{
		return mapDoors[n].GetLevel();
	}
	int getDoorDestX(int n)
	{
		return mapDoors[n].GetDX();
	}
	int getDoorDestY(int n)
	{
		return mapDoors[n].GetDY();
	}

	void setTile(int x, int y, int sx1, int sy1, int dx1, int dy1)
	{

		Map[x][y].setTile(sx1, sy1, dx1, dy1);

	}

	SDL_Rect getSource(int x, int y)
	{
		return Map[x][y].getSource();
	}
	SDL_Rect getDest(int x, int y)
	{
		return Map[x][y].getDest();
	}
};