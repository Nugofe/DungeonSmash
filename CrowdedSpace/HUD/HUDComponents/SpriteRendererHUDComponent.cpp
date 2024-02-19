//#include "SpriteRendererHUDComponent.h"
//
//#include "../../Components/Sprites/SpriteUtils.h"
//#include "../../Actors/Actor.h"
//#include "../../App/app.h"
//#include "../../App/SimpleSprite.h"
//
//SpriteRendererHUDComponent::SpriteRendererHUDComponent() : 
//	m_spriteAsset(nullptr), m_isVisible(true), m_offset(Transform2D::ZeroTransform)
//{
//}
//
//SpriteRendererHUDComponent::~SpriteRendererHUDComponent()
//{
//	Destroy();
//}
//
//const SpriteAsset* SpriteRendererHUDComponent::GetSpriteAsset() const
//{
//	return m_spriteAsset;
//}
//
//void SpriteRendererHUDComponent::SetSpriteAsset(const SpriteAsset* spriteAsset)
//{
//	m_spriteAsset = spriteAsset;
//}
//
//const Transform2D& SpriteRendererHUDComponent::GetTransform() const
//{
//	return m_offset;
//}
//
//void SpriteRendererHUDComponent::SetTransform(const Transform2D& transformOffset)
//{
//	m_offset = transformOffset;
//}
//
//const Vector2D& SpriteRendererHUDComponent::GetPosition() const
//{
//	return m_offset.position;
//}
//
//void SpriteRendererHUDComponent::SetPosition(float x, float y)
//{
//	m_offset.position.x = x;
//	m_offset.position.y = y;
//}
//
//void SpriteRendererHUDComponent::SetPosition(const Vector2D& position)
//{
//	m_offset.position = position;
//}
//
//const float SpriteRendererHUDComponent::GetRotation() const
//{
//	return m_offset.rotation;
//}
//
//void SpriteRendererHUDComponent::SetRotation(float rotation)
//{
//	m_offset.rotation = rotation;
//}
//
//const float SpriteRendererHUDComponent::GetScale() const
//{
//	return m_offset.scale;
//}
//
//void SpriteRendererHUDComponent::SetScale(float scale)
//{
//	m_offset.scale = scale;
//}
//
//bool SpriteRendererHUDComponent::GetIsVisible() const
//{
//	return m_isVisible;
//}
//
//void SpriteRendererHUDComponent::SetIsVisible(bool visible)
//{
//	m_isVisible = visible;
//}
//
///*void SpriteRendererHUDComponent::Update(float deltaTime)
//{
//	spriteAsset->sprite->Update(deltaTime);
//}*/
//
//void SpriteRendererHUDComponent::Render()
//{
//	if (m_isVisible && m_spriteAsset != nullptr && m_spriteAsset->sprite != nullptr)
//	{
//		if (m_parent->GetRootComponent() != nullptr)
//		{
//			const Transform2D& ownerTransform = m_parent->GetRootComponent()->GetTransform();
//
//			m_spriteAsset->sprite->SetPosition(
//				ownerTransform.position.x + m_offset.position.x,
//				ownerTransform.position.y + m_offset.position.y
//			);
//			m_spriteAsset->sprite->SetAngle(ownerTransform.rotation + m_offset.rotation);
//			m_spriteAsset->sprite->SetScale(ownerTransform.scale * m_offset.scale);
//		}
//		//spriteAsset->sprite->Update(0.0f);
//		m_spriteAsset->sprite->Draw();
//	}
//}
//
//void SpriteRendererHUDComponent::Destroy()
//{
//}
//
//bool SpriteRendererHUDComponent::IsValid() const
//{
//	return this != nullptr && m_spriteAsset != nullptr && m_spriteAsset->sprite != nullptr;
//}