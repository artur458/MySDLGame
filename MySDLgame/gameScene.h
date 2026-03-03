#pragma once
#include <SDL.h>

extern SDL_Surface* playerSurf;
extern SDL_Texture* playerTexture;
extern SDL_Rect playerDstRect;

extern SDL_Surface* mapSurf;
extern SDL_Texture* mapTexture;
extern SDL_Rect mapRect;


extern SDL_Surface* itemSurf;
extern SDL_Texture* itemTexture;
extern SDL_Rect itemRect;

extern SDL_RendererFlip flip;

void OnGameStart(SDL_Renderer* renderer);
void OnGameRender(SDL_Renderer* renderer);
void OnGameCleanup();