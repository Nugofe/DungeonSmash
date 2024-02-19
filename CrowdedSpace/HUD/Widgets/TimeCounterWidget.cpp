#include "TimeCounterWidget.h"
#include "../HUDComponents/TextRendererHUDComponent.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Managers/GameManager.h"
#include "../../Worlds/World.h"

TimeCounterWidget::TimeCounterWidget() : 
	m_textRenderer(AddHUDComponent<TextRendererHUDComponent>()), 
	m_gameManager(nullptr)
{
	m_position = Vector2D(800, 700);
}

void TimeCounterWidget::BeginPlay()
{
	Widget::BeginPlay();

	GameManager* gameManager = HelperFunctions::cast<GameManager>(
		GameplayStatics::GetInstance().GetCurrentWorld()->GetGameplayManager()
	);

	if (gameManager != nullptr)
	{
		m_gameManager = gameManager;
	}
}

void TimeCounterWidget::Update(float deltaTime)
{
	Widget::Update(deltaTime);

	if (m_gameManager != nullptr)
	{
		float time = m_gameManager->GetRemainingTime();
		std::string s = std::to_string((int)time) + std::string(" seconds");
		m_textRenderer->m_text = s.c_str();
	}
}