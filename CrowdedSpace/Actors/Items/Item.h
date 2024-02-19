#pragma once

#include "../Actor.h"
#include "../../Components/Pick/PickComponent.h"
#include "../../Components/Effects/Effect.h"
#include "../../Components/Effects/DamageEffect.h"
#include "../../Worlds/World.h"
#include "../../Utils/Utils.h"

class ItemData;
class BoxCollider2D;
class SpriteRendererComponent;

class Item : public Actor, public IPickable
{
public:
	Item();

	ItemData* GrantItem(Actor* actor);
	const int GetMaxGrantedActors() const;
	void SetMaxGrantedActors(int num);

	BoxCollider2D* GetCollider() const;
	SpriteRendererComponent* GetSpriteRenderer() const;

	virtual void BeginPlay() override;
	virtual void EndPlay() override;

protected:
	template<typename ItemDataType, typename ...Args>
	inline void SetItemData(Args&& ... args);

private:
	void OnSpriteChanged();

protected:
	std::function<ItemData* ()> m_CreateFunc;

	int m_maxGrantedActors;
	int m_currentGrantedActors;

	BoxCollider2D* m_collider;
	SpriteRendererComponent* m_spriteRenderer;

	DelegateHandle m_spriteChangedHandle;

	friend class World;
};


// called in each subclass constructor to indicate which type of ItemData will be returned when GrantItem() is called
template<typename ItemDataType, typename ...Args>
inline void Item::SetItemData(Args&& ... args)
{
	m_CreateFunc = [args = std::make_tuple(std::forward<Args>(args)...)]()mutable -> ItemData*
		{
			return std::apply([](auto&& ... args) {
				// use args
				return new ItemDataType(std::forward<Args>(args)...);
				}, 
				std::move(args)
			);
		};
}


class SimpleSwordItem : public Item
{
public:
	SimpleSwordItem();

	virtual void BeginPlay() override;
};