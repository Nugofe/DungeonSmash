#pragma once

#include "Utils.h"

#include <string>
#include <unordered_map>

class World;
class PlayerController;
class Component;
class Collider2D;
class BoxCollider2D;
class CircleCollider2D;

class GameplayStatics
{
public:
	static GameplayStatics& GetInstance();
	~GameplayStatics();

	World* GetCurrentWorld() const;

	template<typename T>
	void SetCurrentWorld();

	void CheckAndSetCurrentWorld();

	PlayerController* GetPlayerController(int num);

	std::vector<Collider2D*> RaycastCollision(Collider2D* collider);

	bool CheckBoxToBoxCollision(BoxCollider2D* box1, BoxCollider2D* box2);
	bool CheckCircleToCircleCollision(CircleCollider2D* circle1, CircleCollider2D* circle2);
	bool CheckBoxToCircleCollision(BoxCollider2D* box, CircleCollider2D* circle);

	bool IsPointInCircle(const Vector2D& point, CircleCollider2D* circle);

	static void DrawBox(Vector2D pos, float width, float height, RGBColor color);
	static void DrawCircle(Vector2D center, float radius, int numSegments, RGBColor color);

protected:
	GameplayStatics();

private:
	World* m_currentWorld;
	World* m_worldPendingToLoad;
};


template<typename T>
inline void GameplayStatics::SetCurrentWorld()
{
	static_assert(std::is_base_of<World, T>::value, "T has to be a child of World");

	if (m_worldPendingToLoad != nullptr)
	{
		delete m_worldPendingToLoad;
	}

	m_worldPendingToLoad = new T();
}