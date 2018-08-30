
#include "stdafx.h"
#include "Game.h"


#include "windows.h"	// AllocConsole����

Game* g_game = 0;

int main(int argc, char *argv[]) {
	/* ����������SubSystem: Windows (/SUBSYSTEM:WINDOWS) ģʽ�´򿪿���̨�����Բ鿴��� */
	AllocConsole();
	freopen("CON", "w", stdout);

	g_game = new Game();
	g_game->init(u8"��ã�SDL! GREAT!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		//1440, 900,
		false);

	while (g_game->running()) {
		g_game->handleEvents();
		g_game->update();
		g_game->render();

		SDL_Delay(10); // add the delay.
	}
	g_game->clean();
	delete g_game;
	return 0;
}