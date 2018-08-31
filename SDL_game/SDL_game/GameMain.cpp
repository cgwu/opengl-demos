
#include "stdafx.h"
#include "Game.h"


#include "windows.h"	// AllocConsole����

//Game* g_game = 0;

int main(int argc, char *argv[]) {
	/* ����������SubSystem: Windows (/SUBSYSTEM:WINDOWS) ģʽ�´򿪿���̨�����Բ鿴��� */
	AllocConsole();
	freopen("CON", "w", stdout);

	//g_game = new Game();
	TheGame::Instance()->init(u8"��ã�SDL! GREAT!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		//1440, 900,
		false);

	while (TheGame::Instance()->running()) {
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();

		SDL_Delay(10); // add the delay.
	}
	TheGame::Instance()->clean();
	//delete g_game;
	return 0;
}