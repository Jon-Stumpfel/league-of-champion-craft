#pragma once

#include "StdAfx.h"
#include "InputManager.h"
class IGameState
{
public:

	virtual ~IGameState(void) = 0
	{

	}

	virtual void Enter(void) = 0;
	virtual void Exit(void) = 0;
	virtual void Input(INPUT_ENUM input) = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(void) = 0;
};