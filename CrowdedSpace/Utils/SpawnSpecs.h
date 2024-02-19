#pragma once

#include "Utils.h"

#include <string>

// SPAWN SPECS
struct ComponentSpawnSpec
{
	std::string componentName;
	//className;
};

struct ActorSpawnSpec
{
	std::string actorName;
	Transform2D transform = Transform2D::ZeroTransform;
	//className;
	std::vector<ComponentSpawnSpec> components;
};