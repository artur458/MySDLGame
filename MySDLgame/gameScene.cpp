#include "gameScene.h"
#include <SDL_image.h>

SDL_Surface* playerSurf;
SDL_Texture* playerTexture;
SDL_Rect playerDstRect;

SDL_Surface* mapSurf;
SDL_Texture* mapTexture;
SDL_Rect mapRect;

void OnGameStart(SDL_Renderer* renderer) {
	playerSurf = IMG_Load("data/player.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurf);
	playerDstRect = { 800 / 2, 600 / 2, 100, 100 };

	mapSurf = IMG_Load("data/2.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurf);
	mapRect = { 0, 0, 1024, 1024 };
}

void OnGameRender(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerDstRect);

	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]) { playerDstRect.y -= 1; }
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]) { playerDstRect.y += 1; }
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]) { playerDstRect.x -= 1; }
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]) { playerDstRect.x += 1; }
}

void OnGameCleanup() {
	SDL_FreeSurface(playerSurf);
	SDL_DestroyTexture(playerTexture);
	SDL_FreeSurface(mapSurf);
	SDL_DestroyTexture(mapTexture);
}