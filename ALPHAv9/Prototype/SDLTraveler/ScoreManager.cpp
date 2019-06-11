#include "ScoreManager.h"
using namespace std;
ScoreManager* ScoreManager::instance;


ScoreManager* ScoreManager::GetInstance(SDL_Renderer* pRend)
{
	if (instance == nullptr)
	{
		instance = new ScoreManager(pRend);
	}
	return instance;
}

void ScoreManager::Render(SDL_Renderer* pRend)
{
	SDL_RenderCopy(pRend, tTextureText, NULL, &textR2);
	SDL_RenderCopy(pRend, tTextureScore, NULL, &textR);
}
ScoreManager::ScoreManager(SDL_Renderer* pRend)
{
	TTF_Init();
	font = TTF_OpenFont("SuperMario256.ttf", 24);
	if (font == NULL) {
		cout << "FONT FAIL  1 \n\n";

		cout << SDL_GetError()<<endl;
	}
	tSurface = TTF_RenderText_Solid(font, textScore, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  2 \n\n";
		cout << SDL_GetError();
	}
	tTextureText = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureText == NULL) {
		cout << "TEXTURE FAIL  3  \n\n";
		cout << SDL_GetError() << endl;
	}
	SDL_FreeSurface(tSurface);


	tSurface = TTF_RenderText_Solid(font, textNum, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  4 \n\n";
		cout << SDL_GetError() << endl;
	}
	tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureScore == NULL) {
		cout << "TEXTURE FAIL 5  \n\n";
	}
	SDL_FreeSurface(tSurface);
}

void ScoreManager::AddScore(SDL_Renderer* pRend)
{
	
	if (score < 999)
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

		tSurface = TTF_RenderText_Solid(font, textNum, white);
		if (tSurface == NULL) {
			cout << "SURFACE FAIL  4 \n\n";
			cout << SDL_GetError() << endl;
		}
		tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
		if (tTextureScore == NULL) {
			cout << "TEXTURE FAIL 5  \n\n";
			cout << SDL_GetError() << endl;
		}
		SDL_FreeSurface(tSurface);
	}
}
void ScoreManager::Reset(SDL_Renderer* pRend)
{


	score = 0;
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
	tSurface = TTF_RenderText_Solid(font, textNum, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  4 \n\n";
		cout << SDL_GetError() << endl;
	}
	tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureScore == NULL) {
		cout << SDL_GetError() << endl;
		cout << "TEXTURE FAIL 5  \n\n";
	}
	SDL_FreeSurface(tSurface);
}
ScoreManager::~ScoreManager() {}

