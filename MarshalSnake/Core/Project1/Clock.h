#pragma once
#include <chrono>
#include <ctime>

#include <windows.h>
#include "Singleton.h"


class Clock : public Singleton<Clock>
{
	std::chrono::duration<double> m_elapsed_seconds;
	std::chrono::duration<double> m_deltaTime;
	std::chrono::time_point<std::chrono::system_clock> m_start;
	std::chrono::time_point<std::chrono::system_clock> m_end;

public:
	Clock();
	~Clock();
	static void Update();
	static double GetDelta();
};

