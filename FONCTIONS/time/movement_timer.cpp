

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "movement_timer.h"

SpeedTimer* SpeedTimer::start;
SpeedTimer* SpeedTimer::end;	// La liste de tous les timers

//SpeedTimer* SpeedTimer::allTimers[MAX_TIMERS] = {};
unsigned long long  SpeedTimer::idTotal = 0;				// Le nombre timer total actuel

// Overload l'opérateur égal! =
SpeedTimer& SpeedTimer::operator= (const SpeedTimer& speedTimer)
{
	// Copie toute. Sauf le pointeur nxt et l'id
	this->tickedThisFrame = speedTimer.tickedThisFrame;
	this->movesThisFrame = speedTimer.movesThisFrame;
	this->moving = speedTimer.moving;
	this->cd = speedTimer.cd;
	this->cdDuration = speedTimer.cdDuration;
	this->infinite = speedTimer.infinite;
	this->timeLeft = speedTimer.timeLeft;
	this->totalSteps = speedTimer.totalSteps;
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
	// n'ajoute pas de id dans la liste des timers créés
	id = -1;
}


SpeedTimer::~SpeedTimer()	// Reconnecte les éléments de la liste
{
	static SpeedTimer* it, * prev;
	static bool found;

	if (id != -1)	// si est présent dans la liste on le delete
	{
		it = start;
		prev = NULL;
		found = false;

		while (it)
		{
			if (it->id >= 2160)
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

void SpeedTimer::Override_Ticks_Per_Frame()	// NE JAMAIS UTILISER
{
	resetThisFrame = false;
}

void SpeedTimer::katch_Up()
{
	if (this->timeLeft <= 0)
	{
		movesThisFrame++;
		timeLeft += cdDuration;		// reset le temps pour le prochain mouvement

		if (infinite)	
			katch_Up();	
		else
			if (cd.Count())		// Nombre de moves Max terminé					
				Stop();	// Stop le mouvement		
			else
				katch_Up();
		return;			
	}
}

// Set la durée de base du CountDown. Quand le count down se termine, 1 mouvement peut être fait
void SpeedTimer::Start_Timer(int speed, int numMove, bool inf, int addDuration)		// Speed est en millisecondes
{
	if (!addDuration)
	{
		if (speed == 0)
			timeLeft = cdDuration = (speed * GameLoopClock::Get_Delta_Time());	// Finis instantannément			TEST
		else
			timeLeft = cdDuration = 1000;	// DEFAULT.		1000ms = 1seconde
	}
	else
		timeLeft = cdDuration = 1000 + addDuration;	// J'ai ajouté ceci pour modifier la durée du  timer, mais je crois que ça va exploser. Bref, besoin de tester avec d'utiliser

	if (!inf)
		cd.Set(numMove);				// Nombre de mouvement à faire

	// MÉTHODE #2
	if (tickedThisFrame)	// On ne tick pas deux fois dans dans le même cycle, même si tu reset le timer 1 fois
	{
		tickedThisFrame = false;
		resetThisFrame = true;
	}

	spd = speed;
	infinite = inf;
	moving = true;
}

bool SpeedTimer::Updates_Left()  // Dans un while, fait les updates que ta de besoin selon le le nombre de moves durant une frame
{
	if (movesThisFrame)
		return movesThisFrame--;
	else
		return false;
}	

bool SpeedTimer::OLD_Tick()	// Update le temps écoulé à partir de delta time
{
	if (this->moving)
		this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// Réduit le countdown à partir de DeltaTime
	else
		return false;	// NO MOVE

	katch_Up();

	if (movesThisFrame)
		return true;	// MOVING
	else
		return false;	// NO MOVING
}



 // MÉTHODE NUMÉRO DEUX -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Permet d'utiliser un seul while
// Difficile à débugger, et pas évident ce que ça fait

bool SpeedTimer::Update_Timer()
{
	if (this->timeLeft <= 0)
	{
		timeLeft += cdDuration;		// reset le temps pour le prochain mouvement

		if (infinite)
			return true;	// We move
		else
			if (cd.Count())		// Nombre de moves Max terminé					
				Stop();	// Stop le mouvement		

		return true; // We move
	}

	return false;
}

bool SpeedTimer::Catchup_Needed()				// Katchup le timer si le temps écoulé durant une frame dépassait le countdown
{
	if (Update_Timer())
		return true;
	else
	{
		tickedThisFrame = false; // stahp for good
		return false; // we stahp
	}
}


bool SpeedTimer::Tick()	// Update le temps écoulé à partir de delta time
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
			this->timeLeft -= (spd * GameLoopClock::Get_Delta_Time());	// Réduit le countdown à partir de DeltaTime
			
			if (Update_Timer()) 
			{
				tickedThisFrame = true;
				return true;		// we update
			}
		}
	}

	return false;	// we NO update
}
void SpeedTimer::Stop_All_Timers()	// Stop tout les timers qui sont listés.		// La seule exception à date c'est les timer des affichages de strings
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