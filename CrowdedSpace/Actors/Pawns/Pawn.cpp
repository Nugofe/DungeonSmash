#include "Pawn.h"
#include "../Actor.h"
#include "../Controllers/Controller.h"
#include "../../Worlds/World.h"

Pawn::Pawn()
{
	m_name = "Pawn";
}

Controller* Pawn::GetController() const
{
	for (Controller* controller : GetWorld()->GetActorsOfClass<Controller>())
	{
		if (controller->GetPawn() == this)
		{
			return controller;
		}
	}
	return nullptr;
}
