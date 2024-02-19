#include "StartMenuWidget.h"
#include "../HUDComponents/TextRendererHUDComponent.h"

StartMenuWidget::StartMenuWidget() :
	m_firstText(" --- START GAME ---"),
	m_secondText("Press 'B' with gamepad or 'P' with keyboard"),
	m_firstTextRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_secondTextRenderer(AddHUDComponent<TextRendererHUDComponent>())
{
	m_position = Vector2D(410, 400);

	m_firstTextRenderer->m_text = m_firstText;

	m_secondTextRenderer->m_offset = Vector2D(-80, -50);
	m_secondTextRenderer->m_text = m_secondText;
}