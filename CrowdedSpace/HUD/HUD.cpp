#include "HUD.h"
#include "Widgets/Widget.h"
#include "../Actors/Controllers/PlayerController/PlayerController.h"
#include "../Worlds/World.h"

HUD::HUD() : m_haveAllWidgetsBegunPlay(false), m_ownerPlayerController(nullptr), m_gameplayManager(nullptr)
{
}

HUD::~HUD()
{
	Destroy();
}

PlayerController* HUD::GetPlayerController() const
{
	return m_ownerPlayerController;
}

GameplayManager* HUD::GetPlayerGameplayManager() const
{
	return m_gameplayManager;
}

void HUD::BeginPlay()
{
	m_renderHandle = m_ownerPlayerController->GetWorld()->OnFinishedRender.Subscribe(this, &HUD::Render);
}

void HUD::EndPlay()
{
	m_ownerPlayerController->GetWorld()->OnFinishedRender.Unsubscribe(m_renderHandle);

	for (Widget* widget : m_widgets)
	{
		if (widget != nullptr)
		{
			widget->Destroy();
			delete widget;
		}
	}
	m_widgets.clear();
}

void HUD::Update(float deltaTime)
{
	if (!m_haveAllWidgetsBegunPlay)
	{
		for (Widget* widget : m_widgets)
		{
			if (widget != nullptr)
			{
				if (!widget->HasBegunPlay())
				{
					widget->BeginPlay();
				}
				widget->Update(deltaTime);
			}
		}
	}
	else
	{
		for (Widget* widget : m_widgets)
		{
			if (widget != nullptr)
			{
				widget->Update(deltaTime);
			}
		}
	}	
}

void HUD::Render()
{
	for (Widget* widget : m_widgets)
	{
		if (widget != nullptr)
		{
			widget->Render();
		}
	}
}

void HUD::Destroy()
{
	EndPlay();
}