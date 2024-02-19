#pragma once

#include "../Component.h"

class IPickable 
{
public:
	IPickable() = default;
	virtual ~IPickable() = default;
};

class PickComponent : public Component
{
public:
	PickComponent();
	IPickable* Pick();
};