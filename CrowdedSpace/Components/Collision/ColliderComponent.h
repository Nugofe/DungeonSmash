#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

class Actor;
class SceneComponent;
class GameplayStatics;

class Collider2D : public Component
{
public:
	Collider2D();

	const bool GetIsActive() const;
	void SetIsActive(bool active);
	const Transform2D& GetOffset() const;
	void SetOffset(const Transform2D& offset);
	const Vector2D GetWorldPosition() const;

	const std::vector<Collider2D*>& GetOverlappingColliders() const;
	
	virtual bool CheckCollision(Collider2D* collider) = 0;

	virtual void Update(float deltaTime) override;
	virtual void EndPlay() override;

private:
	void TryAddOverlap(Collider2D* collider);
	void TryRemoveOverlap(Collider2D* collider);

public:
	Delegate<Collider2D*> OnBeginOverlap;
	Delegate<Collider2D*> OnEndOverlap;

protected:
	bool m_isActive;
	Transform2D m_offset;

private:
	std::vector<Collider2D*> m_overlappingColliders;

	friend class GameplayStatics;
};

class BoxCollider2D : public Collider2D
{
public:
	BoxCollider2D();

	const float GetWidth() const;
	void SetWidth(float width);
	const float GetHeight() const;
	void SetHeight(float height);

	const float GetRealWidth() const;
	const float GetRealHeight() const;
	const float GetRealHalfWidth() const;
	const float GetRealHalfHeight() const;

	virtual bool CheckCollision(Collider2D* collider) override;

	virtual void Render() override;

private:
	float m_width;
	float m_height;
};

class CircleCollider2D : public Collider2D
{
public:
	CircleCollider2D();

	const float GetRadius() const;
	void SetRadius(float radius);
	
	const float GetRealRadius() const;

	virtual bool CheckCollision(Collider2D* collider) override;

private:
	float m_radius;
};