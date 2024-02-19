#pragma once

#include "Character.h"
#include "../../Utils/Utils.h"

class SFXComponent;

class EnemyCharacter : public Character
{
public:
	EnemyCharacter();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;

public:
	inline static Delegate<EnemyCharacter*> OnEnemyDied;

private:
	SFXComponent* m_sfxComponent;
};