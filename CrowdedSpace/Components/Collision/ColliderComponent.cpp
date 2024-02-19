#include "ColliderComponent.h"
#include "../Scene/SceneComponent.h"
#include "../../Actors/Actor.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Worlds/World.h"
#include "../../App/app.h"

Collider2D::Collider2D() : m_isActive(true), m_offset(Transform2D::ZeroTransform)
{
	m_name = "Collider";
}

const bool Collider2D::GetIsActive() const
{
	return m_isActive;
}

void Collider2D::SetIsActive(bool active)
{
	m_isActive = active;
}

const Transform2D& Collider2D::GetOffset() const
{
	return m_offset;
}

void Collider2D::SetOffset(const Transform2D& offset)
{
	m_offset = offset;
}

const Vector2D Collider2D::GetWorldPosition() const
{
	if (GetOwner()->GetRootComponent() == nullptr) return {};

	return GetOwner()->GetRootComponent()->GetPosition() + GetOffset().position;
}

const std::vector<Collider2D*>& Collider2D::GetOverlappingColliders() const
{
	return m_overlappingColliders;
}

void Collider2D::Update(float deltaTime)
{
	//CheckCollision();
}

void Collider2D::EndPlay()
{
	for (Collider2D* collider : m_overlappingColliders)
	{
		collider->TryRemoveOverlap(this);
	}
	m_overlappingColliders.clear();

	Component::EndPlay();
}

void Collider2D::TryAddOverlap(Collider2D* collider)
{
	// new overlapping collider
	if (!HelperFunctions::contains(m_overlappingColliders, collider))
	{
		m_overlappingColliders.push_back(collider);
		OnBeginOverlap.Broadcast(collider);
	}
}

void Collider2D::TryRemoveOverlap(Collider2D* collider)
{
	// the other collider does not overlap anymore with this collider
	if (HelperFunctions::contains(m_overlappingColliders, collider))
	{
		HelperFunctions::remove(m_overlappingColliders, collider);
		OnEndOverlap.Broadcast(collider);
	}
}

BoxCollider2D::BoxCollider2D() : m_width(1.0f), m_height(1.0f)
{
	m_name = "BoxCollider";
}

const float BoxCollider2D::GetWidth() const
{
	return m_width;
}

void BoxCollider2D::SetWidth(float width)
{
	m_width = width;
}

const float BoxCollider2D::GetHeight() const
{
	return m_height;
}

void BoxCollider2D::SetHeight(float height)
{
	m_height = height;
}

const float BoxCollider2D::GetRealWidth() const
{
	return GetWidth() * GetOffset().scale;
}

const float BoxCollider2D::GetRealHeight() const
{
	return GetHeight() * GetOffset().scale;
}

const float BoxCollider2D::GetRealHalfWidth() const
{
	return GetRealWidth() / 2;
}

const float BoxCollider2D::GetRealHalfHeight() const
{
	return GetRealHeight() / 2;
}

bool BoxCollider2D::CheckCollision(Collider2D* collider)
{
	BoxCollider2D* box = HelperFunctions::cast<BoxCollider2D>(collider);
	if (box != nullptr)
	{
		return GameplayStatics::GetInstance().CheckBoxToBoxCollision(this, box);
	}

	CircleCollider2D* circle = HelperFunctions::cast<CircleCollider2D>(collider);
	if (circle != nullptr)
	{
		return GameplayStatics::GetInstance().CheckBoxToCircleCollision(this, circle);
	}
}

void BoxCollider2D::Render()
{
	/*SceneComponent* ownerSC = GetOwner()->GetRootComponent();

	Vector2D pos = ownerSC->GetPosition() + GetOffset().position;
	float width = GetWidth() * GetOffset().scale;
	float height = GetHeight() * GetOffset().scale;

	GameplayStatics::DrawBox(pos, width, height, RGBColor::White);*/
}

CircleCollider2D::CircleCollider2D() : m_radius(1.0f)
{
	m_name = "CircleCollider";
}

const float CircleCollider2D::GetRadius() const
{
	return m_radius;
}

void CircleCollider2D::SetRadius(float radius)
{
	m_radius = radius;
}

const float CircleCollider2D::GetRealRadius() const
{
	return m_radius * GetOffset().scale;
}

bool CircleCollider2D::CheckCollision(Collider2D* collider)
{
	CircleCollider2D* circle = HelperFunctions::cast<CircleCollider2D>(collider);
	if (circle != nullptr)
	{
		return GameplayStatics::GetInstance().CheckCircleToCircleCollision(this, circle);
	}

	BoxCollider2D* box = HelperFunctions::cast<BoxCollider2D>(collider);
	if (box != nullptr)
	{
		return GameplayStatics::GetInstance().CheckBoxToCircleCollision(box, this);
	}
}