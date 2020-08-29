

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "timerOP.h"

#include "countdown_clock.h"

// OLDVERSION : pour nouvelle version, checker speedtimer dans movement_timer.h
/*
	Cette version de timer fonctionne avec le delta time provenant du timer principale de la gameloop de mon jeu. Chaque countdown sera décrémenté en fonction de ce deltatime.
*/

int dbugDelay_Lol = 1;

void CDTimer::Set_Debug_Delay_Lol()
{
	if (dbugDelay_Lol == 1)
		dbugDelay_Lol = 20;
	else
		dbugDelay_Lol = 1;

}


bool CDTimer::Tick_Timer()	// Update le temps écoulé à partir de delta time
{
	if (this->isRunning)
		this->timeLeft -= /*lag / framerate(ou MS_PER_UPDATE) * */ GameLoopClock::Get_Delta_Time() / dbugDelay_Lol;	// Réduit le countdown à partir de DeltaTime

	if (this->timeLeft <= 0)
	{
		totalCD++;			// 1 cycle de fait de plus

		if (cd.Count())		// Terminé le nombre de countdown à faire, ferme le timer
		{
			this->isRunning = false;	// Stop le timer
			isFinished = true;
			return false;
		}
		else
			Restart_CountDown();
	}

	return true;	// We still running
}

void CDTimer::Start_CountDown(int nbCD)	// Enclanche le temps. Conserve les données relié au temps écoulé
{
	if (this->isRunning)	// était déjà en cours
		return;
	else
		if (timeLeft <= 0 && cdDuration > 0)	// Le Countdown doit avoir une durée pour être starté
		{
			cd.Set(nbCD);			// Nombre de révolution à faire avant de stopper la clock

			timeLeft = cdDuration;	// Reset le cooldown
			this->isRunning = true;	// Et on reprend
			isFinished = false;		// et on reprend
		}	
}
void CDTimer::Restart_CountDown()						// Ré-Enclanche le timer
{
	timeLeft = cdDuration;	// Reset le cooldown
}

/* not used*/
bool CDTimer::Update_Time_Left_DT(float dt)		// Réduit le countdown
{
	if (this->isRunning)
		this->timeLeft -= dt;	// Décrémentation du temps

	if (this->timeLeft <= 0)
	{
		this->isRunning = false;	// Stop le timer
		return true;		// timer finit
	}
	else
		return false;	// Timer pas finit
}

// UI
void CDTimer::Dsp_Time_Left(Coord crd, Colors clr)	// Affiche la clock à un certain endroit dans la console
{
	UI_Dsp_String(crd, std::to_string(timeLeft), clr);	 // affiche un int sous forme de string dans la console
}
void CDTimer::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String(crd, timerName, clr, time);		// Affiche le nom
}

