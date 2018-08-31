#pragma once
#include "GameObject.h"
#include "LoaderParams.h"

class SDLGameObject :
	public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	~SDLGameObject();

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_x;
	int m_y;

	int m_width;
	int m_height;
};

