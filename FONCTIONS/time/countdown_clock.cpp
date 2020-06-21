

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "countdown_clock.h"


/*
	Cette version de timer fonctionne avec le delta time provenant du timer principale de la gameloop de mon jeu. Chaque countdown sera d�cr�ment� en fonction de ce deltatime.
*/


bool CDTimer::Tick_Timer()	// Update le temps �coul� � partir de delta time
{
	if (this->isRunning)
		this->timeLeft -= GameLoopClock::Get_Delta_Time();	// R�duit le countdown � partir de DeltaTime

	if (this->timeLeft <= 0)
	{
		this->isRunning = false;	// Stop le timer
		return false;
	}
	else return true;
}

bool CDTimer::Tick_Timer_With_Speed(int speed)	// Update le temps �coul� � partir de delta time
{
	if (this->isRunning)
		this->timeLeft -= (speed * GameLoopClock::Get_Delta_Time());	// R�duit le countdown � partir de DeltaTime

	if (this->timeLeft <= 0)
	{
		this->isRunning = false;	// Stop le timer
		return false;
	}
	else return true;
}


void CDTimer::Start_CountDown()	// Enclanche le temps. Conserve les donn�es reli� au temps �coul�
{
	if (this->isRunning)	// �tait d�j� en cours
		return;
	else
		if (timeLeft <= 0 && cdDuration > 0)	// Le Countdown doit avoir une dur�e pour �tre start�
		{
			timeLeft = cdDuration;	// Reset le cooldown
			this->isRunning = true;	// Et on reprend
		}	
}

/* not used*/
bool CDTimer::Update_Time_Left_DT(float dt)		// R�duit le countdown
{
	if (this->isRunning)
		this->timeLeft -= dt;	// D�cr�mentation du temps

	if (this->timeLeft <= 0)
	{
		this->isRunning = false;	// Stop le timer
		return true;		// timer finit
	}
	else
		return false;	// Timer pas finit
}

// UI
void CDTimer::Dsp_Time_Left(Coord crd, Colors clr)	// Affiche la clock � un certain endroit dans la console
{
	UI_Dsp_String(crd, std::to_string(timeLeft), clr);	 // affiche un int sous forme de string dans la console
}
void CDTimer::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String(crd, timerName, clr, time);		// Affiche le nom
}






