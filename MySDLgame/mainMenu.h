#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

extern TTF_Font* font;
extern SDL_Surface* bgSurf;
extern SDL_Surface* textSurface;
extern SDL_Surface* StartButtonSurf;

extern SDL_Rect bgRect;
extern SDL_Rect textRect;
extern SDL_Rect StartButtonRect;

extern SDL_Cursor* normalCursor;
extern SDL_Cursor* hoverCursor;

void MainMenuStart(SDL_Renderer* renderer);
void MainMenuEvent(SDL_Event& event, char& gameState);
void MainMenuRender(SDL_Renderer* renderer);
void MainMenuCleanup();