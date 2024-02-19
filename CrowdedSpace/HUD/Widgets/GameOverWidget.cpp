#include "GameOverWidget.h"
#include "../HUDComponents/TextRendererHUDComponent.h"
#include "../../Utils/Utils.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Managers/GameManager.h"
#include "../../Worlds/World.h"
#include "../../Actors/Controllers/PlayerController/GamePlayerController.h"

GameOverWidget::GameOverWidget() :
	m_enemiesText("GAME OVER!!  Enemies Killed: "),
	m_restartText("To RESTART the game press 'B' with gamepad or 'P' with keyboard"),
	m_enemiesTextRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_restartTextRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_time(1.5f)
{
	m_updateWhenPaused = true;
	m_position = Vector2D(380, 400);

	m_restartTextRenderer->m_offset = Vector2D(-150, -50);
	m_restartTextRenderer->m_text = m_restartText;
}

void GameOverWidget::BeginPlay()
{
	Widget::BeginPlay();

	GameManager* gameManager = HelperFunctions::cast<GameManager>(
		GameplayStatics::GetInstance().GetCurrentWorld()->GetGameplayManager()
	);

	if (gameManager != nullptr)
	{
		gameManager->GetEnemiesKilled();

		int num = gameManager->GetEnemiesKilled();
		std::string s = std::to_string(num);
		m_enemiesTextRenderer->m_text = m_enemiesText + s.c_str();
	}
}

void GameOverWidget::Update(float deltaTime)
{
	Widget::Update(deltaTime);

	m_time -= deltaTime;
	if (m_time > 0.0) return;

	GamePlayerController* playerController = HelperFunctions::cast<GamePlayerController>(GetHUD()->GetPlayerController());
	if (playerController != nullptr)
	{
		playerController->CheckResetGame();
	}
}