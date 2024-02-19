#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

class HealthComponent : public Component
{
public:
	HealthComponent();

	float GetMaxHealth() const;
	void SetMaxHealth(float health);
	float GetCurrentHealth() const;
	void SetCurrentHealth(float health);
	void SetHealth(float health);
	bool GetIsInvulnerable() const;
	void SetIsInvulnerable(bool invulnerable);

	void TakeDamage(float damage);
	void TakeHealing(float healing);

public:
	Delegate<float> HealthUpdatedDelegate;

private:
	float m_maxHealth;
	float m_currentHealth;
	bool m_isInvulnerable;
};