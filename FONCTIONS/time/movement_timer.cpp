

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "movement_timer.h"

SpeedTimer* SpeedTimer::start;
SpeedTimer* SpeedTimer::end;	

unsigned long long  SpeedTimer::idTotal = 0;				// Le nombre timer total actuel

// Overload l'opérateur égal! =
SpeedTimer& SpeedTimer::operator= (const SpeedTimer& speedTimer)
{
	// Copie toute. Sauf le pointeur nxt et l'id
	this->tickedThisFrame = speedTimer.tickedThisFrame;
	this->moving = speedTimer.moving;
	this->cd = speedTimer.cd;
	this->cdDuration = speedTimer.cdDuration;
	this->infinite = speedTimer.infinite;
	this->timeLeft = speedTimer.timeLeft;
	this->spd = speedTimer.spd;
	
	return *this;
}

SpeedTimer::SpeedTimer()
{
	if (end)
	{
		end = end->nxt = this;
		end->nxt = NULL;
	}
	else
	{
		start = end = this;
		start->nxt = end->nxt = NULL;
	}

	if (this != end)
		throw "dafuck is this";

	id = ++idTotal;
}

SpeedTimer::SpeedTimer(bool noId)
{
	id = -1;
}


SpeedTimer::~SpeedTimer()	// Reconnecte les éléments de la liste
{
	static SpeedTimer* it, * prev;
	static bool found;

	if (id != -1)	
	{
		it = start;
		prev = NULL;
		found = false;

		while (it)
		{
			if (it->id >= 2160)	// no idea wtf is this
				found = true;

			if (it == this)
			{
				if (it == start && start == end)	// Liste unique
					start = end = NULL;
				else
					if (it == start)				// Reset le start
						start = start->nxt;
					else
						if (it == end)				// Reset la fin
						{
							end = prev;
							end->nxt = NULL;
						}
						else
  							prev->nxt = it->nxt;	// Reconnection au milieu de la liste
				
 				return;
			}

			prev = it;
			it = it->nxt;
		}

		if (!found)
			throw "how?";

	}
}

// Set la durée de base du CountDown. Quand le count down se termine, 1 mouvement peut être fait
void SpeedTimer::Start_Timer(int speed, int numMove, bool inf, int addDuration)		
{
	if (!addDuration)
	{
		if (speed == 0)
			timeLeft = cdDuration = (speed * GameLoopClock::Get_Delta_Time());	// Finis instantannément			
		else
			timeLeft = cdDuration = 1000;	
	}
	else
		timeLeft = cdDuration = 1000 + addDuration;	// NE PAS UTILISER "addDuration" Lol. J'ai ajouté ceci pour modifier la durée du timer, mais je crois que ça fait exploser tout 

	if (!inf)
		cd.Set(numMove);				

	if (tickedThisFrame)	
	{
		tickedThisFrame = false;
		resetThisFrame = true;
	}

	spd = speed;
	infinite = inf;
	moving = true;
}


bool SpeedTimer::Update_Timer()
{
	if (this->timeLeft <= 0)
	{
		timeLeft += cdDuration;		

		if (infinite)
			return true;	
		else
			if (cd.Count())						
				Stop();		

		return true;
	}

	return false;
}

bool SpeedTimer::Catchup_Needed()				// Katchup le timer si le temps écoulé durant une frame dépassait le countdown
{
	if (Update_Timer())
		return true;
	else
	{
		tickedThisFrame = false; 
		return false; 
	}
}


bool SpeedTimer::Tick()	// Update le temps écoulé à partir de delta time
{
	if (this->moving)
	{
		if (Timer_Was_Reset())	// Safety: Pour ne pas update un timer qui s'est fait reset dans une frame
		{
			resetThisFrame = false;
			return false;	
		}

		if(tickedThisFrame)
			return Catchup_Needed();
		else
		{
			this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	
			
			if (Update_Timer()) 
			{
				tickedThisFrame = true;
				return true;		
			}
		}
	}

	return false;	
}
void SpeedTimer::Stop_All_Timers()	
{
	static SpeedTimer* it;
	it = start;
	
	while (it)
	{
		if (it == NULL)
			throw "How is that even possible?";

		it->Stop();
		it = it->nxt;
	}

}