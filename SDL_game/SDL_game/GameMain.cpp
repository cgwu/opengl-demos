
#include "stdafx.h"
#include "Game.h"

#include "windows.h"	// AllocConsole函数

//Game* g_game = 0;

const Uint32 FPS = 60;		// Frames Per Second
const Uint32 DELAY_TIME = Uint32(1000.0f / FPS);

int main(int argc, char *argv[]) {
	/* 以下两句在SubSystem: Windows (/SUBSYSTEM:WINDOWS) 模式下打开控制台窗口以查看输出 */
	AllocConsole();
	freopen("CON", "w", stdout);

	//g_game = new Game();
	TheGame::Instance()->init(u8"你好，SDL! GREAT!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		//1440, 900,
		false);

	Uint32 frameStart, frameTime;
	while (TheGame::Instance()->running()) {
		// SDL_GetTicks() returns the amount of milliseonds since we call SDL_Init().
		frameStart = SDL_GetTicks();

		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();

		frameTime = SDL_GetTicks() - frameStart;	//处理渲染所花时间
		if (frameTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frameTime); // add the delay.
		}
		
	}
	TheGame::Instance()->clean();
	//delete g_game;
	return 0;
}
