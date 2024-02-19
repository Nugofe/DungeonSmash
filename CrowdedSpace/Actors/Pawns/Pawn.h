#pragma once

#include "../Actor.h"

class Controller;
class SpriteRendererComponent;

class Pawn : public Actor
{
public:
	Pawn();

	Controller* GetController() const;
};