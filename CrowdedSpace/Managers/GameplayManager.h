#pragma once

#include "../Actors/Actor.h"

class EnemyCharacter;

class GameplayManager : public Actor
{
public:
	GameplayManager();

	bool IsGamePaused() const;
	void SetIsGamePaused(bool pause);

private:
	bool m_isGamePaused;
};