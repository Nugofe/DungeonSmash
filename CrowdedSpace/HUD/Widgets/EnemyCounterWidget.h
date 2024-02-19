#pragma once

#include "Widget.h"
#include "../../Utils/Utils.h"

#include <string>

class TextRendererHUDComponent;
class GameManager;

class EnemyCounterWidget : public Widget
{
public:
	EnemyCounterWidget();

	virtual void BeginPlay() override;
	virtual void Destroy() override;

private:
	void OnEnemiesKilledChanged(int num);

private:
	std::string m_fixedText;
	TextRendererHUDComponent* m_textRenderer;

	GameManager* m_gameManager;

	DelegateHandle m_enemiesKilledHandle;
};