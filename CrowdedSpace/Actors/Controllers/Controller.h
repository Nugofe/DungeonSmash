#pragma once

#include "../Actor.h"

class Pawn;

class Controller : public Actor
{
public:
	Controller();

	const Pawn* GetPawn() const;
	virtual void PossesPawn(Pawn* pawn);
	void UnpossesPawn();

protected:
	Pawn* m_pawn;
};