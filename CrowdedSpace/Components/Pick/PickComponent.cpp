#include "PickComponent.h"
#include "../../Assets.h"
#include "../../Utils/GameplayStatics.h"
#include "../../Actors/Pawns/Character.h"
#include "../Collision/ColliderComponent.h"

PickComponent::PickComponent()
{
    m_name = "PickComponent";
}

IPickable* PickComponent::Pick()
{
    Character* character = HelperFunctions::cast<Character>(GetOwner());
    if (character == nullptr) return nullptr;

    BoxCollider2D* collider = character->GetCollider();
    std::vector<Collider2D*> overlappingColliders = GameplayStatics::GetInstance().RaycastCollision(collider);
    for (Collider2D* overlapped : overlappingColliders)
    {
        // TODO: if the character is colliding with several pickables,
        // return the item that the character is facing towards instead of the first that collided
        IPickable* pickable = HelperFunctions::cast<IPickable>(overlapped->GetOwner());
        if (pickable != nullptr)
        {
            return pickable;
        }
    }
    return nullptr;
}
