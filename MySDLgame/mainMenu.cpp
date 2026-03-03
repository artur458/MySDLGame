#include "mainMenu.h"
#include <iostream>
#include <string>
#include "myTools.h"

TTF_Font* font = NULL;
SDL_Surface* bgSurf = NULL;
SDL_Surface* textSurface = NULL;
SDL_Surface* StartButtonSurf = NULL;
SDL_Surface* urlsSurf = NULL;

SDL_Rect SrcUrlsRectDs = { 0, 0, 128, 128 };
SDL_Rect SrcUrlsRectTg = { 0, 128, 128, 128 };
SDL_Rect SrcUrlsRectGit = { 0, 256, 128, 128 };
SDL_Rect SrcUrlsRectTxt = { 128, 0, 128, 384 };

SDL_Rect bgRect = { 800 / 2, 600 / 2, 960, 720 };
SDL_Rect textRect = { 20, 20, 400, 200 };
SDL_Rect StartButtonRect = { 15, 200, 200, 75 };
SDL_Rect DscUrlsRectDs = { 15, 450, 75, 75 };
SDL_Rect DscUrlsRectTg = { 95, 450, 75, 75 };
SDL_Rect DscUrlsRectGit = { 175, 450, 75, 75 };
SDL_Rect DscUrlsRectTxt = { 150, 245, SrcUrlsRectTxt.w - 30, SrcUrlsRectTxt.h - 30 };

SDL_Texture* bgTexture = NULL;
SDL_Texture* textTexture = NULL;
SDL_Texture* StartButtonTexture = NULL;
SDL_Texture* urlsTexture = NULL;

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
	
	urlsSurf = IMG_Load("data/urls.png");
	urlsTexture = SDL_CreateTextureFromSurface(renderer, urlsSurf);


	textRect.w = textSurface->w * 2;
	textRect.h = textSurface->h * 2;
	StartButtonRect.w = StartButtonSurf->w;
	StartButtonRect.h = StartButtonSurf->h;

}

// Обработка событий меню
void MainMenuEvent(SDL_Event& event, char& gameState) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (isHover(DscUrlsRectDs) || isHover(DscUrlsRectTg) || isHover(DscUrlsRectGit) || isHover(StartButtonRect)) { SDL_SetCursor(hoverCursor); }
	else { SDL_SetCursor(normalCursor); }

	if (event.button.button == SDL_BUTTON_LEFT) {
		if ( isHover(StartButtonRect) ) { gameState = 1; SDL_SetCursor(normalCursor); MainMenuCleanup(); }
		if ( isHover(DscUrlsRectDs) ) { SDL_OpenURL( "https://discord.gg/m7qWUgRGK7" ); }
		if ( isHover(DscUrlsRectTg) ) { SDL_OpenURL( "https://t.me/Deadly_Place "); }
		if ( isHover(DscUrlsRectGit) ) { SDL_OpenURL( "https://github.com/artur458/MySDLGame" ); }
	}

	if (event.type == SDL_MOUSEMOTION) {
		bgRect.x = 800 / 2 - bgRect.w / 2 + (event.motion.x - 800 / 2) / 5;
		bgRect.y = 600 / 2 - bgRect.h / 2 + (event.motion.y - 600 / 2) / 5;

		textRect.x = 10 + (event.motion.x - 20) / 50;
		textRect.y = 10 + (event.motion.y - 20) / 50;

		StartButtonRect.x = 15 + (event.motion.x - 20) / 50;
		StartButtonRect.y = 200 + (event.motion.y - 20) / 50;

		DscUrlsRectDs.x = 15 + (event.motion.x - 20) / 50;
		DscUrlsRectDs.y = 450 + (event.motion.y - 20) / 50;

		DscUrlsRectTg.x = 95 + (event.motion.x - 20) / 50;
		DscUrlsRectTg.y = 450 + (event.motion.y - 20) / 50;

		DscUrlsRectGit.x = 175 + (event.motion.x - 20) / 50;
		DscUrlsRectGit.y = 450 + (event.motion.y - 20) / 50;

		DscUrlsRectTxt.x = 150 + (event.motion.x - 20) / 50;
		DscUrlsRectTxt.y = 245 + (event.motion.y - 20) / 50;
	}
}

// Рендер меню
void MainMenuRender(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderCopy(renderer, StartButtonTexture, NULL, &StartButtonRect);

	SDL_RenderCopyEx(renderer, urlsTexture, &SrcUrlsRectTxt, &DscUrlsRectTxt, -90.f, NULL, SDL_FLIP_NONE);
	SDL_RenderCopy(renderer, urlsTexture, &SrcUrlsRectDs, &DscUrlsRectDs);
	SDL_RenderCopy(renderer, urlsTexture, &SrcUrlsRectTg, &DscUrlsRectTg);
	SDL_RenderCopy(renderer, urlsTexture, &SrcUrlsRectGit, &DscUrlsRectGit);

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