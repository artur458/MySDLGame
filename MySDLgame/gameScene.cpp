#include "gameScene.h"
#include "myTools.h"
#include <SDL_image.h>

bool isPlayerRunning;
bool isPlayerAlive;
bool itemInHeands;
float playerAnimTimer;
int health;

SDL_Surface* mapSurf;
SDL_Surface* itemSurf;
SDL_Surface* playerSurf;

SDL_Texture* itemTexture;
SDL_Texture* mapTexture;
SDL_Texture* playerTexture;

SDL_Rect itemHealthRect;
SDL_Rect itemHealthSrcRect;

SDL_Rect itemSpikeRect;
SDL_Rect itemSpikeSrcRect;

SDL_Rect HealthRect;
SDL_Rect HealthSrcRect;

SDL_Rect mapRect;
SDL_Rect playerDstRect;
SDL_Rect playerSrcRect;

SDL_RendererFlip flip;

void OnGameStart(SDL_Renderer* renderer) {
	playerSurf = IMG_Load("data/AnimationSheet.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurf);
	playerDstRect = { 800 / 2 - 50, 600 / 2 - 50, 100, 100 };
	playerSrcRect = { 0, 24, 24, 24 };
	playerAnimTimer = 0.f;
	isPlayerRunning = false;
	isPlayerAlive = true;
	itemInHeands = false;
	mapSurf = IMG_Load("data/2.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurf);
	mapRect = { 400 - 1024, 300 - 1024, 2048, 2048 };

	itemSurf = IMG_Load("data/item.png");
	itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurf);
	itemHealthRect = { 200, 200, 25, 25 };
	itemHealthSrcRect = { 0, 0, 8, 8 };

	HealthRect = { 0, 0, 50, 50 };
	HealthSrcRect = { 16, 0, 8, 8 };
	health = 3;

	itemSpikeRect = { 400, 400, 25, 25 };
	itemSpikeSrcRect = { 8, 0, 8, 8 };

	flip = SDL_FLIP_NONE;
}

void OnGameRender(SDL_Renderer* renderer, SDL_Event& event) {
	SDL_RenderCopy(renderer, mapTexture, NULL, &mapRect);
	SDL_RenderCopyEx(renderer, playerTexture, &playerSrcRect, &playerDstRect, NULL, NULL, flip);
	SDL_RenderCopy(renderer, itemTexture, &itemSpikeSrcRect, &itemSpikeRect);

	// -------------
	// Логика использования хилки
	// -------------
	HealthRect.x = 0;
	for (int i = 0; i < health; i++)
	{
		SDL_RenderCopy(renderer, itemTexture, &HealthSrcRect, &HealthRect);
		HealthRect.x += HealthRect.w + 1;
	}
	if (itemInHeands == false)
		SDL_RenderCopy(renderer, itemTexture, &itemHealthSrcRect, &itemHealthRect);
	if (inTrigger(playerDstRect, itemHealthRect) && itemInHeands == false) {
			
		itemInHeands = true;
		health++;
		//itemHealthRect.x = playerDstRect.x + playerDstRect.w / 2;
		//itemHealthRect.y = playerDstRect.y + playerDstRect.h / 2;
		//if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_G]) {
		//	switch (flip) {
		//	case SDL_FLIP_HORIZONTAL:
		//	itemHealthRect.x -= 100;
		//	break;
		//	case SDL_FLIP_NONE:
		//	itemHealthRect.x += 100;
		//	break;
		//	}
		//}
	}
	// -------------
	// Логика смерти и анимации игрока
	// -------------
	if (isPlayerRunning) {
		playerSrcRect.y = 24;
		playerAnimTimer += deltaTime();
		if (playerAnimTimer >= 0.10f) { playerSrcRect.x += 24; playerAnimTimer = 0.f; }
		if (playerSrcRect.x >= 168) { playerSrcRect.x = 0; }
	}
	else { playerSrcRect.x = 0; playerSrcRect.y = 120; }
	
	if (inTrigger(playerDstRect, itemSpikeRect) && isPlayerAlive != false) { health--; playerDstRect.x = 800 / 2 - 50; playerDstRect.y = 600 / 2 - 50; }
	if (health <= 0) { isPlayerAlive = false; }
	switch (isPlayerAlive) {
		case false:           // Игрок умер
			playerSrcRect.y = 96;
			playerAnimTimer += deltaTime();
			if (playerAnimTimer >= 0.10f) { playerSrcRect.x += 24; playerAnimTimer = 0.f; }
			if (playerSrcRect.x >= 168) { OnGameStart(renderer); }
			break;

		case true:            // Игрок жив
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
	SDL_DestroyTexture(itemTexture);
	SDL_DestroyTexture(mapTexture);
	SDL_DestroyTexture(playerTexture);

	SDL_FreeSurface(playerSurf);
	SDL_FreeSurface(mapSurf);
	SDL_FreeSurface(itemSurf);
}