#pragma once

#include "AnimationComponent.h"

class SpriteRendererComponent;
struct AnimationAsset;

class PlayerAnimComponent : public AnimationComponent
{
public:
	PlayerAnimComponent() = default;

	virtual void Update(float deltaTime) override;

private:
	void ChangeWalkAnimation();
};