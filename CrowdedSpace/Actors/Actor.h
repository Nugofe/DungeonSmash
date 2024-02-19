#pragma once

#include "../Utils/Utils.h"

#include <string>
#include <vector>

class Component;
class SceneComponent;
class World;

class Actor
{
public:
	Actor();
	~Actor();

	const std::string& GetName() const;
	void SetName(const std::string& name);
	bool HasBegunPlay() const;
	bool UpdatesWhenPaused() const;

	SceneComponent* GetRootComponent() const;

	const std::vector<Component*>& GetComponents() const;

	template <typename T>
	T* GetComponent() const;

	template <typename T>
	const std::vector<T*> GetComponentsOfClass() const;

	World* GetWorld() const;
	Vector2D GetVelocity() const;

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();

protected:
	template <typename T>
	T* AddComponent();

	void AddComponent(Component* comp);

private:
	void NewComponentAdded(Component* comp);
	void OnComponentDestroyed(Component* comp);

protected:
	std::string m_name;
	bool m_hasBegunPlay;
	bool m_haveAllComponentsBegunPlay;

	bool m_updateWhenPaused;

	SceneComponent* m_rootComponent;
	std::vector<Component*> m_components;
	std::vector<Component*> m_componentsDestroyed;

private:
	World* m_world;
	inline static Delegate<Actor*> OnDestroy;
	DelegateHandle m_componentDestroyedHandle;

	friend class World;
};


template<typename T>
inline const std::vector<T*> Actor::GetComponentsOfClass() const
{
	static_assert(std::is_base_of<Component, T>::value, "T has to be a child of Component");

	std::vector<T*> result;
	for (Component* component : m_components) {
		// Check if the component is an instance of the specified class type
		if (HelperFunctions::instanceof<T>(component)) {
			result.push_back(HelperFunctions::cast<T>(component));
		}
	}
	return result;
}


template<typename T>
inline T* Actor::GetComponent() const
{
	static_assert(std::is_base_of<Component, T>::value, "T has to be a child of Component");

	for (Component* comp : m_components)
	{
		T* t = dynamic_cast<T*>(comp);
		if (t != nullptr)
		{
			return t;
		}
	}
	return nullptr;
}

template<typename T>
inline T* Actor::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T has to be a child of Component");

	T* comp = new T();
	if (comp != nullptr)
	{
		NewComponentAdded(comp);
	}
	return comp;
};