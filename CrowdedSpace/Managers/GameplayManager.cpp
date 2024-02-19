#include "GameplayManager.h"

GameplayManager::GameplayManager() : m_isGamePaused(false)
{
}

bool GameplayManager::IsGamePaused() const
{
	return m_isGamePaused;
}

void GameplayManager::SetIsGamePaused(bool pause)
{
	m_isGamePaused = pause;
}