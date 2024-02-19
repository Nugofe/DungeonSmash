#include "ShieldEffect.h"
#include "../Health/HealthComponent.h"
#include "../../Utils/Utils.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Managers/TimerManager.h"

ShieldEffect::ShieldEffect() : m_target(nullptr)
{
	m_duration = 2.0f;
}

void ShieldEffect::Apply(Actor* target)
{
	if (target == nullptr) return;

	HealthComponent* healthComp = target->GetComponent<HealthComponent>();
	if (healthComp != nullptr)
	{
		healthComp->SetIsInvulnerable(true);
		m_target = target;
	}

	GameplayStatics::GetInstance().GetCurrentWorld()->
		GetTimerManager().SetTimer(m_duration, this, &ShieldEffect::DoRevert, false);
}

void ShieldEffect::Revert(Actor* target)
{
	if (m_target == nullptr || target == nullptr || m_target != target) return;

	HealthComponent* healthComp = target->GetComponent<HealthComponent>();
	if (healthComp != nullptr)
	{
		healthComp->SetIsInvulnerable(false);
		m_target = nullptr;
	}
}

void ShieldEffect::DoRevert()
{
	Revert(m_target);
}
