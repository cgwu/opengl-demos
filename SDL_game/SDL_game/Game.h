#pragma once

#include <vector>
#include <memory>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	static Game* Instance() {
		if (s_pInstance == NULL) {
			s_pInstance = new Game();
		}
		return s_pInstance;
	}

	bool init(const char *title, int x, int y, int w, int h, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() {
		return m_bRunning;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer;  }

private:
	Game();
	~Game();
	static Game* s_pInstance;

	bool m_bRunning;
	SDL_Window * m_pWindow;
	SDL_Renderer * m_pRenderer;

	//SDL_Texture * m_pTexture;
	//SDL_Rect m_sourceRectangle;
	//SDL_Rect m_destinationRectangle;

	int m_currentFrame;
	//TextureManager m_textureManager;

	//GameObject* m_go;
	std::shared_ptr<Player> m_player;
	//Enemy* m_enemy;
	std::shared_ptr<Enemy> m_enemy;

	//std::vector<GameObject*> m_gameObjects;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};

typedef Game TheGame;
