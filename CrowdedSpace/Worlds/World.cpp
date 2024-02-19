#include "World.h"
#include "../Components/Scene/SceneComponent.h"
#include "../Managers/GameplayManager.h"
#include "../Utils/GameplayStatics.h"

//#include <windows.h>

World::World() : 
    m_haveAllActorsBegunPlay(false),
    m_gameplayManager(nullptr),
    m_timerManager(TimerManager())
{
    m_gameplayManager = SpawnActor<GameplayManager>();
    m_actors.clear();

    m_actorDestroyedHandle = Actor::OnDestroy.Subscribe(this, &World::OnActorDestroyed);
}

World::~World()
{
    Destroy();
}

const std::vector<Actor*>& World::GetActors() const
{
    return m_actors;
}

const std::vector<Component*> World::GetComponents() const
{
    std::vector<Component*> components;
    for (Actor* actor : m_actors)
    {
        HelperFunctions::append(components, actor->GetComponents());
    }
    return components;
}

/*void World::Init(const std::vector<ActorSpawnSpec>& spawnSpecs)
{
    for (ActorSpawnSpec sp : spawnSpecs)
    {
        SpawnActor(sp);
    }
}

Actor* World::SpawnActor(const ActorSpawnSpec& spawnSpec)
{
    Actor* a = new Actor();
    a->m_world = this;
    
    if (a != nullptr)
    {
        if (!spawnSpec.actorName.empty())
        {
            a->SetName(spawnSpec.actorName);
        }
        m_actors.push_back(a);
        m_haveAllActorsBegunPlay = false;

        //char text[100];
        //sprintf_s(text, "Spawned actor '%s' in position (%f, %f)\n", spawnSpec.actorName.c_str(), spawnSpec.transform.position.x, spawnSpec.transform.position.y);
        //OutputDebugStringA(text);
    }

    return a;
}*/

GameplayManager* World::GetGameplayManager()
{
    return m_gameplayManager;
}

TimerManager& World::GetTimerManager()
{
    return m_timerManager;
}

void World::Update(float deltaTime)
{
    bool gamePaused = m_gameplayManager->IsGamePaused();
    if (!gamePaused)
    {
        if (!m_gameplayManager->HasBegunPlay())
        {
            m_gameplayManager->BeginPlay();
        }
        m_gameplayManager->Update(deltaTime);
        m_timerManager.Update(deltaTime);
    }

    if (!m_haveAllActorsBegunPlay)
    {
        for (Actor* actor : m_actors)
        {
            if (actor == nullptr) continue;

            if (!gamePaused || (gamePaused && actor->UpdatesWhenPaused()))
            {
                if (!actor->HasBegunPlay())
                {
                    actor->BeginPlay();
                }
                actor->Update(deltaTime);
            }
        }
    }
    else 
    {
        for (Actor* actor : m_actors)
        {
            if (actor == nullptr) continue;

            if (!gamePaused || (gamePaused && actor->UpdatesWhenPaused()))
            {
                actor->Update(deltaTime);
            }
        }
    }

    // delete destroyed world actors
    for (Actor* actor : m_actorsDestroyed)
    {
        if (HelperFunctions::contains(m_actors, actor))
        {
            actor->EndPlay();
            HelperFunctions::remove(m_actors, actor);
            delete actor;
        }
    }
    m_actorsDestroyed.clear();
}

void World::Render()
{
    OnStartedRender.Broadcast();

    m_gameplayManager->Render();
    for (Actor* actor : m_actors)
    {
        if (actor != nullptr)
        {
            actor->Render();
        }
    }

    OnFinishedRender.Broadcast();
}

void World::Destroy()
{
    Actor::OnDestroy.Unsubscribe(m_actorDestroyedHandle);

    if (m_gameplayManager != nullptr)
    {
        m_gameplayManager->EndPlay();
    }

    for (Actor* actor : m_actors)
    {
        if (actor != nullptr)
        {
            actor->EndPlay();
        }
        delete actor;
    }
    m_actors.clear();

    if (m_gameplayManager != nullptr)
    {
        delete m_gameplayManager;
        m_gameplayManager = nullptr;
    }
}

void World::OnActorDestroyed(Actor* actor)
{
    if (HelperFunctions::contains(m_actors, actor) && !HelperFunctions::contains(m_actorsDestroyed, actor))
    {
        m_actorsDestroyed.push_back(actor);
    }
}