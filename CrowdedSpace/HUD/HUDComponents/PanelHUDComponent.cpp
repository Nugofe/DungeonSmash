#include "PanelHUDComponent.h"

PanelHUDComponent::PanelHUDComponent() : m_width(1.0f), m_height(1.0f)
{
}

Vector2D PanelHUDComponent::GetParentPosition()
{
	return m_parent->GetParentPosition() + m_offset;
}
