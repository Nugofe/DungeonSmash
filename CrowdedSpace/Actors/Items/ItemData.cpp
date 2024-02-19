#include "ItemData.h"
#include "../Actor.h"
#include "../../Worlds/World.h"
#include "../../Utils/Utils.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Managers/TimerManager.h"
#include "../../Components/Effects/Effect.h"
#include "../../Components/Effects/DamageEffect.h"
#include "../../Components/Scene/SceneComponent.h"
#include "../Pawns/Character.h"
#include "../../Components/VFX/VFXComponent.h"
#include "../../Components/SFX/SFXComponent.h"
#include "../../Assets.h"

ItemData::ItemData() : m_isActive(false), m_cooldown(0.0f), m_sfxComponent(nullptr)
{
}

void ItemData::PlaySFX() const
{
	if (m_sfxComponent != nullptr)
	{
		m_sfxComponent->Play();
	}
}

bool ItemData::Activate()
{
	if (GetOwner() == nullptr || m_isActive) return false;

	m_isActive = true;
	GameplayStatics::GetInstance().GetCurrentWorld()->
		GetTimerManager().SetTimer(m_cooldown, this, &ItemData::ResetActivated, false);
	OnActivate.Broadcast();

	return true;

	// each subclass of item data should override this method, call it, 
	// and then do the apply of its effects in the way that best suits them
}

void ItemData::Deactivate()
{
	ResetActivated();
	// TODO: clear timer
}

void ItemData::ResetActivated()
{
	m_isActive = false;
}

void ItemData::EndPlay()
{
	if (m_sfxComponent != nullptr)
	{
		delete m_sfxComponent;
		m_sfxComponent = nullptr;
	}

	for (Effect* effect : m_effects)
	{
		if (effect != nullptr)
		{
			effect->EndPlay();
		}
		delete effect;
	}
	m_effects.clear();

	Component::EndPlay();
}

void ItemData::Update(float deltaTime)
{
	Component::Update(deltaTime);

	if (!m_isActive) return;

	for (Effect* effect : m_effects)
	{
		effect->Update(deltaTime);
	}
}

IDSimpleSword::IDSimpleSword() : 
	m_threshold(100.0f),
	m_damageEffect(new DamageEffect()),
	m_circleVFX(new VFXCircle())
{
	m_damageEffect->SetDamage(10.0f);
	Init();
}

IDSimpleSword::IDSimpleSword(float damage, float threshold) : 
	m_threshold(threshold),
	m_damageEffect(new DamageEffect()), 
	m_circleVFX(new VFXCircle())
{
	m_damageEffect->SetDamage(damage);
	Init();
}

bool IDSimpleSword::Activate()
{
	bool canProceed = ItemData::Activate();
	if (!canProceed) return false;

	Actor* owner = GetOwner();

	m_circleVFX->m_center = owner->GetRootComponent()->GetPosition();
	m_circleVFX->Play();
	PlaySFX();

	// get actors in a range of "m_threshold" and apply them damage effect
	// (not apply the effect to the actor that activates the item)
	const World* world = GameplayStatics::GetInstance().GetCurrentWorld();
	for (Actor* a : world->GetActors())
	{
		if (a == owner) continue;

		float dist = Vector2D::DistanceSquare(
			owner->GetRootComponent()->GetPosition(),
			a->GetRootComponent()->GetPosition()
		);
		if (dist <= m_threshold * m_threshold)
		{
			m_damageEffect->Apply(a);
		}
	}

	return true;
}

void IDSimpleSword::EndPlay()
{
	m_damageEffect = nullptr;
	delete m_circleVFX;
	m_circleVFX = nullptr;

	ItemData::EndPlay();
}

void IDSimpleSword::Update(float deltaTime)
{
	ItemData::Update(deltaTime);

	m_circleVFX->Update(deltaTime);
}

void IDSimpleSword::Render()
{
	ItemData::Render();

	m_circleVFX->Render();
}

void IDSimpleSword::Init()
{
	m_cooldown = 0.5f;

	m_effects.push_back(m_damageEffect);

	m_circleVFX->m_radius = m_threshold;
	m_circleVFX->SetTime(0.2f);

	m_sfxComponent = new SFXComponent(Assets::GetInstance().simpleSwordSound);
}