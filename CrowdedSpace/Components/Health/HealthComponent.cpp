#include "HealthComponent.h"
#include "../../Actors/Actor.h"

#include <windows.h>

HealthComponent::HealthComponent() : 
	m_maxHealth(100.0f), m_currentHealth(100.0f), m_isInvulnerable(false)
{
	m_name = "HealthComponent";
}

float HealthComponent::GetMaxHealth() const
{
	return m_maxHealth;
}

void HealthComponent::SetMaxHealth(float health)
{
	m_maxHealth = health;
}

float HealthComponent::GetCurrentHealth() const
{
	return m_currentHealth;
}

void HealthComponent::SetCurrentHealth(float health)
{
	m_currentHealth = health;
}

void HealthComponent::SetHealth(float health)
{
	m_maxHealth = health;
	m_currentHealth = health;
}

bool HealthComponent::GetIsInvulnerable() const
{
	return m_isInvulnerable;
}

void HealthComponent::SetIsInvulnerable(bool invulnerable)
{
	m_isInvulnerable = invulnerable;
}

void HealthComponent::TakeDamage(float damage)
{
	if (m_isInvulnerable) return;
		
	m_currentHealth -= damage;
	HealthUpdatedDelegate.Broadcast(m_currentHealth);
	if (m_currentHealth <= 0.0f)
	{
		/*char text[100];
		sprintf_s(text, "DESTROYED!!!:  DAMAGE '%f'   -   CURRENT HEALTH '%f'\n", damage, m_currentHealth);
		OutputDebugStringA(text);*/

		GetOwner()->Destroy();
	} 
	else
	{
		char text[100];
		sprintf_s(text, "DAMAGE '%f'   -   CURRENT HEALTH '%f'\n", damage, m_currentHealth);
		OutputDebugStringA(text);
	}
}

void HealthComponent::TakeHealing(float healing)
{
	float health = m_currentHealth + healing;
	if (health <= m_maxHealth)
	{
		m_currentHealth = health;
	}
	else 
	{
		m_currentHealth = m_maxHealth;
	}
	HealthUpdatedDelegate.Broadcast(m_currentHealth);
}