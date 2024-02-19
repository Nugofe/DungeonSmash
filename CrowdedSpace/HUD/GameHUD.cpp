#include "GameHUD.h"
#include "Widgets/EnemyCounterWidget.h"
#include "Widgets/TimeCounterWidget.h"
#include "Widgets/ControlsWidget.h"
#include "Widgets/GameOverWidget.h"
#include "Widgets/StartMenuWidget.h"
#include "../Utils/GameplayStatics.h"
#include "../Worlds/World.h"
#include "../Managers/GameManager.h"
#include "../Actors/Controllers/PlayerController/PlayerController.h"

GameHUD::GameHUD()
{
	AddWidget<EnemyCounterWidget>();
	AddWidget<TimeCounterWidget>();
	AddWidget<ControlsWidget>();
}

void GameHUD::GameOver()
{
	if (GetWidgetOfClass<GameOverWidget>() == nullptr)
	{
		AddWidget<GameOverWidget>();
	}
}

void GameHUD::BeginPlay()
{
	HUD::BeginPlay();

	GameManager* gameManager = HelperFunctions::cast<GameManager>(GetPlayerGameplayManager());

	if (gameManager != nullptr)
	{
		m_gameOverHandle = gameManager->OnGameOver.Subscribe(this, &GameHUD::GameOver);
	}
}

void GameHUD::EndPlay()
{
	GameManager* gameManager = HelperFunctions::cast<GameManager>(GetPlayerGameplayManager());

	if (gameManager != nullptr)
	{
		gameManager->OnGameOver.Unsubscribe(m_gameOverHandle);
	}

	HUD::EndPlay();
}

StartGameHUD::StartGameHUD()
{
	AddWidget<StartMenuWidget>();
}