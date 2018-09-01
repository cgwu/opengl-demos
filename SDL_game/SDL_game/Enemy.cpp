#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{
}


Enemy::~Enemy()
{
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	//m_x += 1;
	//m_y += 1;
	//this->m_position = this->m_position + Vector2D(1,1);
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);

	//m_velocity.setX(1);
	//m_velocity.setY(1);
	m_acceleration.setX(1);
	m_acceleration.setY(1);
	//if (m_velocity.length() > 100) { m_velocity.setX(0); m_velocity.setY(0); }
	SDLGameObject::update();
}

void Enemy::clean()
{
}
