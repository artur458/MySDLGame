#include "gameScene.h"
#include "myTools.h"
#include <SDL_image.h>

SDL_Surface* playerSurf;
SDL_Texture* playerTexture;
SDL_Rect playerDstRect;
SDL_Rect playerSrcRect;
bool isPlayerRunning;
bool isPlayerAlive;
float playerAnimTimer;

SDL_Surface* mapSurf;
SDL_Texture* mapTexture;
SDL_Rect mapRect;

SDL_Surface* itemSurf;
SDL_Texture* itemTexture;

SDL_Rect itemHealthRect;
SDL_Rect itemHealthSrcRect;

SDL_Rect itemSpikeRect;
SDL_Rect itemSpikeSrcRect;

SDL_RendererFlip flip;

void OnGameStart(SDL_Renderer* renderer) {
	playerSurf = IMG_Load("data/AnimationSheet.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurf);
	playerDstRect = { 800 / 2 - 50, 600 / 2 - 50, 100, 100 };
	playerSrcRect = { 0, 24, 24, 24 };
	playerAnimTimer = 0.f;
	isPlayerRunning = false;
	isPlayerAlive = true;

	mapSurf = IMG_Load("data/2.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurf);
	mapRect = { 400 - 1024, 300 - 1024, 2048, 2048 };

	itemSurf = IMG_Load("data/item.png");
	itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurf);
	itemHealthRect = { 200, 200, 25, 25 };
	itemHealthSrcRect = { 0, 0, 8, 8 };

	itemSpikeRect = { 400, 400, 25, 25 };
	itemSpikeSrcRect = { 8, 0, 8, 8 };

	flip = SDL_FLIP_NONE;
}

void OnGameRender(SDL_Renderer* renderer, SDL_Event& event) {
	SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);
	SDL_RenderCopyEx(renderer, playerTexture, &playerSrcRect, &playerDstRect, NULL, NULL, flip);
	SDL_RenderCopy(renderer, itemTexture, &itemHealthSrcRect, &itemHealthRect);
	SDL_RenderCopy(renderer, itemTexture, &itemSpikeSrcRect, &itemSpikeRect);

	if (inTrigger(playerDstRect, itemHealthRect)) {
		switch (flip) {
			case SDL_FLIP_NONE:
				itemHealthRect.x = playerDstRect.x;
				itemHealthRect.y = playerDstRect.y;
				break;
			case SDL_FLIP_HORIZONTAL:
				itemHealthRect.x = playerDstRect.x + playerDstRect.w - itemHealthRect.w;
				itemHealthRect.y = playerDstRect.y;
			}
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_G]) {
			itemHealthRect.x -= 100;
		}
	}
	if (isPlayerRunning) {
		playerSrcRect.y = 24;
		playerAnimTimer += deltaTime();
		if (playerAnimTimer >= 0.10f) { playerSrcRect.x += 24; playerAnimTimer = 0.f; }
		
		if (playerSrcRect.x >= 168) { playerSrcRect.x = 0; }
	}

	if (inTrigger(playerDstRect, itemSpikeRect) && isPlayerAlive != false) { isPlayerAlive = false; }
	switch (isPlayerAlive) {
		case false:
			playerSrcRect.y = 96;
			playerAnimTimer += deltaTime();
			if (playerAnimTimer >= 0.10f) { playerSrcRect.x += 24; playerAnimTimer = 0.f; }
			if (playerSrcRect.x >= 168) { OnGameStart(renderer); }
			break;
		case true:
			if ( isHover(playerDstRect) && event.button.button == SDL_BUTTON_LEFT) { SDL_OpenURL("https://penzilla.itch.io/protagonist-character"); }
			if      ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]    ) { playerDstRect.y -= 1; isPlayerRunning = true; }
			else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]  ) { playerDstRect.y += 1; isPlayerRunning = true; }
			else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]  ) { playerDstRect.x -= 1; flip = SDL_FLIP_HORIZONTAL; isPlayerRunning = true; }
			else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D] || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] ) { playerDstRect.x += 1; flip = SDL_FLIP_NONE; isPlayerRunning = true; }
			else { isPlayerRunning = false; }
			break;
	}
}

void OnGameCleanup() {
	SDL_FreeSurface(playerSurf);
	SDL_DestroyTexture(playerTexture);
	SDL_FreeSurface(mapSurf);
	SDL_DestroyTexture(mapTexture);
	SDL_FreeSurface(itemSurf);
	SDL_DestroyTexture(itemTexture);
}