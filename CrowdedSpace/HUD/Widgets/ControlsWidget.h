#pragma once

#include "Widget.h"

#include <string>

class TextRendererHUDComponent;

class ControlsWidget : public Widget
{
public:
	ControlsWidget();

private:
	TextRendererHUDComponent* m_actionTextRenderer;
	TextRendererHUDComponent* m_gamepadTextRenderer;
	TextRendererHUDComponent* m_keyboardTextRenderer;
};