#include "Widget.h"
#include "../HUDComponents/HUDComponent.h"
#include "../../Actors/Controllers/PlayerController/PlayerController.h"
#include "../../Worlds/World.h"
#include "../../Managers/GameplayManager.h"

Widget::Widget() : 
	m_isVisible(true),
	m_hasBegunPlay(false),
	m_haveAllComponentsBegunPlay(false),
	m_updateWhenPaused(false),
	m_position(Vector2D::ZeroVector),
	m_hud(nullptr)
{
}

Widget::~Widget()
{
	Destroy();
}

Vector2D Widget::GetParentPosition()
{
	return m_position;
}

bool Widget::HasBegunPlay()
{
	return m_hasBegunPlay;
}

HUD* Widget::GetHUD() const
{
	return m_hud;
}

void Widget::BeginPlay()
{
	if (!m_haveAllComponentsBegunPlay)
	{
		for (HUDComponent* comp : m_components)
		{
			if (comp != nullptr && !comp->HasBegunPlay())
			{
				comp->BeginPlay();
			}
		}
	}
	m_haveAllComponentsBegunPlay = true;
	m_hasBegunPlay = true;
}

void Widget::Update(float deltaTime)
{
	bool gamePaused = m_hud->GetPlayerController()->GetWorld()->GetGameplayManager()->IsGamePaused();
	if (gamePaused && !m_updateWhenPaused) return;

	if (!m_haveAllComponentsBegunPlay)
	{
		for (HUDComponent* comp : m_components)
		{
			if (comp != nullptr)
			{
				if (!comp->HasBegunPlay())
				{
					comp->BeginPlay();
				}
				comp->Update(deltaTime);
			}
		}
	}
	else
	{
		for (HUDComponent* comp : m_components)
		{
			if (comp != nullptr)
			{
				comp->Update(deltaTime);
			}
		}
	}
}

void Widget::Render()
{
	if (!m_isVisible) return;

	for (HUDComponent* comp : m_components)
	{
		if (comp != nullptr && comp->m_isVisible)
		{
			comp->Render();
		}
	}
}

void Widget::Destroy()
{
	for (HUDComponent* comp : m_components)
	{
		if (comp != nullptr)
		{
			comp->Destroy();
			delete comp;
		}
	}
	m_components.clear();
}