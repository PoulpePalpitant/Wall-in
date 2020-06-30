

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "movement_timer.h"


void MovementTimer::katch_Up()
{
	if (this->timeLeft <= 0)
	{
		movesThisFrame++;
		timeLeft += cdDuration;		// reset le temps pour le prochain mouvement

		if (infinite)	
			katch_Up();	
		else
			if (cd.Count())		// Nombre de moves Max termin�					
				End_Moving();	// Stop le mouvement		
			else
				katch_Up();
		return;			
	}
}

// Set la dur�e de base du CountDown. Quand le count down se termine, 1 mouvement peut �tre fait
void MovementTimer::Start_Timer(int speed, int numMove, bool inf)		// Speed est en millisecondes
{
	if (speed == 0)
		timeLeft = cdDuration = 0;	// Finis instantann�ment
	else
		timeLeft = cdDuration = 1000;	// DEFAULT.		1000ms = 1seconde

	if (!inf)
		cd.Set(numMove);				// Nombre de mouvement � faire

	// M�THODE #2
	if (tickedThisFrame)	// On ne tick pas deux fois dans dans le m�me cycle, m�me si tu reset le timer 1 fois
	{
		tickedThisFrame = false;
		resetThisFrame = true;
	}

	spd = speed;
	infinite = inf;
	moving = true;
}

bool MovementTimer::Updates_Left()  // Dans un while, fait les updates que ta de besoin selon le le nombre de moves durant une frame
{
	if (movesThisFrame)
		return movesThisFrame--;
	else
		return false;
}	

bool MovementTimer::OLD_Tick()	// Update le temps �coul� � partir de delta time
{
	if (this->moving)
		this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// R�duit le countdown � partir de DeltaTime
	else
		return false;	// NO MOVE

	katch_Up();

	if (movesThisFrame)
		return true;	// MOVING
	else
		return false;	// NO MOVING
}



 // M�THODE NUM�RO DEUX -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Permet d'utiliser un seul while
// Difficile � d�bugger, et pas �vident ce que �a fait

bool MovementTimer::Update_Timer()
{
	if (this->timeLeft <= 0)
	{
		timeLeft += cdDuration;		// reset le temps pour le prochain mouvement

		if (infinite)
			return true;	// We move
		else
			if (cd.Count())		// Nombre de moves Max termin�					
				End_Moving();	// Stop le mouvement		

		return true; // We move
	}

	return false;
}

bool MovementTimer::Catchup_Needed()				// Katchup le timer si le temps �coul� durant une frame d�passait le countdown
{
	if (Update_Timer())
		return true;
	else
	{
		tickedThisFrame = false; // stahp for good
		return false; // we stahp
	}
}


bool MovementTimer::Tick()	// Update le temps �coul� � partir de delta time
{
	if (this->moving)
	{
		if (Timer_Was_Reset())	// Safety: Pour ne pas update un timer qui s'est fait reset dans une frame
		{
			resetThisFrame = false;
			return false;	// we no update
		}

		if(tickedThisFrame)
			return Catchup_Needed(); // update maybe?
		else
		{
			this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// R�duit le countdown � partir de DeltaTime
			
			if (Update_Timer()) 
			{
				tickedThisFrame = true;
				return true;		// we update
			}
		}
	}

	return false;	// we NO update
}