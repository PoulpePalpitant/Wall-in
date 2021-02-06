#pragma once

#include <chrono>

//Inspiré des internets
class GameLoopClock {
	static std::chrono::system_clock::time_point startTime;	
	static float timeScale;
	static std::chrono::duration<float> deltaTime;
	static bool active;
public:
	static void Reset_Timer();						
	static float Get_Delta_Time();
	static float Get_Time_Scale();					
	static void Set_Time_Scale(float t = 1.0f);	

	static void Tick();						

	static bool Is_Running();
	static void Stop();
};

