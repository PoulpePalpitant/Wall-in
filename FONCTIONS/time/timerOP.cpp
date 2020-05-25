
#include "timerOP.h"


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// clock du dude sur les internet


TimerOP* TimerOP::pInstance = NULL;	// pointe sur null

// Créer un nouveau timer, au lieu d'un objet timer, il ne peut y avoir qu'une seule instance étant donné que c'est static
TimerOP* TimerOP::Set_Instance()
{
	if (pInstance == NULL)
		pInstance = new TimerOP();

	return pInstance;

}

// Sert à delete le Timer pointé par instance
void TimerOP::Release()
{

	delete pInstance;
	pInstance = NULL;
}

// Constructor
TimerOP::TimerOP() {
	Reset_Timer();
	timeScale = 1.0f;
	deltaTime = std::chrono::duration<float>(0.0f);	// Initialisation de précaution
}
//Destructor
TimerOP::~TimerOP()
{}

// reset Start time
void TimerOP::Reset_Timer() {
	startTime = std::chrono::system_clock::now();

}

// Va chercher delta time c'est la durée qui sépare chaque tick de la clock je crois
float TimerOP::Get_Delta_Time() {
	return deltaTime.count();
}

// set le timeScale
void TimerOP::Set_Time_Scale(float t  /* = 1.of*/)
{
	timeScale = t;
}

// Get timescale
float TimerOP::Get_Time_Scale()
{
	return timeScale;
}

// ASSIGNE LE DELTA TIME
void TimerOP::Tick() {
	deltaTime = std::chrono::system_clock::now() - startTime;	// La différence entre le temps now et le start time
}