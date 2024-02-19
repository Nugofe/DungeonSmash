#pragma once

#include "Widget.h"

#include <string>

class TextRendererHUDComponent;

class GameOverWidget : public Widget
{
public:
	GameOverWidget();

	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;

private:
	std::string m_enemiesText;
	std::string m_restartText;
	TextRendererHUDComponent* m_enemiesTextRenderer;
	TextRendererHUDComponent* m_restartTextRenderer;

	float m_time;
};