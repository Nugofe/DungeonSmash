#pragma once

#include "Widget.h"

#include <string>

class TextRendererHUDComponent;

class StartMenuWidget : public Widget
{
public:
	StartMenuWidget();

private:
	std::string m_firstText;
	std::string m_secondText;
	TextRendererHUDComponent* m_firstTextRenderer;
	TextRendererHUDComponent* m_secondTextRenderer;
};