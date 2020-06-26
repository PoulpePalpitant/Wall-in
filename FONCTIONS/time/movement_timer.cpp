

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "movement_timer.h"

// Set la dur�e de base du CountDown. Quand le count down se termine, 1 mouvement peut �tre fait
void MovementTimer::Start_Timer(float speed, int numMove, int interval)		// Speed est en millisecondes
{
	spd = speed;
	intval = interval;	// de base = 1
	timeLeft = cdDuration = interval;
	cd.Set(numMove);				// Nombre de mouvement � faire
	moving = true;
}	

bool MovementTimer::Move_Tick()	// Update le temps �coul� � partir de delta time
{
	if (this->moving)
		this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// R�duit le countdown � partir de DeltaTime
	else
		return false;

	if (this->timeLeft <= 0)
	{
		if (cd.Count())
			End_Moving();	// Stop le mouvement
		else
		{
			timeLeft += cdDuration;		// reset le prochain mouvement
			Stop_If_Too_Fast();
		}
		return true;			// MOVE NOW
	}

	return false;	// NO MOVING
}

void MovementTimer::Stop_If_Too_Fast()
{
	if (timeLeft + cdDuration < 0)
		moving = false;
}
