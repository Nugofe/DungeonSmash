#include "Item.h"
#include "ItemData.h"
#include "../../Components/Collision/ColliderComponent.h"
#include "../../Components/Sprites/SpriteRendererComponent.h"
#include "../../Components/Scene/SceneComponent.h"
#include "../../Assets.h"

Item::Item() : 
    m_maxGrantedActors(1),
    m_currentGrantedActors(0),
    m_collider(AddComponent<BoxCollider2D>()),
    m_spriteRenderer(AddComponent<SpriteRendererComponent>())
{
    m_name = "Item";
}

ItemData* Item::GrantItem(Actor* actor)
{
    if (m_currentGrantedActors >= m_maxGrantedActors) return nullptr;

    ItemData* itemData = m_CreateFunc();
    ++m_currentGrantedActors;
    if (m_currentGrantedActors == m_maxGrantedActors)
    {
        Destroy();
    }
    itemData->SetOwner(actor);
    return itemData;
}

const int Item::GetMaxGrantedActors() const
{
    return m_maxGrantedActors;
}

void Item::SetMaxGrantedActors(int num)
{
    m_maxGrantedActors = num;
}

BoxCollider2D* Item::GetCollider() const
{
    return m_collider;
}

SpriteRendererComponent* Item::GetSpriteRenderer() const
{
    return m_spriteRenderer;
}

void Item::BeginPlay()
{
    Actor::BeginPlay();

    m_spriteChangedHandle = m_spriteRenderer->OnSpriteChanged.Subscribe(this, &Item::OnSpriteChanged);
    m_rootComponent->SetScale(1.3f);
}

void Item::EndPlay()
{
    m_spriteRenderer->OnSpriteChanged.Unsubscribe(m_spriteChangedHandle);
    m_collider = nullptr;
    m_spriteRenderer = nullptr;

    Actor::EndPlay();
}

void Item::OnSpriteChanged()
{
    m_collider->SetWidth(m_spriteRenderer->GetSpriteAsset()->sprite->GetWidth());
    m_collider->SetHeight(m_spriteRenderer->GetSpriteAsset()->sprite->GetHeight());
}

SimpleSwordItem::SimpleSwordItem()
{
    SetItemData<IDSimpleSword>();
}

void SimpleSwordItem::BeginPlay()
{
    Item::BeginPlay();

    m_spriteRenderer->SetSpriteAsset(Assets::GetInstance().spriteSimpleSword);
}