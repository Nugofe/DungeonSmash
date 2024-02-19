#pragma once

#include "../Utils/Utils.h"

#include <vector>

// interface possesed by hud elements that can be parent of a hud component
class IHUDParent
{
public:
	IHUDParent() = default;
	virtual ~IHUDParent() = default;

	virtual Vector2D GetParentPosition() = 0;
};

class Widget;
class PlayerController;
class GameplayManager;

class HUD
{
public:
	HUD();
	virtual ~HUD();

	PlayerController* GetPlayerController() const;
	GameplayManager* GetPlayerGameplayManager() const;

	virtual void BeginPlay();
	virtual void EndPlay();
	void Update(float deltaTime);
	void Render();
	void Destroy();

protected:
	template<typename T>
	T* GetWidgetOfClass();
	
	template<typename T>
	T* AddWidget();

private:
	bool m_haveAllWidgetsBegunPlay;
	std::vector<Widget*> m_widgets;

	PlayerController* m_ownerPlayerController;
	GameplayManager* m_gameplayManager;

	DelegateHandle m_renderHandle;

	friend class PlayerController;
};


template<typename T>
inline T* HUD::GetWidgetOfClass()
{
	static_assert(std::is_base_of<Widget, T>::value, "T has to be a child of Widget");

	for (Widget* widget : m_widgets) {
		// Check if the widget is an instance of the specified class type
		if (HelperFunctions::instanceof<T>(widget)) {
			return HelperFunctions::cast<T>(widget);
		}
	}
	return nullptr;
}

template<typename T>
inline T* HUD::AddWidget()
{
	static_assert(std::is_base_of<Widget, T>::value, "T has to be a child of Widget");
	T* widget = new T();
	if (widget != nullptr)
	{
		widget->m_hud = this;
		m_widgets.push_back(widget);
	}
	return widget;
}