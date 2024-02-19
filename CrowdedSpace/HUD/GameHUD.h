#pragma once

#include "HUD.h"
#include "../Utils/Utils.h"

class GameHUD : public HUD
{
public:
	GameHUD();

	void GameOver();

	virtual void BeginPlay();
	virtual void EndPlay();

private:
	DelegateHandle m_gameOverHandle;
};

class StartGameHUD : public HUD
{
public:
	StartGameHUD();
};