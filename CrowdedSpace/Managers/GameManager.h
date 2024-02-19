#pragma once

#include "GameplayManager.h"

class EnemyCharacter;

class GameManager : public GameplayManager
{
public:
	GameManager();

	bool IsGameOver() const;
	void GameOver();

	float GetRemainingTime() const;
	int GetEnemiesKilled() const;

	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

private:
	void OnEnemyDied(EnemyCharacter* enemy);
	void SpawnEnemies();
	void SpawnEnemy();

public:
	Delegate<int> OnEnemiesKilledChanged;
	Delegate<> OnGameOver;

private:
	bool m_isGameOver;

	float m_remainingTime;
	float m_currentRemainingTime;

	int m_enemiesKilled;
	int m_maxEnemiesSpawned;
	float m_spawnThreshold;
	float m_timeBetweenSpawns;
	float m_timeBetweenSpawnsLeft;
	std::vector<EnemyCharacter*> m_enemiesSpawned;
	
	DelegateHandle m_enemiesKilledHandle;
};