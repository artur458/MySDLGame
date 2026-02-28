#include "mainMenu.h"
#include <iostream>
#include <string>
// Глобальные ресурсы
TTF_Font* font = NULL;
SDL_Surface* bgSurf = NULL;
SDL_Surface* textSurface = NULL;
SDL_Surface* StartButtonSurf = NULL;

SDL_Rect bgRect = { 800 / 2, 600 / 2, 960, 720 };
SDL_Rect textRect = { 20, 20, 400, 200 };
SDL_Rect StartButtonRect = { 15, 200, 200, 75 };

SDL_Texture* bgTexture = NULL;
SDL_Texture* textTexture = NULL;
SDL_Texture* StartButtonTexture = NULL;

SDL_Cursor* normalCursor = NULL;
SDL_Cursor* hoverCursor  = NULL;

// Инициализация меню
void MainMenuStart(SDL_Renderer* renderer) {
	font = TTF_OpenFont("data/Roboto-Bold.ttf", 64);

	bgSurf = IMG_Load("data/1.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurf);

	textSurface = TTF_RenderText_Blended_Wrapped(font, "Main Menu", { 255, 255, 255, 255 }, NULL);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	StartButtonSurf = TTF_RenderText_Blended_Wrapped(font, "Start", { 255, 255, 255, 255 }, NULL);
	StartButtonTexture = SDL_CreateTextureFromSurface(renderer, StartButtonSurf);

	normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	textRect.w = textSurface->w * 2;
	textRect.h = textSurface->h * 2;
	StartButtonRect.w = StartButtonSurf->w;
	StartButtonRect.h = StartButtonSurf->h;
	std::cout << std::to_string(StartButtonSurf->w) + " " + std::to_string(StartButtonSurf->h) << std::endl;
}

// Обработка событий меню
void MainMenuEvent(SDL_Event& event, char& gameState) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	bool overButton = mouseX > StartButtonRect.x && mouseX < StartButtonRect.x + StartButtonRect.w &&
		mouseY > StartButtonRect.y && mouseY < StartButtonRect.y + StartButtonRect.h;

	if (overButton) { StartButtonRect.h = 95; StartButtonRect.w = 161; StartButtonRect.x -= 20; StartButtonRect.y -= 20; SDL_SetCursor(hoverCursor); }
	else { StartButtonRect.h = 75; StartButtonRect.w = 141; StartButtonRect.x = 15; StartButtonRect.y = 200; SDL_SetCursor(normalCursor); }

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (overButton) { gameState = 1; SDL_SetCursor(normalCursor); MainMenuCleanup(); }
	}

	if (event.type == SDL_MOUSEMOTION) {
		bgRect.x = 800 / 2 - bgRect.w / 2 + (event.motion.x - 800 / 2) / 5;
		bgRect.y = 600 / 2 - bgRect.h / 2 + (event.motion.y - 600 / 2) / 5;

		textRect.x = 10 + (event.motion.x - 20) / 50;
		textRect.y = 10 + (event.motion.y - 20) / 50;

		StartButtonRect.x = 15 + (event.motion.x - 20) / 50;
		StartButtonRect.y = 200 + (event.motion.y - 20) / 50;
	}
}

// Рендер меню
void MainMenuRender(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderCopy(renderer, StartButtonTexture, NULL, &StartButtonRect);
}

// Очистка ресурсов
void MainMenuCleanup() {
	if (bgTexture) SDL_DestroyTexture(bgTexture);
	if (textTexture) SDL_DestroyTexture(textTexture);
	if (StartButtonTexture) SDL_DestroyTexture(StartButtonTexture);

	if (bgSurf) SDL_FreeSurface(bgSurf);
	if (textSurface) SDL_FreeSurface(textSurface);
	if (StartButtonSurf) SDL_FreeSurface(StartButtonSurf);

}