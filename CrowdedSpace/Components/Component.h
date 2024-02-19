#pragma once

#include "../Utils/Utils.h"

#include <string>

class Actor;

class Component 
{
public:
	Component();
	~Component();

	const std::string& GetName() const;
	void SetName(const std::string& name);
	Actor* GetOwner() const;
	bool HasBegunPlay() const;
	bool UpdatesWhenPaused() const;
	//void SetOwner(const Actor* actor);

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

protected:
	void SetOwner(Actor* actor);

protected:
	std::string m_name;
	bool m_hasBegunPlay;

	bool m_updateWhenPaused;

public:
	Delegate<> OnBeginPlay;
	Delegate<> OnEndPlay;

private:
	Actor* m_owner;
	inline static Delegate<Component*> OnDestroy;

	friend class Actor;
};