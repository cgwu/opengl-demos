#pragma once
#include <string>
#include <SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();
	void Update();
	bool IsClosed();
	void Clear(float r, float g, float b, float a);

private:
	SDL_Window * m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

