#include "Effect.h"
#include "../../Actors/Actor.h"

Effect::Effect() : 
	m_applictationType(EApplicationType::INMEDIATE),
	/*activationType(EActivationType::PRESS),
	pulsations(1.0), currentPulsations(0.0),*/ /*m_isApplying(false), m_wasApplied(false), m_isCoolingDown(false),*/
	m_duration(1.0f), /*m_durationLeft(1.0f),*/
	m_cooldown(0.0f) /*m_cooldownLeft(0.0f),*/
	//m_target(nullptr)
{
	m_name = "Effect";
}

/*EActivationType Effect::GetActivationType() const
{
	return activationType;
}

void Effect::SetActivationType(EActivationType activationType, float pulsations)
{
	this->activationType = activationType;
	SetPulsations(pulsations);
}

float Effect::GetPulsations() const
{
	return pulsations;
}*/

//void Effect::SetPulsations(int pulsations)
//{
	/*if (pulsations <= 0) // only natural numbers (>=1)
	{
		pulsations = 1.0f;
	}

	switch (this->activationType)
	{
	case EActivationType::PRESS:
		this->pulsations = floor(pulsations); // number of pulsations
		break;
	case EActivationType::HOLD_PRESS:
		this->pulsations = pulsations; // time that the action needs to happen
		break;
	default:
		break;
	}*/

	/*this->pulsations = pulsations;
	if (this->pulsations == 0 || this->pulsations < -1)
	{
		this->pulsations = -1;
		if(!isApplying)
		{
			currentPulsations = 0;
		}
	}*/
//}

void Effect::SetApplicationType(EApplicationType type)
{
	m_applictationType = type;
}

float Effect::GetDuration() const
{
	return m_duration;
}

void Effect::SetDuration(float duration)
{
	if (duration > 0.0f)
	{
		m_duration = duration;
	}
}

float Effect::GetCooldown() const
{
	return m_cooldown;
}

void Effect::SetCooldown(float cooldown)
{
	m_cooldown = cooldown;
}

//void Effect::Apply(/*Actor* instigator, Actor* causer,*/ Actor* target)
//{
//	if(/*m_isCoolingDown ||*/ m_isApplying || target == nullptr) return;
//
//	/*switch (this->activationType)
//	{
//	// Press: actually apply the effect when pulsations reached
//	case EActivationType::PRESS:
//		if (pulsations > -1)
//		{
//			++currentPulsations;
//			if (currentPulsations == pulsations)
//			{
//				currentPulsations = 0;
//			}
//			else
//			{
//				return;
//			}
//		}
//		break;
//	// Other: break
//	case EActivationType::HOLD_PRESS:
//	default:
//		break;
//	}*/
//	
//	m_target = target;
//	m_isApplying = true;
//}

void Effect::Apply(/*Actor* instigator, Actor* causer,*/ Actor* target)
{
}

void Effect::Revert(Actor* target)
{
}

//void Effect::Update(float deltaTime)
//{
//	/*switch (this->activationType)
//	{
//	case EActivationType::PRESS:
//		if (!isApplying) return;
//		break;
//	
//	case EActivationType::HOLD_PRESS:
//		if (!isApplying) 
//		{
//			currentPulsations += deltaTime;
//			if (currentPulsations >= pulsations)
//			{
//				isApplying = true;
//			}
//		}
//		break;
//
//	default:
//		break;
//	}*/
//
//	// is cooling down
//	/*if (m_isCoolingDown && m_cooldown > 0.0f)
//	{
//		m_cooldownLeft -= deltaTime;
//		if (m_cooldownLeft <= 0.0f)
//		{
//			m_cooldownLeft = m_cooldown;
//			m_isCoolingDown = false;
//			return;
//		}
//	}*/
//
//	if (!m_isApplying) return;
//
//	// is applying
//	switch (m_applictationType)
//	{
//	case INMEDIATE:
//		if (!m_wasApplied)
//		{
//			DoApply(m_target);
//			m_wasApplied = true;
//		}
//		break;
//
//	case OVER_TIME:
//		DoApply(m_target);
//		break;
//
//	default:
//		break;
//	}
//
//	m_durationLeft -= deltaTime;
//	if (m_durationLeft <= 0.0f)
//	{
//		m_isApplying = false;
//		m_wasApplied = false;
//		m_isCoolingDown = true;
//	}
//}