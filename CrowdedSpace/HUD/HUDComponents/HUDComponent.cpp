#include "HUDComponent.h"
#include "../HUD.h"

HUDComponent::HUDComponent() : m_isVisible(true), m_offset(Vector2D::ZeroVector), m_hasBegunPlay(false), m_parent(nullptr)
{
}

HUDComponent::~HUDComponent()
{
	Destroy();
}

void HUDComponent::SetParent(IHUDParent* parent)
{
	m_parent = parent;
}

Vector2D HUDComponent::GetPosition()
{
	return m_parent->GetParentPosition() + m_offset;
}

bool HUDComponent::HasBegunPlay()
{
	return m_hasBegunPlay;
}

void HUDComponent::BeginPlay()
{
	if (m_hasBegunPlay) return;
	m_hasBegunPlay = true;
}

void HUDComponent::Update(float deltaTime)
{
}

void HUDComponent::Render()
{
}

void HUDComponent::Destroy()
{
}