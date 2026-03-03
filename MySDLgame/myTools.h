#pragma once
#include <SDL.h>

extern Uint32 lastTime;

extern Uint32 currentTime;
extern float deltatime;

void toolsStart();
void toolsEvent(SDL_Event& event);
void toolsUpdate();

float deltaTime();
bool isHover(SDL_Rect& buttonRect);
void SDL_RenderCopyShadow(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect& dstrect, int shadowX = 5, int shadowY = 5);
SDL_Point GetMousePos();