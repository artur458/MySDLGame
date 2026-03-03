#include "myTools.h"
#include <SDL.h>

Uint32 lastTime;

Uint32 currentTime;
float deltatime;

int mouseX, mouseY;
void toolsStart() {
	lastTime = SDL_GetTicks();
}
void toolsEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}
}

void toolsUpdate() {
	currentTime = SDL_GetTicks();
	deltatime = (currentTime - lastTime) / 1000.0f; 
	lastTime = currentTime;
}

float deltaTime() {
	return deltatime;
}
bool isHover(SDL_Rect& buttonRect) {
	return mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w &&
		   mouseY > buttonRect.y && mouseY < buttonRect.y + buttonRect.h;
}
void SDL_RenderCopyShadow(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect& dstrect, int shadowX, int shadowY) {
	SDL_SetTextureColorMod(texture, 0, 0, 0);
	SDL_SetTextureAlphaMod(texture, 127);
	dstrect.x += shadowX;
	dstrect.y += shadowY;
	SDL_RenderCopy(renderer, texture, srcrect, &dstrect);
	dstrect.x -= shadowX;
	dstrect.y -= shadowY;
	SDL_SetTextureColorMod(texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_RenderCopy(renderer, texture, srcrect, &dstrect);
}

SDL_Point GetMousePos() {
	SDL_Point pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}