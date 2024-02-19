#include "GameManager.h"
#include "../Components/Health/HealthComponent.h"
#include "../Components/Scene/SceneComponent.h"
#include "../Components/Sprites/SpriteRendererComponent.h"
#include "../Actors/Pawns/EnemyCharacter.h"
#include "../Worlds/World.h"
#include "../Utils/Utils.h"
#include "../Utils/GameplayStatics.h"
#include "../App/AppSettings.h"
#include "../Actors/Controllers/PlayerController/PlayerController.h"
#include "../HUD/GameHUD.h"

GameManager::GameManager() :
	m_isGameOver(false),
	m_remainingTime(61.0f), // ACTUALLY 60 SECONDS
	m_currentRemainingTime(m_remainingTime),
	m_enemiesKilled(0),
	m_maxEnemiesSpawned(10),
	m_spawnThreshold(50.0f),
	m_timeBetweenSpawns(0.5f),
	m_timeBetweenSpawnsLeft(m_timeBetweenSpawns)
{
}

bool GameManager::IsGameOver() const
{
	return m_isGameOver;
}

void GameManager::GameOver()
{
	m_isGameOver = true;
	OnGameOver.Broadcast();
}

float GameManager::GetRemainingTime() const
{
	return m_remainingTime;
}

int GameManager::GetEnemiesKilled() const
{
	return m_enemiesKilled;
}

void GameManager::BeginPlay()
{
	GameplayManager::BeginPlay();

	m_timeBetweenSpawnsLeft = m_timeBetweenSpawns;

	m_enemiesKilledHandle = EnemyCharacter::OnEnemyDied.Subscribe(this, &GameManager::OnEnemyDied);
	OnEnemiesKilledChanged.Broadcast(m_enemiesKilled);
}

void GameManager::EndPlay()
{
	EnemyCharacter::OnEnemyDied.Unsubscribe(m_enemiesKilledHandle);

	GameplayManager::EndPlay();
}

void GameManager::Update(float deltaTime)
{
	GameplayManager::Update(deltaTime);

	if(IsGamePaused()) return;

	m_timeBetweenSpawnsLeft -= deltaTime;
	if (m_timeBetweenSpawnsLeft <= 0)
	{
		m_timeBetweenSpawnsLeft = m_timeBetweenSpawns;
		SpawnEnemy();
	}

	m_remainingTime -= deltaTime;
	if (m_remainingTime <= 0)
	{
		SetIsGamePaused(true);
		GameOver();
		/*GameHUD* gameHUD = HelperFunctions::cast<GameHUD>(GameplayStatics::GetInstance().GetPlayerController(0)->GetHUD());
		if (gameHUD != nullptr)
		{
			GameOver();
			gameHUD->GameOver();
		}*/
	}
}

void GameManager::Destroy()
{
	GameplayManager::Destroy();
}

void GameManager::OnEnemyDied(EnemyCharacter* enemy)
{
	// count enemies killed
	++m_enemiesKilled;
	OnEnemiesKilledChanged.Broadcast(m_enemiesKilled);

	// spawn new enemy
	HelperFunctions::remove(m_enemiesSpawned, enemy);
	m_timeBetweenSpawnsLeft = m_timeBetweenSpawns;
}

void GameManager::SpawnEnemies()
{
	while (m_enemiesSpawned.size() < m_maxEnemiesSpawned)
	{
		SpawnEnemy();
	}
}

void GameManager::SpawnEnemy()
{
	if (m_enemiesSpawned.size() >= m_maxEnemiesSpawned) return;

	bool alreadyExistentPos = false;
	Vector2D randPos = HelperFunctions::GetRandomPositionInRange(APP_VIRTUAL_WIDTH - 100, APP_VIRTUAL_HEIGHT - 100);
	for (SpriteRendererComponent* spriteRenderer : GetWorld()->GetComponentsOfClass<SpriteRendererComponent>())
	{
		if (spriteRenderer != nullptr)
		{
			SceneComponent* sc = spriteRenderer->GetOwner()->GetRootComponent();
			if (sc != nullptr)
			{
				float dist = Vector2D::DistanceSquare(sc->GetPosition(), randPos);
				if (dist <= m_spawnThreshold * m_spawnThreshold)
				{
					alreadyExistentPos = true;
					break;
				}
			}
		}
	}
	if (!alreadyExistentPos)
	{
		EnemyCharacter* enemy = GetWorld()->SpawnActor<EnemyCharacter>();
		SceneComponent* sc = enemy->GetRootComponent();
		if (sc != nullptr)
		{
			enemy->GetRootComponent()->SetPosition(randPos);
			m_enemiesSpawned.push_back(enemy);
		}
	}
}