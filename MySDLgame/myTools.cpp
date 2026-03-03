#include "myTools.h"
#include <SDL.h>

Uint32 lastTime;

Uint32 currentTime;
float deltatime;

int mouseX, mouseY;
void toolsStart() {
	lastTime = SDL_GetTicks();
}

void toolsUpdate() {
	currentTime = SDL_GetTicks();
	deltatime = (currentTime - lastTime) / 1000.0f; 
	lastTime = currentTime;
	SDL_GetMouseState(&mouseX, &mouseY);
}

float deltaTime() {
	return deltatime;
}
bool isHover(SDL_Rect& buttonRect) {
	return mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w &&
		   mouseY > buttonRect.y && mouseY < buttonRect.y + buttonRect.h;
}