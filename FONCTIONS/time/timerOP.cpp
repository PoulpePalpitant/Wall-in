
#include "timerOP.h"

 std::chrono::system_clock::time_point GameLoopClock::startTime = std::chrono::system_clock::now();	
 std::chrono::duration<float> GameLoopClock::deltaTime = std::chrono::duration<float>(0.0f);
 
 float GameLoopClock::timeScale = 1.0f;;
 bool GameLoopClock::active = true;

 bool GameLoopClock::Is_Running()
 {
	 return active;
 }
 void GameLoopClock::Stop()
 {
	 active = false;
 }

void GameLoopClock::Reset_Timer() {
	startTime = std::chrono::system_clock::now();
}

float GameLoopClock::Get_Delta_Time() {
	return deltaTime.count();
}

void GameLoopClock::Set_Time_Scale(float t)
{
	timeScale = t;
}

float GameLoopClock::Get_Time_Scale()
{
	return timeScale;
}

void GameLoopClock::Tick() {
	deltaTime = std::chrono::system_clock::now() - startTime;	
}

