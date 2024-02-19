#include "MovementComponent.h"
#include "../Scene/SceneComponent.h"
#include "../../Actors/Actor.h"
#include "../../App/AppSettings.h"

#include <algorithm>

MovementComponent::MovementComponent() : 
	m_speed(150.0f), 
	m_inputVector(Vector2D::ZeroVector),
	m_velocityVector(Vector2D::ZeroVector),
	m_ownerSceneComponent(nullptr)
{
	m_name = "MovementComponent";
}

float MovementComponent::GetSpeed() const
{
	return m_speed;
}

void MovementComponent::SetSpeed(float speed)
{
	if (speed > 0.0f)
	{
		m_speed = speed;
	}
}

Vector2D MovementComponent::GetVelocity() const
{
	return m_velocityVector;
}

void MovementComponent::AddInputVector(const Vector2D& direction)
{
	m_inputVector.x += direction.x;
	m_inputVector.y += direction.y;
	m_inputVector.Normalize();
}

void MovementComponent::BeginPlay()
{
	Component::BeginPlay();

	m_ownerSceneComponent = GetOwner()->GetRootComponent();
}

void MovementComponent::EndPlay()
{
	m_ownerSceneComponent = nullptr;

	Component::EndPlay();
}

void MovementComponent::Update(float deltaTime)
{
	if (m_ownerSceneComponent == nullptr) return;

	// calculate moveAmount
	m_velocityVector = Vector2D(m_inputVector.x * m_speed, m_inputVector.y * m_speed);              // direction * speed
	Vector2D moveAmount = Vector2D(m_velocityVector.x * deltaTime, m_velocityVector.y * deltaTime); // velocity * deltatime

	// set position
	Vector2D currentPosition = m_ownerSceneComponent->GetPosition();
	Vector2D newPosition;
	newPosition.x = std::clamp<float>(currentPosition.x + moveAmount.x, 0 + 40, APP_VIRTUAL_WIDTH - 40);
	newPosition.y = std::clamp<float>(currentPosition.y + moveAmount.y, 0 + 50, APP_VIRTUAL_HEIGHT - 50);
	m_ownerSceneComponent->SetPosition(newPosition.x, newPosition.y);
	
	// reset input vector
	m_inputVector = Vector2D::ZeroVector;
}