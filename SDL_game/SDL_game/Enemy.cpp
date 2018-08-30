#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::update()
{
	m_x += 1;
	m_y += 1;
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);
}
