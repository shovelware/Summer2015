#ifndef GAMECLOCK_H
#define GAMECLOCK_H

//Game clock that ticks appropriately and is not responsible for updates taking effect. It knows when they should and presumes they do, independent of game systems.

//long types are milliseconds
typedef long milli;

class GameClock{
private:
	milli m_tickTime, m_curTime, m_prvTime, m_startTime, m_accum;
	long m_tickCount;

	//Clock functions
	void start();
	void tick();
public:
	GameClock();
	GameClock(milli const& tickTime);

	//Accessors
	milli timeSinceLastUpdate() const;
	milli timeSinceStarted() const;
	milli timeNow() const;
	long getTickCount() const;
	long GameClock::getTicksPerSecond() const;

	//Clock functions
	void update();
};

#endif