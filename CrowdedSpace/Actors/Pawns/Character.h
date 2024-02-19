#pragma once

#include "Pawn.h"
#include "../../Utils/Utils.h"

class BoxCollider2D;
class SpriteRendererComponent;
class AnimationComponent;
class MovementComponent;
class HealthComponent;

class Character : public Pawn
{
public:
	Character();

	BoxCollider2D* GetCollider() const;
	SpriteRendererComponent* GetSpriteRenderer() const;
	AnimationComponent* GetAnimationComponent() const;
	MovementComponent* GetMovementComponent() const;
	HealthComponent* GetHealthComponent() const;

	virtual void MoveRight();
	virtual void MoveLeft();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;

private:
	void OnSpriteChanged();

protected:
	BoxCollider2D* m_collider;
	SpriteRendererComponent* m_spriteRenderer;
	AnimationComponent* m_animationComponent;
	MovementComponent* m_movementComponent;
	HealthComponent* m_healthComponent;

	DelegateHandle m_spriteChangedHandle;
};