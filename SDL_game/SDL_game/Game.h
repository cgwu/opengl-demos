#pragma once
class Game
{
public:
	Game();
	~Game();

	bool init(const char *title, int x, int y, int w, int h, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() {
		return m_bRunning;
	}
private:
	bool m_bRunning;
	SDL_Window * m_pWindow;
	SDL_Renderer * m_pRenderer;

	SDL_Texture * m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
};

