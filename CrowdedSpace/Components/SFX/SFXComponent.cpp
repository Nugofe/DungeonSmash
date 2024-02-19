#include "SFXComponent.h"
#include "../../Utils/SoundsHelper.h"

SFXComponent::SFXComponent(std::string filename) : m_fileName(filename), m_volume(-1000), m_isLooping(false)
{
}

void SFXComponent::Play()
{
	DWORD flags = (m_isLooping) ? DSBPLAY_LOOPING : 0;
	SoundsHelper::GetInstance().PlaySound(m_fileName.c_str(), m_volume, flags);
}

void SFXComponent::Stop()
{
	SoundsHelper::GetInstance().StopSound(m_fileName.c_str());
}