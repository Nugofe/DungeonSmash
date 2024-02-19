#pragma once

#include "../Utils/Utils.h"
#include "../Components/Component.h"
#include "../Actors/Actor.h"
#include "../Managers/TimerManager.h"

#include <vector>

class GameplayManager;

class World
{
public:
	World();
	virtual ~World();

	const std::vector<Actor*>& GetActors() const;
	const std::vector<Component*> GetComponents() const;

	template <typename T>
	std::vector<T*> GetActorsOfClass() const;

	template <typename T>
	std::vector<T*> GetComponentsOfClass() const;

	//void Init(const std::vector<ActorSpawnSpec>& spawnSpecs);
	//Actor* SpawnActor(const ActorSpawnSpec& spawnSpec);

	GameplayManager* GetGameplayManager();
	TimerManager& GetTimerManager();

	template <typename T>
	T* SpawnActor();
	//T* SpawnActor(const Vector2D& position = Vector2D::ZeroVector);

	void Update(float deltaTime);
	void Render();
	void Destroy();

private:
	void OnActorDestroyed(Actor* actor);

public:
	Delegate<> OnStartedRender;
	Delegate<> OnFinishedRender;

protected:
	bool m_haveAllActorsBegunPlay;
	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_actorsDestroyed;

	GameplayManager* m_gameplayManager;
	TimerManager m_timerManager;

	DelegateHandle m_actorDestroyedHandle;
};


template<typename T>
inline std::vector<T*> World::GetActorsOfClass() const
{
	std::vector<T*> result;
	for (Actor* actor : m_actors) {
		// Check if the actor is an instance of the specified class type
		T* t = HelperFunctions::cast<T>(actor);
		if (t != nullptr) {
			result.push_back(t);
		}
	}
	return result;
}

template<typename T>
inline std::vector<T*> World::GetComponentsOfClass() const
{
	std::vector<T*> result;
	for (Actor* actor : m_actors) {
		for (T* t : actor->GetComponentsOfClass<T>()) {
			result.push_back(t);
		}
	}
	return result;
}

template<typename T>
inline T* World::SpawnActor(/*const Vector2D& position*/)
{
	static_assert(std::is_base_of<Actor, T>::value, "T has to be a child of Actor");

	T* a = new T();
	if (a != nullptr)
	{
		a->m_world = this;
		m_actors.push_back(a);
		m_haveAllActorsBegunPlay = false;
	}
	return a;
}