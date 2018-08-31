#pragma once
#include "SDLGameObject.h"
#include "LoaderParams.h"

class Enemy :
	public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	~Enemy();

	virtual void draw();
	virtual void update();
	virtual void clean();
};

