#include "PlayerAnimComponent.h"
#include "../../../Utils/AnimationEnums.h"
#include "../../../Actors/Actor.h"

void PlayerAnimComponent::Update(float deltaTime)
{
	AnimationComponent::Update(deltaTime);

	ChangeWalkAnimation();
}

void PlayerAnimComponent::ChangeWalkAnimation()
{
	Vector2D velocity = GetOwner()->GetVelocity();
	if (velocity == Vector2D::ZeroVector)
	{
		SetFrame(0);
		Pause();
	}
	else
	{
		if (velocity.x > 0.0f)
		{
			SetAnimation(FourWayWalkAnimations::ANIM_RIGHT);
		}
		if (velocity.x < 0.0f)
		{
			SetAnimation(FourWayWalkAnimations::ANIM_LEFT);
		}
		if (velocity.y > 0.0f)
		{
			SetAnimation(FourWayWalkAnimations::ANIM_BACKWARDS);
		}
		if (velocity.y < 0.0f)
		{
			SetAnimation(FourWayWalkAnimations::ANIM_FORWARDS);
		}
		Resume();
	}
}
