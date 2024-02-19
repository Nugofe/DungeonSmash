#include "VFXComponent.h"
#include "../../Utils/GameplayStatics.h"

VFXComponent::VFXComponent() : m_time(1.0f), m_timeElapsed(0.0f), m_isPlaying(false)
{
}

float VFXComponent::GetTime() const
{
	return m_time;
}

void VFXComponent::SetTime(float time)
{
	if (time >= 0.0)
	{
		m_time = time;
		m_timeElapsed = 0.0f;
	}
}

bool VFXComponent::IsPlaying() const
{
	return m_isPlaying;
}

void VFXComponent::Play()
{
	m_isPlaying = true;
	m_timeElapsed = 0.0f;
}

void VFXComponent::Stop()
{
	m_isPlaying = false;
}

void VFXComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	if (!m_isPlaying) return;

	m_timeElapsed += deltaTime;
	if (m_timeElapsed >= m_time)
	{
		Stop();
	}
}

VFXCircle::VFXCircle() : m_center(Vector2D()), m_radius(100.0f)
{
}

void VFXCircle::Render()
{
	if (!IsPlaying()) return;

	GameplayStatics::DrawCircle(m_center, m_radius, 32, RGBColor::White);
}