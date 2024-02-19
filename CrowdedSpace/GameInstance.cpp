#include "stdafx.h"
#include "App/app.h"
#include "Utils/GameplayStatics.h"
#include "Worlds/GameWorld.h"
#include "Assets.h"

World* currentWorld;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	Assets::GetInstance(); // assets and gameplayStatics load
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	GameplayStatics::GetInstance().CheckAndSetCurrentWorld();

	static bool firstFrame = true;
	World* currentWorld = GameplayStatics::GetInstance().GetCurrentWorld();
	if (currentWorld == nullptr) return;

	if (firstFrame)
	{
		firstFrame = false;

		currentWorld->Update(0.0f);
		return;
	}
	currentWorld->Update(deltaTime / 1000.0f); // deltatime in seconds
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	World* currentWorld = GameplayStatics::GetInstance().GetCurrentWorld();
	if (currentWorld == nullptr) return;
	
	currentWorld->Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}