#include "Actor.h"
#include "../Worlds/World.h"
#include "../Components/Component.h"
#include "../Components/Scene/SceneComponent.h"
#include "../Components/Movement/MovementComponent.h"
#include "../Managers/GameplayManager.h"

Actor::Actor() :
    m_name("Actor"),
    m_hasBegunPlay(false),
    m_haveAllComponentsBegunPlay(false),
    m_updateWhenPaused(false),
    m_rootComponent(nullptr),
    m_world(nullptr)
{
    m_rootComponent = AddComponent<SceneComponent>();

    m_componentDestroyedHandle = Component::OnDestroy.Subscribe(this, &Actor::OnComponentDestroyed);
}

Actor::~Actor()
{
    Destroy();
}

const std::string& Actor::GetName() const
{
    return m_name;
}

void Actor::SetName(const std::string& name)
{
    m_name = name;
}

bool Actor::HasBegunPlay() const
{
    return m_hasBegunPlay;
}

bool Actor::UpdatesWhenPaused() const
{
    return m_updateWhenPaused;
}

SceneComponent* Actor::GetRootComponent() const
{
    return m_rootComponent;
}

const std::vector<Component*>& Actor::GetComponents() const
{
    return m_components;
}

/*void Actor::RemoveComponent(const Component& component)
{
    auto it = std::find(components.begin(), components.end(), &component);
    if (it != components.end()) {
        components.erase(it);
    }
}*/

World* Actor::GetWorld() const
{
    return m_world;
}

Vector2D Actor::GetVelocity() const
{
    MovementComponent* movComp = GetComponent<MovementComponent>();
    if (movComp != nullptr)
    {
        return movComp->GetVelocity();
    }
    else
    {
        return Vector2D::ZeroVector;
    }
}

void Actor::BeginPlay()
{
    if (!m_haveAllComponentsBegunPlay)
    {
        for (Component* component : m_components)
        {
            if (component == nullptr) continue;

            if (!component->HasBegunPlay())
            {
                component->BeginPlay();
            }
        }
    }
    m_haveAllComponentsBegunPlay = true;
    m_hasBegunPlay = true;
}

void Actor::EndPlay()
{
    Component::OnDestroy.Unsubscribe(m_componentDestroyedHandle);

    for (Component* component : m_components)
    {
        if (component != nullptr)
        {
            component->EndPlay();
        }
        delete component;
    }
    m_components.clear();
    m_rootComponent = nullptr;
    m_world = nullptr;
}

void Actor::Update(float deltaTime)
{
    bool gamePaused = m_world->GetGameplayManager()->IsGamePaused();

    if (!m_haveAllComponentsBegunPlay)
    {
        for (Component* component : m_components)
        {
            if (component == nullptr) continue;

            if (!gamePaused || (gamePaused && component->UpdatesWhenPaused()))
            {
                if (!component->HasBegunPlay())
                {
                    component->BeginPlay();
                }
                component->Update(deltaTime);
            }         
        }
    }
    else
    {
        for (Component* component : m_components)
        {
            if (component == nullptr) return;

            if (!gamePaused || (gamePaused && component->m_updateWhenPaused))
            {
                component->Update(deltaTime);
            }
        }
    }

    // delete destroyed actor components
    for (Component* component : m_componentsDestroyed)
    {
        if (HelperFunctions::contains(m_components, component))
        {
            component->EndPlay();
            HelperFunctions::remove(m_components, component);
            delete component;
        }
    }
    m_componentsDestroyed.clear();
}

void Actor::Render()
{
    for (Component* component : m_components)
    {
        if (component != nullptr)
        {
            component->Render();
        }
    }
}

void Actor::Destroy()
{
    OnDestroy.Broadcast(this);
}

void Actor::AddComponent(Component* comp)
{
    if (comp == nullptr) return;

    for (Component* component : m_components)
    {
        if (component == comp) return;
    }
    NewComponentAdded(comp);
}

void Actor::NewComponentAdded(Component* comp)
{
    comp->m_owner = this;
    m_components.push_back(comp);
    m_haveAllComponentsBegunPlay = false;
}

void Actor::OnComponentDestroyed(Component* comp)
{
    if (HelperFunctions::contains(m_components, comp) && !HelperFunctions::contains(m_componentsDestroyed, comp))
    {
        m_componentsDestroyed.push_back(comp);
    }
}