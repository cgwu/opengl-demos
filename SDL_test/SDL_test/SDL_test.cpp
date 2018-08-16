// SDL_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Display.h"

int main(int argc, char* argv[])
{
	Display display(800,600,u8"你好SDL2!");
	while (!display.IsClosed()) {
		display.Clear(.0f, .15f, .3f, 1.0f);
		display.Update();
	}
    return 0;
}

