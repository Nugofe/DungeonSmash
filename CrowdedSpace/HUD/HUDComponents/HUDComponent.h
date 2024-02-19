#pragma once

#include "../../Utils/Utils.h"

class IHUDParent;

class HUDComponent
{
public:
	HUDComponent();
	~HUDComponent();

	void SetParent(IHUDParent* parent);
	Vector2D GetPosition();
	bool HasBegunPlay();

	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

public:
	bool m_isVisible;
	Vector2D m_offset;
	//float m_pivot;

protected:
	bool m_hasBegunPlay;
	IHUDParent* m_parent;
};