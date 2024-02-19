#include "ControlsWidget.h"
#include "../HUDComponents/TextRendererHUDComponent.h"
#include "../../App/app.h"
#include "../../App/app.h"

ControlsWidget::ControlsWidget() :
	m_actionTextRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_gamepadTextRenderer(AddHUDComponent<TextRendererHUDComponent>()),
	m_keyboardTextRenderer(AddHUDComponent<TextRendererHUDComponent>())
{
	m_position = Vector2D(10, 120);

	m_actionTextRenderer->m_text = "                      Move       |    Pick or use the item";
	m_actionTextRenderer->m_font = GLUT_BITMAP_HELVETICA_12;

	m_gamepadTextRenderer->m_offset = Vector2D(0, -20);
	m_gamepadTextRenderer->m_text = "Gamepad:   Left joystick   |             'B'";
	m_gamepadTextRenderer->m_font = GLUT_BITMAP_HELVETICA_12;

	m_keyboardTextRenderer->m_offset = Vector2D(0, -40);
	m_keyboardTextRenderer->m_text = "Keyboard:       WASD      |             'P'";
	m_keyboardTextRenderer->m_font = GLUT_BITMAP_HELVETICA_12;
}