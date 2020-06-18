#pragma once

#include <chrono>

//////////////////////////////////////////////////////////////////////////
// tentative de faire comme dans la vidéo du dude
class TimerOP {
	static TimerOP* pInstance;						// instance du timer
	std::chrono::system_clock::time_point startTime;	// Pour quand tu reset?
	float timeScale;
	std::chrono::duration<float> deltaTime;


public:
	static TimerOP* Set_Instance();
	static void Release();
	void Reset_Timer();				// reset le timer à starttime

	float Get_Delta_Time();
	float Get_Time_Scale();					// Get le timeScale
	void Set_Time_Scale(float t = 1.0f);	// Permet de set le time scale

	void Tick();							// "Tick" le timer forward

	TimerOP();//constructor
	~TimerOP();// Destructor
	//////////////////////////////////////////////////////////////////////////
};



