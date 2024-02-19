#include "GameWorld.h"
#include "../Actors/Controllers/PlayerController/GamePlayerController.h"
#include "../Actors/Pawns/PlayerCharacter.h"
#include "../Actors/Items/Item.h"
#include "../Components/Scene/SceneComponent.h"
#include "../Managers/GameManager.h"
#include "../HUD/HUD.h"
#include "../HUD/GameHUD.h"

GameWorld::GameWorld()
{
	// GAME MANAGER
	m_gameplayManager = SpawnActor<GameManager>();
	m_actors.clear();

	// PLAYER
	PlayerCharacter* player = SpawnActor<PlayerCharacter>();
	player->GetRootComponent()->SetPosition(400.0f, 400.0f);

	// PLAYER CONTROLLER
	GamePlayerController* playerController = SpawnActor<GamePlayerController>();
	playerController->SetInputControl(0); // player 0
	playerController->PossesPawn(player);
	playerController->SetHUD<GameHUD>();

	// SWORD ITEM
	SimpleSwordItem* sword = SpawnActor<SimpleSwordItem>();
	sword->GetRootComponent()->SetPosition(600.0f, 400.0f);
}

StartGameWorld::StartGameWorld()
{
	// PLAYER CONTROLLER
	StartGamePlayerController* playerController = SpawnActor<StartGamePlayerController>();
	playerController->SetInputControl(0); // player 0
	playerController->SetHUD<StartGameHUD>();
}