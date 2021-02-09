#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0)	{
}

Timer::~Timer()	{
}

void Timer::Start()	{
	prevTicks = currentTicks = SDL_GetTicks(); //milliseconds since SDL initialized (in window)
}

void Timer::UpdateFrameTicks()	{
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const	{
	return (currentTicks - prevTicks) / MILLI_TO_SEC; //deltatime in Seconds
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const	{
	unsigned int milliSecsPerFrame = MILLI_TO_SEC / fps_;

	if (milliSecsPerFrame == 0) {
		return 0;
	}
	
	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}
	return sleepTime;
}

float Timer::GetCurrentTickMilli() const	{

	return static_cast<float>(currentTicks);
}

float Timer::GetCurrentTickSec() const
{
	return currentTicks / MILLI_TO_SEC;
}
