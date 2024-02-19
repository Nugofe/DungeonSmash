#pragma once

#include "Utils\AnimationEnums.h"
#include "Utils\SoundsHelper.h"
#include "Components\Sprites\SpriteUtils.h"
#include "Actors\Items\ItemData.h"

#include <string>

class Assets
{
public:
	static Assets& GetInstance()
	{
		static Assets m_assets;
		return m_assets;
	};

	~Assets()
	{
		delete playerSpriteAsset;
		delete playerAnimationAsset;
		delete enemySpriteAsset;
		delete enemyAnimationAsset;
		delete spriteSimpleSword;
	};

protected:
	Assets() :
		// player
		playerSpriteAsset(new SpriteAsset(".\\Assets\\Sprites\\player_scaled5x.png", 4, 3)),
		player_ANIM_FORWARDS({ FourWayWalkAnimations::ANIM_FORWARDS, 15.0f, { 6,7,8 } }),
		player_ANIM_LEFT({ FourWayWalkAnimations::ANIM_LEFT, 15.0f, { 9,10,11 } }),
		player_ANIM_RIGHT({ FourWayWalkAnimations::ANIM_RIGHT, 15.0f, { 3,4,5 } }),
		player_ANIM_BACKWARDS({ FourWayWalkAnimations::ANIM_BACKWARDS, 15.0f, { 0,1,2 } }),
		playerAnimationAsset(new AnimationAsset()),

		// enemy
		enemySpriteAsset(new SpriteAsset(".\\Assets\\Sprites\\enemy_scaled5x.png", 4, 3)),
		enemy_ANIM_FORWARDS({ FourWayWalkAnimations::ANIM_FORWARDS, 15.0f, { 6,7,8 } }),
		enemy_ANIM_LEFT({ FourWayWalkAnimations::ANIM_LEFT, 15.0f, { 9,10,11 } }),
		enemy_ANIM_RIGHT({ FourWayWalkAnimations::ANIM_RIGHT, 15.0f, { 3,4,5 } }),
		enemy_ANIM_BACKWARDS({ FourWayWalkAnimations::ANIM_BACKWARDS, 15.0f, { 0,1,2 } }),
		enemyAnimationAsset(new AnimationAsset()),

		// items
		spriteSimpleSword(new SpriteAsset(".\\Assets\\Sprites\\scythe.png", 1, 1)),

		// sounds
		enemyDeathSound(".\\Assets\\Sounds\\enemyDeath.wav"),
		simpleSwordSound(".\\Assets\\Sounds\\sword.wav")
	{
		playerAnimationAsset->spriteAsset = playerSpriteAsset;
		playerAnimationAsset->animations = {
			{FourWayWalkAnimations::ANIM_FORWARDS, &player_ANIM_FORWARDS},
			{FourWayWalkAnimations::ANIM_LEFT, &player_ANIM_LEFT},
			{FourWayWalkAnimations::ANIM_RIGHT, &player_ANIM_RIGHT},
			{FourWayWalkAnimations::ANIM_BACKWARDS, &player_ANIM_BACKWARDS}
		};

		enemyAnimationAsset->spriteAsset = enemySpriteAsset;
		enemyAnimationAsset->animations = {
			{FourWayWalkAnimations::ANIM_FORWARDS, &enemy_ANIM_FORWARDS},
			{FourWayWalkAnimations::ANIM_LEFT, &enemy_ANIM_LEFT},
			{FourWayWalkAnimations::ANIM_RIGHT, &enemy_ANIM_RIGHT},
			{FourWayWalkAnimations::ANIM_BACKWARDS, &enemy_ANIM_BACKWARDS}
		};

		SoundsHelper::GetInstance().LoadWaveFile(enemyDeathSound.c_str());
		SoundsHelper::GetInstance().LoadWaveFile(simpleSwordSound.c_str());
	}	

public:
	// player
	SpriteAsset* playerSpriteAsset;
	Animation player_ANIM_FORWARDS;
	Animation player_ANIM_LEFT;
	Animation player_ANIM_RIGHT;
	Animation player_ANIM_BACKWARDS;
	AnimationAsset* playerAnimationAsset;

	// enemy
	SpriteAsset* enemySpriteAsset;
	Animation enemy_ANIM_FORWARDS;
	Animation enemy_ANIM_LEFT;
	Animation enemy_ANIM_RIGHT;
	Animation enemy_ANIM_BACKWARDS;
	AnimationAsset* enemyAnimationAsset;

	// items
	SpriteAsset* spriteSimpleSword;

	// sounds
	std::string enemyDeathSound;
	std::string simpleSwordSound;
};