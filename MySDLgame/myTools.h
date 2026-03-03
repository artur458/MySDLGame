#pragma once
#include <SDL.h>

extern Uint32 lastTime;

extern Uint32 currentTime;
extern float deltatime;

void toolsStart();
void toolsUpdate();

float deltaTime();
bool isHover(SDL_Rect& buttonRect);