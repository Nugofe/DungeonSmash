#include "Controller.h"
#include "../Pawns/Pawn.h"

// for now, the controller's rootcomponent will be nullptr

Controller::Controller() : m_pawn(nullptr)
{
	m_name = "Controller";
}

const Pawn* Controller::GetPawn() const
{
	return m_pawn;
}

void Controller::PossesPawn(Pawn* pawn)
{
	if (pawn != nullptr)
	{
		m_pawn = pawn;
	}
}

void Controller::UnpossesPawn()
{
	m_pawn = nullptr;
}