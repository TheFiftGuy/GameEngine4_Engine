#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

constexpr float MILLI_TO_SEC = 1000.0f;

class Timer	{
public:
	//these remove the ablity to copy/move the timer class, so that there is only ever 1 unchanging timer
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();//update tick value
	float GetDeltaTime() const; //time inbetween fp(s)
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;
private:
	unsigned int prevTicks;
	unsigned int currentTicks;


};

#endif