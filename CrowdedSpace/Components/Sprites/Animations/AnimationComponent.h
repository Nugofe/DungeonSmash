#pragma once

#include "../../Component.h"

class SpriteRendererComponent;
struct AnimationAsset;

class AnimationComponent : public Component
{
public:
	AnimationComponent();

	AnimationAsset* GetAnimationAsset() const;
	void SetAnimationAsset(AnimationAsset* spriteToAnimate);
	void SetAnimation(unsigned int animId);
	void SetFrame(int frame);

	void Play();
	void Resume();
	void Pause();
	void Stop();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Update(float deltaTime) override;

private:
	void UpdateFrame();

private:
	SpriteRendererComponent* m_spriteRendererComponent;
	AnimationAsset* m_animationAsset;
	unsigned int m_currentAnimationId;
	float m_timeElapsed;
	bool m_isPlaying;

	DelegateHandle m_updateFrameHandle;
};