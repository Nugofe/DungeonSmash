#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

class SceneComponent;

class MovementComponent : public Component
{
public:
	MovementComponent();

	float GetSpeed() const;
	void SetSpeed(float speed);
	Vector2D GetVelocity() const;

	void AddInputVector(const Vector2D& direction);

	virtual void BeginPlay() override;
	virtual void EndPlay();
	virtual void Update(float deltaTime) override;

protected:
	float m_speed;
	Vector2D m_inputVector;
	Vector2D m_velocityVector;

	SceneComponent* m_ownerSceneComponent;
};