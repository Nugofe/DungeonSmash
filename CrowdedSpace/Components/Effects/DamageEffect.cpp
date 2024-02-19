#include "DamageEffect.h"
#include "../../Actors/Actor.h"
#include "../Health/HealthComponent.h"

DamageEffect::DamageEffect() : m_damage(10.0f)
{
	m_name = "DamageEffect";
}

float DamageEffect::GetDamage() const
{
	return m_damage;
}

void DamageEffect::SetDamage(float damage)
{
	m_damage = damage;
	if (damage <= 0.0f)
	{
		m_damage = 0.01f;
	}
}

void DamageEffect::Apply(Actor* target)
{
	if (target == nullptr) return;

	HealthComponent* healthComp = target->GetComponent<HealthComponent>();
	if (healthComp != nullptr)
	{
		healthComp->TakeDamage(m_damage);
	}
}