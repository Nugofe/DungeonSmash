#include "TimerManager.h"

void TimerManager::Update(float deltaTime)
{
	std::vector<TimerID> pendingToKill;

	// update
	for (auto& pair : m_timers)
	{
		TimerData& data = pair.second;
		data.m_countdown -= deltaTime;
		if (data.m_countdown <= 0.0f)
		{
			data.m_func();
			if (!data.m_floops)
			{
				pendingToKill.push_back(pair.first);
			}
			else
			{
				data.m_countdown = data.m_time;
			}
		}
	}

	// clear
	for (TimerID id : pendingToKill)
	{
		ClearTimer(id);
	}
}

void TimerManager::SetTimer(float time, std::function<void()> func, bool loops)
{
	if (time > 0.0f)
	{
		m_timers[++s_IDCount] = { time, time, func, loops };
	}
}

void TimerManager::ClearTimer(TimerID id)
{
	m_timers.erase(id);
}
