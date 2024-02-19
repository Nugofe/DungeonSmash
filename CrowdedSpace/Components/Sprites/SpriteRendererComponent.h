#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

struct SpriteAsset;

class SpriteRendererComponent : public Component
{
public:
	 SpriteRendererComponent();
	 ~SpriteRendererComponent();

	 const SpriteAsset* GetSpriteAsset() const;
	 void SetSpriteAsset(const SpriteAsset* spriteAsset);

	 const Transform2D& GetTransform() const;
	 void SetTransform(const Transform2D& transform);
	 const Vector2D& GetPosition() const;
	 void SetPosition(float x, float y);
	 void SetPosition(const Vector2D& position);
	 const float GetRotation() const;
	 void SetRotation(float rotation);
	 const float GetScale() const;
	 void SetScale(float scale);

	 bool GetIsVisible() const;
	 void SetIsVisible(bool visible);

	 virtual void BeginPlay() override;
	 virtual void EndPlay() override;
	 virtual void Render() override;

	 bool IsValid() const;

public:
	Delegate<> OnSpriteChanged;
	Delegate<> OnBeginRender;

protected:
	const SpriteAsset* m_spriteAsset;
	bool m_isVisible;
	Transform2D m_offset;
};