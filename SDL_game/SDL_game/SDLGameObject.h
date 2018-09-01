#pragma once
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

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

	//int m_x;
	//int m_y;
	Vector2D m_position;
	Vector2D m_velocity;		// 速度
	Vector2D m_acceleration;	// 加速度

	int m_width;
	int m_height;
};

