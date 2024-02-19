#include "AnimationComponent.h"
#include "../SpriteRendererComponent.h"
#include "../SpriteUtils.h"
#include "../../../Actors/Actor.h"
#include "../../App/SimpleSprite.h"
#include "../../../Utils/AnimationEnums.h"

#include <cmath>

AnimationComponent::AnimationComponent() : 
	m_spriteRendererComponent(nullptr), 
	m_animationAsset(nullptr),
	m_currentAnimationId(0), 
	m_timeElapsed(0.0f),
	m_isPlaying(true)
{
	m_name = "AnimationComponent";
}

AnimationAsset* AnimationComponent::GetAnimationAsset() const
{
	return m_animationAsset;
}

void AnimationComponent::SetAnimationAsset(AnimationAsset* animationAsset)
{
	if (!animationAsset->IsValid()) return;
	m_animationAsset = animationAsset;
	if (!m_animationAsset->IsValid()) return;

	for (auto anim : m_animationAsset->animations)
	{
		// first = key, second = value
		if (anim.second != nullptr)
		{
			m_animationAsset->spriteAsset->sprite->CreateAnimation(anim.second->id, anim.second->speed, anim.second->frames);
		}
	}
	m_currentAnimationId = 0;
	m_timeElapsed = 0.0f;
}

void AnimationComponent::SetAnimation(unsigned int animId)
{
	if (!m_animationAsset->IsValid()) return;

	// if the key is present, then change the animation
	if (m_animationAsset->animations.find(animId) != m_animationAsset->animations.end())
	{
		m_currentAnimationId = animId;
	}
}

void AnimationComponent::SetFrame(int frame)
{
	float timeframe = frame * (1 / m_animationAsset->animations[m_currentAnimationId]->speed);
	m_timeElapsed = timeframe;
}

void AnimationComponent::Play()
{
	m_isPlaying = true;
	m_timeElapsed = 0.0f;
}

void AnimationComponent::Resume()
{
	m_isPlaying = true;
}

void AnimationComponent::Pause()
{
	m_isPlaying = false;
}

void AnimationComponent::Stop()
{
	m_isPlaying = false;
	m_timeElapsed = 0.0f;
}

void AnimationComponent::BeginPlay()
{
	Component::BeginPlay();

	m_spriteRendererComponent = GetOwner()->GetComponent<SpriteRendererComponent>();
	if (m_spriteRendererComponent != nullptr)
	{
		m_updateFrameHandle = m_spriteRendererComponent->OnBeginRender.Subscribe(this, &AnimationComponent::UpdateFrame);
	}
}

void AnimationComponent::EndPlay()
{
	m_spriteRendererComponent = nullptr;
	m_animationAsset = nullptr;

	Component::EndPlay();
}

void AnimationComponent::Update(float deltaTime)
{
	if (m_spriteRendererComponent == nullptr) return;

	// increase time elapsed
	if (!m_isPlaying) return;

	m_timeElapsed += deltaTime;
}

void AnimationComponent::UpdateFrame()
{
	if (m_spriteRendererComponent == nullptr) return;

	if (m_spriteRendererComponent->GetSpriteAsset() != m_animationAsset->spriteAsset && m_animationAsset->IsValid())
	{
		m_spriteRendererComponent->SetSpriteAsset(m_animationAsset->spriteAsset);
	}

	m_animationAsset->spriteAsset->sprite->SetAnimation(m_currentAnimationId);
	Animation* animation = m_animationAsset->animations[m_currentAnimationId];

	// frame duration = 1 second / full animation duration
	float frameDuration = 1 / animation->speed;

	// current frame = (elapsed time / frame duration) % number of frames
	// (we need to perform the module if the current frame is higher than the total number of frames)
	int frame = (int)std::floor(m_timeElapsed / frameDuration) % animation->frames.size();
	m_animationAsset->spriteAsset->sprite->SetFrame(animation->frames[frame]);

	// to prevent m_timeElapsed overflow
	float animationDuration = frameDuration * animation->frames.size();
	if (m_timeElapsed >= animationDuration)
	{
		m_timeElapsed -= animationDuration;
	}
}