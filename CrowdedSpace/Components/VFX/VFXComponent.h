#pragma once

#include "../Component.h"
#include "../../Utils/Utils.h"

class VFXComponent : public Component
{
public:
	VFXComponent();

	float GetTime() const;
	void SetTime(float time);
	bool IsPlaying() const;

	void Play();
	//void Resume();
	//void Pause();
	void Stop();

	virtual void Update(float deltaTime);
	virtual void Render() override = 0;

private:
	float m_time;
	float m_timeElapsed;
	bool m_isPlaying;
};


class VFXCircle : public VFXComponent
{
public:
	VFXCircle();

	virtual void Render() override;

public:
	Vector2D m_center;
	float m_radius;
};