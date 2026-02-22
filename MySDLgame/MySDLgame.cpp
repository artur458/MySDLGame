#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "mainMenu.h"
#include "gameScene.h"

#define SCENE_MAINMENU 0
#define SCENE_GAME 1
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	static SDL_Window* window = SDL_CreateWindow( "My SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_MAXIMIZED);
	static SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC );
	SDL_SetWindowIcon(window, bgSurf);
	// --------------------------------------------
	
	MainMenuStart(renderer);
	OnGameStart(renderer);
	
	char gameState = SCENE_MAINMENU;
	// --------------------------------------------
	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			if (gameState == SCENE_MAINMENU) { MainMenuEvent(event, gameState); }
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		switch (gameState)
		{
			case SCENE_MAINMENU:  MainMenuRender(renderer); break;
			case SCENE_GAME:      OnGameRender(renderer);   break;
		}

		SDL_RenderPresent( renderer );
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	MainMenuCleanup();
	TTF_CloseFont(font);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 1;
}
