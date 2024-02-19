#pragma once

#include "../../App/SimpleSprite.h"
#include "App/app.h"

#include <string>
#include <vector>
#include <unordered_map>

struct SpriteAsset;
struct AnimationAsset;
struct Animation;

struct SpriteAsset
{
	CSimpleSprite* sprite;
	const char* fileName;
	int rows = 1;
	int columns = 1;

	SpriteAsset(const char* fileName, int rows = 1, int columns = 1);
	~SpriteAsset();
};

struct AnimationAsset
{
	SpriteAsset* spriteAsset;
	std::unordered_map<unsigned int, Animation*> animations;

	bool IsValid() const;
};

struct Animation
{
	unsigned int id;
	float speed;  // frames per second
	std::vector<int> frames;
};