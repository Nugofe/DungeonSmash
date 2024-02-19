#pragma once

#include "../Component.h"

#include <string>

class SFXComponent : public Component
{
public:
	SFXComponent(std::string filename);

	void Play();
	void Stop();

public:
	const std::string m_fileName;
	int m_volume;
	bool m_isLooping;
};