#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

#include <vector>

class SceneComponent : public Component
{
public:
	SceneComponent();
	~SceneComponent();

	const Transform2D& GetTransform() const;
	void SetTransform(const Transform2D& transform);
	const Vector2D& GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(const Vector2D& position);
	const float GetRotation() const;
	void SetRotation(float rotation);
	const float GetScale() const;
	void SetScale(float scale);

	//const SceneComponent* GetParent() const;
	//void SetParent(const SceneComponent* parent);
	//const std::vector<SceneComponent*>& GetChildren() const;
	//void AddChild(const SceneComponent* child);
	//void AddChildren(); // TODO ?

private:
	Transform2D m_transform;
	//SceneComponent* parent;
	//std::vector<SceneComponent*> children;
};