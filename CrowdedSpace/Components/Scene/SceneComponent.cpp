#include "SceneComponent.h"

SceneComponent::SceneComponent() : m_transform(Transform2D::ZeroTransform)/*, parent(nullptr)*/
{
	m_name = "SceneComponent";
}

SceneComponent::~SceneComponent()
{
	Destroy();
}

const Transform2D& SceneComponent::GetTransform() const
{
	return m_transform;
}

void SceneComponent::SetTransform(const Transform2D& transform)
{
	m_transform = transform;
}

const Vector2D& SceneComponent::GetPosition() const
{
	return m_transform.position;
}

void SceneComponent::SetPosition(float x, float y)
{
	m_transform.position.x = x;
	m_transform.position.y = y;
}

void SceneComponent::SetPosition(const Vector2D& position)
{
	m_transform.position = position;
}

const float SceneComponent::GetRotation() const
{
	return m_transform.rotation;
}

void SceneComponent::SetRotation(float rotation)
{
	m_transform.rotation = rotation;
}

const float SceneComponent::GetScale() const
{
	return m_transform.scale;
}

void SceneComponent::SetScale(float scale)
{
	m_transform.scale = scale;
}

/*const SceneComponent* SceneComponent::GetParent() const
{
	return parent;
}

void SceneComponent::SetParent(const SceneComponent* parent)
{
	this->parent = const_cast<SceneComponent*>(parent);
}*/

/*const std::vector<SceneComponent*>& SceneComponent::GetChildren() const
{
	return children;
}

void SceneComponent::AddChild(const SceneComponent* child)
{
}*/