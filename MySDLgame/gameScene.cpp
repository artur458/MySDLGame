#include "gameScene.h"

SDL_Surface* playerSurf;
SDL_Texture* playerTexture;
SDL_Rect playerDstRect;

void OnGameStart(SDL_Renderer* renderer) {
	playerSurf = IMG_Load("data/1.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurf);
	playerDstRect = { 800 / 2, 600 / 2, 100, 100 };
}