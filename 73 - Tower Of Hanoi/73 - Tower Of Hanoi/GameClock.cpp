#include "GameClock.hpp"

#pragma region Ctor
//Default Ctor: Game clock with 60 ticks per second
GameClock::GameClock()
{
	m_tickTime = 60/1000;
	start();
}

//Game clock with variable tick time
GameClock::GameClock(milli const& tickTime) : m_tickTime(tickTime)
{
	start();
}
#pragma endregion

#pragma region Accessors
milli GameClock::timeSinceLastUpdate() const
{
	return m_accum;
}

milli GameClock::timeSinceStarted() const
{
	return m_curTime - m_startTime;
}

milli GameClock::timeNow() const
{
	return m_curTime;
}

long GameClock::getTickCount() const
{
	return m_tickCount;
}

long GameClock::getTicksPerSecond() const
{
	return m_tickTime * 60;
}
#pragma endregion

#pragma region Clock Functions
//Starts the game clock, called after setup
void GameClock::start()
{
	m_prvTime = m_curTime = 0;//now
}

//Ticks timer
void GameClock::tick()
{
	m_tickCount++;
}

//Updates the time and rolls over if needed
void GameClock::update()
{
	m_accum += m_curTime - m_prvTime;//or += deltaT
	m_prvTime = m_curTime;
	m_curTime = 0;//now

	while (m_accum >= m_tickTime)
	{
		m_accum -= m_tickTime;
		tick();
	}
}
#pragma endregion
