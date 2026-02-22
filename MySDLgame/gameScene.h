#pragma once
#include <SDL.h>

extern SDL_Surface* playerSurf;
extern SDL_Texture* playerTexture;
extern SDL_Rect playerDstRect;

extern SDL_Surface* mapSurf;
extern SDL_Texture* mapTexture;
extern SDL_Rect mapRect;

void OnGameStart(SDL_Renderer* renderer);
void OnGameRender(SDL_Renderer* renderer);
void OnGameCleanup();