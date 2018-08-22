#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::init(const char *title, int x, int y, int w, int h, bool fullscreen)
{
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success" << std::endl;
		m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

		if (m_pWindow != 0) {
			std::cout << "Window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				std::cout << "Renderer creation success" << std::endl;
				//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else {
				std::cout << "Render init fail" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "Window init fail" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "SDL init fail" << std::endl;
		return false;
	}

	//SDL_Surface * pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	//SDL_Surface * pTempSurface = SDL_LoadBMP("assets/animate.bmp");
	SDL_Surface * pTempSurface = IMG_Load("assets/animate.png");

	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	/*
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

	m_destinationRectangle.x = (m_sourceRectangle.x = 50)+  100;
	m_destinationRectangle.y = (m_sourceRectangle.y = 50) + 100;
	m_destinationRectangle.w = m_sourceRectangle.w; // *2;
	m_destinationRectangle.h = m_sourceRectangle.h; // *2;

	m_sourceRectangle.w /= 2;
	m_sourceRectangle.h /= 2;
	*/
	m_destinationRectangle.x = (m_sourceRectangle.x = 0)+200;
	m_destinationRectangle.y = (m_sourceRectangle.y = 0)+100;
	m_destinationRectangle.w = m_sourceRectangle.w = 128;
	m_destinationRectangle.h = m_sourceRectangle.h = 82;

	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	//SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	//SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, 0);
	//SDL_RenderCopy(m_pRenderer, m_pTexture, 0, &m_destinationRectangle);

	/*
	Passing null into the source rectangle parameter will make the render use the entire texture.
	Likewise, passing null to the destination rectangle parameter will use the entire render for display.
	*/
	//SDL_RenderCopy(m_pRenderer, m_pTexture, 0, 0);

	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle,
		0, 0, SDL_FLIP_HORIZONTAL);
		//90,0,SDL_FLIP_HORIZONTAL);

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_sourceRectangle.x = 128 * int((SDL_GetTicks() / 100) % 6);
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	std::cout << "Cleaning game" << std::endl;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
