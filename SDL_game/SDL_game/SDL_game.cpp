// SDL_game.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

static SDL_Window * g_pWindow = 0;
static SDL_Renderer * g_pRenderer = 0;

int main_SDL_game(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		g_pWindow = SDL_CreateWindow(u8"你好，SDL! GREAT!",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 480,
			SDL_WINDOW_SHOWN);
		if (g_pWindow != 0) {
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	else {
		return 1;	// sdl could not initialize
	}

	SDL_SetRenderDrawColor(g_pRenderer,  0, 255,0, 255);
	SDL_RenderClear(g_pRenderer);

	SDL_RenderPresent(g_pRenderer);
	SDL_Delay(5000);	// set a delay before quitting

	// clean up SDL
	SDL_Quit();
    return 0;
}

