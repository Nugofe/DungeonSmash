#pragma once

#include "HUDComponent.h"
#include "../HUD.h"

class PanelHUDComponent : public HUDComponent, public IHUDParent
{
public:
	PanelHUDComponent();

	virtual Vector2D GetParentPosition() override;

public:
	float m_width;
	float m_height;
};