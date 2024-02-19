#include "PlayerController.h"
#include "App/app.h"
#include "../../Pawns/Pawn.h"
#include "../../Pawns/PlayerCharacter.h"
#include "../../../HUD/HUD.h"

PlayerController::PlayerController() : 
	m_hud(nullptr),
	m_player(nullptr),
	m_inputControl(nullptr),
	m_inputControlNum(0)
{
	m_name = "PlayerController";
}

void PlayerController::SetInputControl(int num)
{
	m_inputControlNum = num;
	m_inputControl = const_cast<CController*>(&App::GetController(num));
}

int PlayerController::GetInputControlNum() const
{
	return m_inputControlNum;
}

void PlayerController::PossesPawn(Pawn* pawn)
{
	Controller::PossesPawn(pawn);

	PlayerCharacter* player = HelperFunctions::cast<PlayerCharacter>(m_pawn);
	if (player != nullptr)
	{
		m_player = player;
	}
}

HUD* PlayerController::GetHUD() const
{
	return m_hud;
}

void PlayerController::BeginPlay()
{
	Controller::BeginPlay();

	m_hud->BeginPlay();
}

void PlayerController::EndPlay()
{
	m_hud->EndPlay();
	delete m_hud;

	Controller::EndPlay();
}

void PlayerController::Update(float deltaTime)
{
	Controller::Update(deltaTime);

	m_hud->Update(deltaTime);
}