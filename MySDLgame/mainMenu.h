#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

extern TTF_Font* font;
extern SDL_Surface* bgSurf;

void MainMenuStart(SDL_Renderer* renderer);
void MainMenuEvent(SDL_Event& event, char& gameState);
void MainMenuRender(SDL_Renderer* renderer, SDL_Event& event);
void MainMenuCleanup();