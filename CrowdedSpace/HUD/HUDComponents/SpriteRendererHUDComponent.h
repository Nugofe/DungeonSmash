//#pragma once
//
//#include "HUDComponent.h"
//#include "../../Utils/Utils.h"
//
//struct SpriteAsset;
//
//class SpriteRendererHUDComponent : public HUDComponent
//{
//public:
//	 SpriteRendererHUDComponent();
//	 ~SpriteRendererHUDComponent();
//
//	 const SpriteAsset* GetSpriteAsset() const;
//	 void SetSpriteAsset(const SpriteAsset* spriteAsset);
//
//	 const Transform2D& GetTransform() const;
//	 void SetTransform(const Transform2D& transform);
//	 const Vector2D& GetPosition() const;
//	 void SetPosition(float x, float y);
//	 void SetPosition(const Vector2D& position);
//	 const float GetRotation() const;
//	 void SetRotation(float rotation);
//	 const float GetScale() const;
//	 void SetScale(float scale);
//
//	 bool GetIsVisible() const;
//	 void SetIsVisible(bool visible);
//
//	 //virtual void Update(float deltaTime) override;
//	 virtual void Render() override;
//	 virtual void Destroy() override;
//
//	 bool IsValid() const;
//
//protected:
//	const SpriteAsset* m_spriteAsset;
//	bool m_isVisible;
//	Transform2D m_offset;
//};