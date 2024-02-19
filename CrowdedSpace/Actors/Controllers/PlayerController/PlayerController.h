#pragma once

#include "../Controller.h"

class CController;
class HUD;
class PlayerCharacter;
class Pawn;
class BoxCollider2D;
class Item;

class PlayerController : public Controller
{
public:
	PlayerController();

	void SetInputControl(int num);
	int GetInputControlNum() const;
	virtual void PossesPawn(Pawn* pawn) override;
	HUD* GetHUD() const;

	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Update(float deltaTime) override;

	template<typename T>
	void SetHUD();

protected:
	HUD* m_hud;
	PlayerCharacter* m_player;
	CController* m_inputControl;
	int m_inputControlNum;
};


template<typename T>
inline void PlayerController::SetHUD()
{
	static_assert(std::is_base_of<HUD, T>::value, "T has to be a child of HUD");
	T* a = new T();
	a->m_ownerPlayerController = this;

	if (GetWorld() != nullptr)
	{
		a->m_gameplayManager = GetWorld()->GetGameplayManager();
	}

	if (a != nullptr)
	{
		m_hud = a;
	}
}