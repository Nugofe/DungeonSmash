#pragma once

#include "Character.h"

class IPickable;
class PickComponent;
class ItemData;

class PlayerCharacter : public Character
{
public:
	PlayerCharacter();

	IPickable* Pick();
	void AddToInventory(IPickable* pickable);
	void RemoveFromInventory(IPickable* pickable);
	void ActivateItem();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;

private:
	PickComponent* m_pickComponent;
	ItemData* m_item;
};