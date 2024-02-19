#pragma once

#include "Effect.h"

class Actor;

class ShieldEffect : public Effect
{
public:
	ShieldEffect();

	virtual void Apply(Actor* target) override;

private:
	virtual void Revert(Actor* target) override;
	void DoRevert();

private:
	Actor* m_target;
};