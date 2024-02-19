#include "EnemyCounterWidget.h"
#include "../HUDComponents/TextRendererHUDComponent.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Managers/GameManager.h"
#include "../../Worlds/World.h"

#include <string>

EnemyCounterWidget::EnemyCounterWidget() :
	m_fixedText("Enemies Killed: "), 
	m_textRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_gameManager(nullptr)
{
	m_position = Vector2D(50, 700);

	m_textRenderer->m_offset = Vector2D(0, 0);
	m_textRenderer->m_color = RGBColor::Pink;
}

void EnemyCounterWidget::BeginPlay()
{
	Widget::BeginPlay();

	GameManager* gameManager = HelperFunctions::cast<GameManager>(
		GameplayStatics::GetInstance().GetCurrentWorld()->GetGameplayManager()
	);

	if (gameManager != nullptr)
	{
		m_gameManager = gameManager;

		int num = m_gameManager->GetEnemiesKilled();
		std::string s = std::to_string(num);
		m_textRenderer->m_text = m_fixedText + s.c_str();

		m_enemiesKilledHandle = m_gameManager->OnEnemiesKilledChanged.Subscribe(this, &EnemyCounterWidget::OnEnemiesKilledChanged);
	}
}

void EnemyCounterWidget::Destroy()
{
	if (m_gameManager != nullptr)
	{
		m_gameManager->OnEnemiesKilledChanged.Unsubscribe(m_enemiesKilledHandle);
	}

	Widget::Destroy();
}

void EnemyCounterWidget::OnEnemiesKilledChanged(int num)
{
	std::string s = std::to_string(num);
	m_textRenderer->m_text = m_fixedText + s.c_str();
}