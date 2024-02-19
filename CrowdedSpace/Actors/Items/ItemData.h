#pragma once

#include "../../Components/Component.h"
#include "../../Utils/Utils.h"

#include <vector>

class Actor;
class Effect;
class DamageEffect;
class VFXCircle;
class SFXComponent;

class ItemData : public Component
{
public:
	ItemData();
	
	void PlaySFX() const;

	virtual bool Activate();
	virtual void Deactivate();

	virtual void EndPlay() override;
	virtual void Update(float deltaTime) override;

protected:
	void ResetActivated();

public:
	Delegate<> OnActivate;

protected:
	bool m_isActive;
	float m_cooldown;
	std::vector<Effect*> m_effects;

	SFXComponent* m_sfxComponent;

	friend class World;
	friend class Item;
};

class IDSimpleSword : public ItemData
{
public:
	IDSimpleSword();
	IDSimpleSword(float damage, float threshold);

	virtual bool Activate() override;

	virtual void EndPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

private:
	void Init();

protected:
	DamageEffect* m_damageEffect;
	float m_threshold;

	VFXCircle* m_circleVFX;
};