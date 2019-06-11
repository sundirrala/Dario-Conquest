#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <cstring>
using namespace std;

class ScoreManager
{
private:
	const char* textScore = "SCORE:"; // text for SCORE TEXT
	const char* textNum = "000";; // constchar for score NUMBER
	SDL_Renderer* pRenderer = nullptr;
	int score;
	std::string newText; //string for TEXT
	std::string newScore; // string for SCORE
	SDL_Texture* tTextureText = nullptr; //Texture for SCORE text
	SDL_Texture* tTextureScore = nullptr; // texture for score NUMBER
	SDL_Color white = { 0,0,0 };
	SDL_Surface* tSurface = nullptr;
	SDL_Rect textR = { 500, 40 ,100,50 };
	SDL_Rect textR2 = { 390,50,100, 25 };
	TTF_Font* font = nullptr;
	
	static ScoreManager* instance; // Instance SINGLETONS
	ScoreManager(SDL_Renderer* pRend);

public:

	static ScoreManager* GetInstance(SDL_Renderer* pRend); // SINGLETON
	int GetScore() { return score; }
	void Render(SDL_Renderer* pRend);
	void Reset(SDL_Renderer* pRend);
	void AddScore(SDL_Renderer* pRend);

		/*if (score < 999)
		{
			score++;
			if (score < 10)
			{
				newScore = "00" + to_string(score);
			}
			else if (score < 100)
			{
				newScore = "0" + to_string(score);
			}
			else
			{
				newScore = to_string(score);
			}
			textNum = newScore.c_str();

			SDL_RenderCopy(pRenderer, tTextureText, NULL, &textR);
			SDL_RenderCopy(pRenderer, tTextureScore, NULL, &textR2);

		}*/
	/*void SetScore(int s)
	{

		if (score < 999)
		{
			score = s;
			if (score < 10)
			{
				newScore = "00" + to_string(score);
			}
			else if (score < 100)
			{
				newScore = "0" + to_string(score);
			}
			else
			{
				newScore = to_string(score);
			}
			textNum = newScore.c_str();

			SDL_RenderCopy(pRenderer, tTextureText, NULL, &textR);
			SDL_RenderCopy(pRenderer, tTextureScore, NULL, &textR2);
		}
	}*/
	~ScoreManager();

};

