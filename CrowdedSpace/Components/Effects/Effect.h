#pragma once

#include "../../Components/Component.h"
#include "../../Worlds/World.h"

class Actor;

/*enum EActivationType
{
	PRESS,
	HOLD_PRESS
};*/

enum EApplicationType
{
	INMEDIATE,
	OVER_TIME
};

class Effect : public Component
{
public:
	Effect();

	/*EActivationType GetActivationType() const;
	void SetActivationType(EActivationType activationType, float pulsations);
	float GetPulsations() const;
	void SetPulsations(int pulsations);*/
	void SetApplicationType(EApplicationType type);
	float GetDuration() const;
	void SetDuration(float duration);
	float GetCooldown() const;
	void SetCooldown(float cooldown);

	virtual void Apply(/*Actor* instigator, Actor* causer,*/ Actor* target);
	virtual void Revert(Actor* target);

protected:
	//EActivationType activationType;
	EApplicationType m_applictationType;

	// EActivationType::PRESS      -> 1 or more pulsations = number of pulsations to actually apply the effect
	// EActivationType::HOLD_PRESS -> time the action must happen to actually apply the effect
	/*float pulsations;
	float currentPulsations;*/
	//bool m_isApplying;
	//bool m_wasApplied;
	//bool m_isCoolingDown;

	float m_duration;
	//float m_durationLeft;

	float m_cooldown;
	//float m_cooldownLeft;

	friend class World;

//private:
	//Actor* instigator;
	//Actor* m_target;
};