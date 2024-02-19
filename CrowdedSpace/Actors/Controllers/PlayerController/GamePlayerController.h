#pragma once

#include "PlayerController.h"

class GamePlayerController : public PlayerController
{
public:
	GamePlayerController();

	void CheckResetGame();

	virtual void Update(float deltaTime) override;
};

class StartGamePlayerController : public PlayerController
{
public:
	StartGamePlayerController();

	virtual void Update(float deltaTime) override;
};