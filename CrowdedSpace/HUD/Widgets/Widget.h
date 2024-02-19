#pragma once

#include "../HUD.h"
#include "../../Utils/Utils.h"

#include <vector>

class HUDComponent;

class Widget : public IHUDParent
{
public:
	Widget();
	~Widget();

	virtual Vector2D GetParentPosition() override;
	bool HasBegunPlay();

	HUD* GetHUD() const;

	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

protected:
	template<typename T>
	T* AddHUDComponent();

public:
	bool m_isVisible;
	Vector2D m_position;
	// Vector2D m_pivot;

protected:
	bool m_hasBegunPlay;
	bool m_haveAllComponentsBegunPlay;
	bool m_updateWhenPaused;

	std::vector<HUDComponent*> m_components;

private:
	HUD* m_hud;

	friend class HUD;
};


template<typename T>
inline T* Widget::AddHUDComponent()
{
	static_assert(std::is_base_of<HUDComponent, T>::value, "T has to be a child of HUDComponent");

	T* comp = new T();
	if (comp != nullptr)
	{
		comp->SetParent(this);
		m_components.push_back(comp);
		m_haveAllComponentsBegunPlay = false;
	}
	return comp;
}