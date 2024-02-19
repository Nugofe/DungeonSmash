#pragma once

#include "Widget.h"

#include <string>

class TextRendererHUDComponent;
class GameManager;

class TimeCounterWidget : public Widget
{
public:
	TimeCounterWidget();

	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;

private:
	TextRendererHUDComponent* m_textRenderer;

	GameManager* m_gameManager;
};