#pragma once

#include "HUDComponent.h"
#include "../../Utils/Utils.h"

#include <string>

class TextRendererHUDComponent : public HUDComponent
{
public:
	TextRendererHUDComponent();

	virtual void Render() override;

public:
	std::string m_text;
	RGBColor m_color;
	void* m_font;
};