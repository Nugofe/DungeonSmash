#include "Component.h"
#include "../Actors/Actor.h"

Component::Component() :
	m_name("Component"),
	m_hasBegunPlay(false),
	m_updateWhenPaused(false),
	m_owner(nullptr)
{
}

Component::~Component()
{
	Destroy();
}

const std::string& Component::GetName() const
{
	return m_name;
}

void Component::SetName(const std::string& name)
{
	m_name = name;
}

Actor* Component::GetOwner() const
{
	return m_owner;
}

bool Component::HasBegunPlay() const
{
	return m_hasBegunPlay;
}

bool Component::UpdatesWhenPaused() const
{
	return m_updateWhenPaused;
}

void Component::BeginPlay()
{
	if (m_hasBegunPlay) return;
	m_hasBegunPlay = true;
	OnBeginPlay.Broadcast();
}

void Component::EndPlay()
{
	OnEndPlay.Broadcast();
}

void Component::Update(float deltaTime)
{
}

void Component::Render()
{
}

void Component::Destroy()
{
	OnDestroy.Broadcast(this);
}

void Component::SetOwner(Actor* actor)
{
	m_owner = actor;
}