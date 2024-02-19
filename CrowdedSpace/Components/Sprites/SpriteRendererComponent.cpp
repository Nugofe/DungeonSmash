#include "SpriteRendererComponent.h"
#include "SpriteUtils.h"
#include "../../Actors/Actor.h"
#include "../Scene/SceneComponent.h"
#include "../../App/app.h"
#include "../../App/SimpleSprite.h"

SpriteRendererComponent::SpriteRendererComponent() : 
	m_spriteAsset(nullptr), m_isVisible(true), m_offset(Transform2D::ZeroTransform)
{
	m_name = "SpriteRendererComponent";
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	Destroy();
}

const SpriteAsset* SpriteRendererComponent::GetSpriteAsset() const
{
	return m_spriteAsset;
}

void SpriteRendererComponent::SetSpriteAsset(const SpriteAsset* spriteAsset)
{
	m_spriteAsset = spriteAsset;
	OnSpriteChanged.Broadcast();
}

const Transform2D& SpriteRendererComponent::GetTransform() const
{
	return m_offset;
}

void SpriteRendererComponent::SetTransform(const Transform2D& transformOffset)
{
	m_offset = transformOffset;
}

const Vector2D& SpriteRendererComponent::GetPosition() const
{
	return m_offset.position;
}

void SpriteRendererComponent::SetPosition(float x, float y)
{
	m_offset.position.x = x;
	m_offset.position.y = y;
}

void SpriteRendererComponent::SetPosition(const Vector2D& position)
{
	m_offset.position = position;
}

const float SpriteRendererComponent::GetRotation() const
{
	return m_offset.rotation;
}

void SpriteRendererComponent::SetRotation(float rotation)
{
	m_offset.rotation = rotation;
}

const float SpriteRendererComponent::GetScale() const
{
	return m_offset.scale;
}

void SpriteRendererComponent::SetScale(float scale)
{
	m_offset.scale = scale;
}

bool SpriteRendererComponent::GetIsVisible() const
{
	return m_isVisible;
}

void SpriteRendererComponent::SetIsVisible(bool visible)
{
	m_isVisible = visible;
}

void SpriteRendererComponent::BeginPlay()
{
	Component::BeginPlay();
}

void SpriteRendererComponent::EndPlay()
{
	m_spriteAsset = nullptr;

	Component::EndPlay();
}

void SpriteRendererComponent::Render()
{
	OnBeginRender.Broadcast();

	if (m_isVisible && m_spriteAsset != nullptr && m_spriteAsset->sprite != nullptr)
	{
		if (GetOwner()->GetRootComponent() != nullptr)
		{
			const Transform2D& ownerTransform = GetOwner()->GetRootComponent()->GetTransform();

			m_spriteAsset->sprite->SetPosition(
				ownerTransform.position.x + m_offset.position.x,
				ownerTransform.position.y + m_offset.position.y
			);
			m_spriteAsset->sprite->SetAngle(ownerTransform.rotation + m_offset.rotation);
			m_spriteAsset->sprite->SetScale(ownerTransform.scale * m_offset.scale);
		}
		m_spriteAsset->sprite->Draw();
	}
}

bool SpriteRendererComponent::IsValid() const
{
	return this != nullptr && m_spriteAsset != nullptr && m_spriteAsset->sprite != nullptr;
}
