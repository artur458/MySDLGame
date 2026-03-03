#include "gameScene.h"
#include <SDL_image.h>
#include "myTools.h"

SDL_Surface* playerSurf;
SDL_Texture* playerTexture;
SDL_Rect playerDstRect;

SDL_Surface* mapSurf;
SDL_Texture* mapTexture;
SDL_Rect mapRect;

SDL_Surface* itemSurf;
SDL_Texture* itemTexture;
SDL_Rect itemRect; 

SDL_RendererFlip flip;

void OnGameStart(SDL_Renderer* renderer) {
	playerSurf = IMG_Load("data/player.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurf);
	playerDstRect = { 800 / 2 - 50, 600 / 2-50, 100, 100 };

	mapSurf = IMG_Load("data/2.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurf);
	mapRect = { 400-1024, 300-1024, 2048, 2048 };

	itemSurf = IMG_Load("data/item.png");
	itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurf);
	itemRect = { 200, 200, 25, 25 };

	flip = SDL_FLIP_NONE;
}

void OnGameRender(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);
	SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerDstRect, NULL, NULL, flip);
	SDL_RenderCopy(renderer, itemTexture, NULL, &itemRect);
	
	// Логика поднятия предмета
	if (playerDstRect.x < itemRect.x + itemRect.w && playerDstRect.x + playerDstRect.w > itemRect.x &&
		playerDstRect.y < itemRect.y + itemRect.h && playerDstRect.y + playerDstRect.h > itemRect.y) {
		switch (flip) {
			case SDL_FLIP_NONE:
				itemRect.x = playerDstRect.x;
				itemRect.y = playerDstRect.y;
				break;
			case SDL_FLIP_HORIZONTAL:
				itemRect.x = playerDstRect.x + playerDstRect.w - itemRect.w;
				itemRect.y = playerDstRect.y;
		}
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_G]) {
			itemRect.x -= 100;
		}
	}

	if ( SDL_GetKeyboardState( NULL )[ SDL_SCANCODE_W ] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]    ) { playerDstRect.y -= 1 * deltaTime(); }
	if ( SDL_GetKeyboardState( NULL )[ SDL_SCANCODE_S ] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]  ) { playerDstRect.y += 1 * deltaTime(); }
	if ( SDL_GetKeyboardState( NULL )[ SDL_SCANCODE_A ] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]  ) { playerDstRect.x -= 1 * deltaTime(); flip = SDL_FLIP_NONE; }
	if ( SDL_GetKeyboardState( NULL )[ SDL_SCANCODE_D ] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] ) { playerDstRect.x += 1 * deltaTime(); flip = SDL_FLIP_HORIZONTAL; }
}

void OnGameCleanup() {
	SDL_FreeSurface(playerSurf);
	SDL_DestroyTexture(playerTexture);
	SDL_FreeSurface(mapSurf);
	SDL_DestroyTexture(mapTexture);
}