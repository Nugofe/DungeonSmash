#include "GameplayStatics.h"
#include "../Worlds/World.h"
#include "../Worlds/GameWorld.h"
#include "../Actors/Actor.h"
#include "../Actors/Controllers/PlayerController/PlayerController.h"
#include "../Components/Scene/SceneComponent.h"
#include "../Components/Collision/ColliderComponent.h"
#include "AppSettings.h"
#include "app.h"

GameplayStatics& GameplayStatics::GetInstance()
{
	static GameplayStatics m_gameplayStatics;
	return m_gameplayStatics;
}

GameplayStatics::GameplayStatics() : m_currentWorld(nullptr), m_worldPendingToLoad(nullptr)
{
	SetCurrentWorld<StartGameWorld>();
}

GameplayStatics::~GameplayStatics()
{
	delete m_currentWorld;
}

World* GameplayStatics::GetCurrentWorld() const
{
	return m_currentWorld;
}

void GameplayStatics::CheckAndSetCurrentWorld()
{
	if (m_worldPendingToLoad != nullptr)
	{
		delete m_currentWorld;
		m_currentWorld = m_worldPendingToLoad;
		m_worldPendingToLoad = nullptr;
	}
}

PlayerController* GameplayStatics::GetPlayerController(int num)
{
	for (PlayerController* playerController : m_currentWorld->GetActorsOfClass<PlayerController>())
	{
		if (playerController->GetInputControlNum() == num)
		{
			return playerController;
		}
	}
	return nullptr;
}

std::vector<Collider2D*> GameplayStatics::RaycastCollision(Collider2D* collider)
{
	if (collider == nullptr || !collider->GetIsActive()) return {};

	SceneComponent* ownerSC = collider->GetOwner()->GetRootComponent();
	if (ownerSC == nullptr) return {};

	// check and manage overlap with other collider
	for (Collider2D* other : GameplayStatics::GetInstance().GetCurrentWorld()->GetComponentsOfClass<Collider2D>())
	{
		if (other == nullptr || other == collider) continue;

		if (!other->GetIsActive())
		{
			collider->TryRemoveOverlap(other);
			other->TryRemoveOverlap(collider);
			continue;
		}

		if (collider->CheckCollision(other))
		{
			collider->TryAddOverlap(other);
			other->TryAddOverlap(collider);
		}
		else
		{
			collider->TryRemoveOverlap(other);
			other->TryRemoveOverlap(collider);
		}
	}

	return collider->m_overlappingColliders;
}

bool GameplayStatics::CheckBoxToBoxCollision(BoxCollider2D* box1, BoxCollider2D* box2)
{
	Vector2D posBox1 = box1->GetWorldPosition();
	Vector2D posBox2 = box2->GetWorldPosition();

	float widthBox1 = box1->GetRealHalfWidth();
	float widthBox2 = box2->GetRealHalfWidth();
	float heightBox1 = box1->GetRealHalfHeight();
	float heightBox2 = box2->GetRealHalfHeight();

	return (posBox1.x - widthBox1 < posBox2.x + widthBox2 && posBox1.x + widthBox1 > posBox2.x - widthBox2 &&
		posBox1.y - heightBox1 < posBox2.y + heightBox2 && posBox1.y + heightBox1 > posBox2.y - heightBox2);
}

bool GameplayStatics::CheckCircleToCircleCollision(CircleCollider2D* circle1, CircleCollider2D* circle2)
{
	// calculate the distance between the two circle’s centers
	Vector2D posCir1 = circle1->GetWorldPosition();
	Vector2D posCir2 = circle2->GetWorldPosition();

	float radius1 = circle1->GetRealRadius();
	float radius2 = circle2->GetRealRadius();

	float distance = Vector2D::Distance(posCir1, posCir2);

	return distance < (radius1 + radius2) * (radius1 + radius2);
}

bool GameplayStatics::CheckBoxToCircleCollision(BoxCollider2D* box, CircleCollider2D* circle)
{
	// closest point on collision box
	Vector2D closestPointToBox;

	Vector2D posCir = circle->GetWorldPosition(); // a
	Vector2D posBox = box->GetWorldPosition(); // b

	// find closest x offset
	if (posCir.x < posBox.x)
	{
		closestPointToBox.x = posBox.x;
	}
	else if (posCir.x > posBox.x + box->GetRealWidth())
	{
		closestPointToBox.x = posBox.x + box->GetRealWidth();
	}
	else
	{
		closestPointToBox.x = posCir.x;
	}

	// find closest y offset
	if (posCir.y < posBox.y)
	{
		closestPointToBox.y = posBox.y;
	}
	else if (posCir.y > posBox.y + box->GetRealHeight())
	{
		closestPointToBox.y = posBox.y + box->GetRealHeight();
	}
	else
	{
		closestPointToBox.y = posCir.y;
	}

	// if the closest point is inside the circle, they have collided
	return IsPointInCircle(closestPointToBox, circle);
}

bool GameplayStatics::IsPointInCircle(const Vector2D& point, CircleCollider2D* circle)
{
	Vector2D posCircle = circle->GetWorldPosition();
	float xSquare = (point.x - posCircle.x) * (point.x - posCircle.x);
	float ySquare = (point.y - posCircle.y) * (point.y - posCircle.y);
	float radiusSquare = circle->GetRealRadius() * circle->GetRealRadius();

	return (xSquare + ySquare) < radiusSquare;
}

void GameplayStatics::DrawBox(Vector2D pos, float width, float height, RGBColor color)
{
	App::DrawLine(pos.x - width/2, pos.y + height / 2, pos.x + width / 2, pos.y + height / 2, color.R, color.G, color.B);
	App::DrawLine(pos.x - width/2, pos.y - height / 2, pos.x + width / 2, pos.y - height / 2, color.R, color.G, color.B);

	App::DrawLine(pos.x - width / 2, pos.y + height / 2, pos.x - width / 2, pos.y - height / 2, color.R, color.G, color.B);
	App::DrawLine(pos.x + width / 2, pos.y + height / 2, pos.x + width / 2, pos.y - height / 2, color.R, color.G, color.B);
}

void GameplayStatics::DrawCircle(Vector2D center, float radius, int numSegments, RGBColor color)
{
	float circumference = radius * 2 * PI;
	float alpha = (2 * PI) / numSegments; // in radians

	for (int i = 0; i < numSegments; ++i)
	{
		float x0, y0, x1, y1;
		x0 = radius * cos(alpha * i) + center.x;
		y0 = radius * sin(alpha * i) + center.y;
		x1 = radius * cos(alpha * ((i + 1) % numSegments)) + center.x;
		y1 = radius * sin(alpha * ((i + 1) % numSegments)) + center.y;

		App::DrawLine(x0, y0, x1, y1, color.R, color.G, color.B);
	}
}

bool IsPointInCircle(float xa, float ya, float xc, float yc, float r)
{
	return ((xa - xc) * (xa - xc) + (ya - yc) * (ya - yc)) < r * r;
}