#include "GamePlayerController.h"
#include "../../Pawns/PlayerCharacter.h"
#include "../../App/app.h"
#include "../../Items/Item.h"
#include "../../../Managers/GameManager.h"
#include "../../../Utils/GameplayStatics.h"
#include "../../../Worlds/GameWorld.h"

GamePlayerController::GamePlayerController()
{
	m_updateWhenPaused = true;
}

void GamePlayerController::CheckResetGame()
{
	// when game is over, allow to press button to start again
	GameManager* gameManager = HelperFunctions::cast<GameManager>(GetWorld()->GetGameplayManager());
	if (gameManager != nullptr && gameManager->IsGameOver())
	{
		if (m_inputControl->CheckButton(XINPUT_GAMEPAD_B) || App::IsKeyPressed('P'))
		{
			GameplayStatics::GetInstance().SetCurrentWorld<GameWorld>();
		}
	}
}

void GamePlayerController::Update(float deltaTime)
{
	PlayerController::Update(deltaTime);

	// when game is running, perform normal game actions
	// MOVEMENT MECHANICH: calculate input vector
	if (m_inputControl == nullptr || m_player == nullptr) return;

	if (m_inputControl->GetLeftThumbStickX() > 0.5f)
	{
		m_player->MoveRight();
	}
	if (m_inputControl->GetLeftThumbStickX() < -0.5f)
	{
		m_player->MoveLeft();
	}
	if (m_inputControl->GetLeftThumbStickY() > 0.5f)
	{
		m_player->MoveUp();
	}
	if (m_inputControl->GetLeftThumbStickY() < -0.5f)
	{
		m_player->MoveDown();
	}

	// ITEM MECHANICS: pick or activate item
	if (m_inputControl->CheckButton(XINPUT_GAMEPAD_B) || App::IsKeyPressed('P'))
	{
		IPickable* pickable = m_player->Pick(); // try pick
		if (pickable != nullptr)
		{
			m_player->AddToInventory(pickable);
		}
		else
		{
			m_player->ActivateItem();
		}
	}	
}

StartGamePlayerController::StartGamePlayerController()
{
}

void StartGamePlayerController::Update(float deltaTime)
{
	PlayerController::Update(deltaTime);

	if (m_inputControl == nullptr) return;

	// OPEN GAME WORLD
	if (m_inputControl->CheckButton(XINPUT_GAMEPAD_B) || App::IsKeyPressed('P'))
	{
		GameplayStatics::GetInstance().SetCurrentWorld<GameWorld>();
	}
}
