#include "Character.h"
#include "../../Components/Collision/ColliderComponent.h"
#include "../../Components/Sprites/SpriteRendererComponent.h"
#include "../../Components/Sprites/Animations/AnimationComponent.h"
#include "../../Components/Sprites/SpriteUtils.h"
#include "../../Components/Movement/MovementComponent.h"
#include "../../Components/Health/HealthComponent.h"

Character::Character() :
	m_collider(AddComponent<BoxCollider2D>()),
	m_spriteRenderer(AddComponent<SpriteRendererComponent>()),
	m_animationComponent(nullptr),
	m_movementComponent(AddComponent<MovementComponent>()),
	m_healthComponent(AddComponent<HealthComponent>())
{
	m_name = "Character";
}

BoxCollider2D* Character::GetCollider() const
{
	return m_collider;
}

SpriteRendererComponent* Character::GetSpriteRenderer() const
{
	return m_spriteRenderer;
}

AnimationComponent* Character::GetAnimationComponent() const
{
	return m_animationComponent;
}

MovementComponent* Character::GetMovementComponent() const
{
	return m_movementComponent;
}

HealthComponent* Character::GetHealthComponent() const
{
	return m_healthComponent;
}

void Character::MoveRight()
{
	m_movementComponent->AddInputVector(Vector2D(1.0f, 0.0f));
}

void Character::MoveLeft()
{
	m_movementComponent->AddInputVector(Vector2D(-1.0f, 0.0f));
}

void Character::MoveUp()
{
	m_movementComponent->AddInputVector(Vector2D(0.0f, 1.0f));
}

void Character::MoveDown()
{
	m_movementComponent->AddInputVector(Vector2D(0.0f, -1.0f));
}

void Character::BeginPlay()
{
	Pawn::BeginPlay();

	if (m_spriteRenderer != nullptr)
	{
		m_spriteChangedHandle = m_spriteRenderer->OnSpriteChanged.Subscribe(this, &Character::OnSpriteChanged);
	}
}

void Character::EndPlay()
{
	if (m_spriteRenderer != nullptr)
	{
		m_spriteRenderer->OnSpriteChanged.Unsubscribe(m_spriteChangedHandle);
	}
	m_collider = nullptr;
	m_spriteRenderer = nullptr;
	m_movementComponent = nullptr;
	m_healthComponent = nullptr;

	Pawn::EndPlay();
}

void Character::OnSpriteChanged()
{
	m_collider->SetWidth( m_spriteRenderer->GetSpriteAsset()->sprite->GetWidth() );
	m_collider->SetHeight( m_spriteRenderer->GetSpriteAsset()->sprite->GetHeight() );
}