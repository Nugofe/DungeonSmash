#pragma once

#include "Effect.h"

class Actor;

class DamageEffect : public Effect
{
public:
	DamageEffect();

	float GetDamage() const;
	void SetDamage(float damage);

	virtual void Apply(Actor* target);

private:
	float m_damage;
};
