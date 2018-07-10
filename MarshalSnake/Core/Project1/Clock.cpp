#include "Clock.h"
#include "Logger.h"


Clock::Clock()
{
	Instance()->m_start = std::chrono::system_clock::now();
}


Clock::~Clock()
{
}

void Clock::Update()
{

	if (Instance() == nullptr)
		return;
	Instance()->m_end = std::chrono::system_clock::now();
	Instance()->m_elapsed_seconds = Instance()->m_end - Instance()->m_start;
	Sleep(float(1000.0 / 60) - Instance()->m_elapsed_seconds.count());
	Instance()->m_deltaTime = Instance()->m_start - std::chrono::system_clock::now();
	Instance()->m_start = std::chrono::system_clock::now();
}

double Clock::GetDelta()
{
	if (Instance() != nullptr)
		return Instance()->m_deltaTime.count();
	return 0;
}
