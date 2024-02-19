#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

using TimerID = uint64_t;

class TimerManager
{
public:
	void Update(float deltaTime);

	// Adds a new timer
	void SetTimer(float time, std::function<void()> func, bool loops = false);

	template<typename T>
	void SetTimer(float time, T* obj, void(T::* func)(), bool loops = false);

	void ClearTimer(TimerID id);

private:
	struct TimerData
	{
		float m_countdown;
		float m_time;
		std::function<void()> m_func;
		bool m_floops;
	};

	inline static TimerID s_IDCount = 0;
	std::unordered_map<TimerID, TimerData> m_timers;
};

template<typename T>
inline void TimerManager::SetTimer(float time, T* obj, void(T::* func)(), bool loops)
{
	if (time > 0.0f)
	{
		m_timers[++s_IDCount] = { time, time, [obj, func]() { (obj->*func)(); }, loops };
	}
}