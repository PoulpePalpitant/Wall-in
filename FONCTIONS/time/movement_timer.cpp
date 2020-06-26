

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "movement_timer.h"

// Set la durée de base du CountDown. Quand le count down se termine, 1 mouvement peut être fait
void MovementTimer::Start_Timer(float speed, int numMove, int interval)		// Speed est en millisecondes
{
	spd = speed;
	intval = interval;	// de base = 1
	timeLeft = cdDuration = interval;
	cd.Set(numMove);				// Nombre de mouvement à faire
	moving = true;
}	

bool MovementTimer::Move_Tick()	// Update le temps écoulé à partir de delta time
{
	if (this->moving)
		this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// Réduit le countdown à partir de DeltaTime
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
