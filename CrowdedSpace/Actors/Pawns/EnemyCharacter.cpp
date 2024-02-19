#include "EnemyCharacter.h"
#include "../../Components/Sprites/SpriteRendererComponent.h"
#include "../../Components/Sprites/Animations/AnimationComponent.h"
#include "../../Components/Scene/SceneComponent.h"
#include "../../Components/Health/HealthComponent.h"
#include "../../Components/SFX/SFXComponent.h"
#include "../../Assets.h"

EnemyCharacter::EnemyCharacter() : m_sfxComponent(new SFXComponent(Assets::GetInstance().enemyDeathSound))
{
	m_name = "EnemyCharacter";

	m_animationComponent = AddComponent<AnimationComponent>();
	m_healthComponent->SetHealth(1.0f);
	m_sfxComponent->m_volume = -2000;
}

void EnemyCharacter::BeginPlay()
{
	Character::BeginPlay();

	m_spriteRenderer->SetSpriteAsset(Assets::GetInstance().enemySpriteAsset);
	m_animationComponent->SetAnimationAsset(Assets::GetInstance().enemyAnimationAsset);
	m_rootComponent->SetScale(0.6f);
}

void EnemyCharacter::EndPlay()
{
	if(m_healthComponent->GetCurrentHealth() <= 0.0f)
	{
		OnEnemyDied.Broadcast(this);
		m_sfxComponent->Play();
	}

	Character::EndPlay();
}