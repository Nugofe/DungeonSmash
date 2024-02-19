#include "SpriteUtils.h"
#include "App/app.h"

SpriteAsset::SpriteAsset(const char* fileName, int rows, int columns)
	: sprite(nullptr), fileName(fileName), rows(rows), columns(columns)
{
	sprite = App::CreateSprite(fileName, columns, rows);
}

SpriteAsset::~SpriteAsset()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

bool AnimationAsset::IsValid() const
{
	return this != nullptr && spriteAsset != nullptr && spriteAsset->sprite != nullptr;
}