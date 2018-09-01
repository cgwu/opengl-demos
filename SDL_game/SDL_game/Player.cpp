#include "stdafx.h"
#include "Player.h"


Player::Player(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{
}


Player::~Player()
{
}


void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	//m_x += 1;
	//this->m_position.setX(this->m_position.getX() + 1);
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);

	//m_velocity.setX(1);
	m_acceleration.setX(1);
	SDLGameObject::update();
}

void Player::clean()
{
}
