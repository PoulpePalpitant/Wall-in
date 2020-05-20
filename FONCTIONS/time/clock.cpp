#include <thread>

#include "clock.h"
#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
extern time_t gCrntLvLTime = 0;	 // Temps total écoulé depuis le début d'un niveau


void GameClock::Activate_Clock()			// Active l'horloge
{
	std::thread t1(this->Get_Time());

	while (!pause)	// Horloge désactivé
	{
		Update_Time();		// Update le temps constamment
	}
	t1.join();
}

void GameClock::Pause_Clock()		// Arrête le temps
{
	this->pause = true;
}

void GameClock::Unpause_Clock()		// Re-démarre le temps
{
	this->pause = false;	// La clock n'est plus sur pause!
	Activate_Clock();	// Redémarre la clock
}

void GameClock::Update_Time()
{
	start = clock();			// Début du timer
	end = clock();				// Fin du timer
	timePassed =  end - start;	// Temps écoulé
	gCrntLvLTime += timePassed;	// Incrémentation du de la clock
}

// UI
void GameClock::Dsp_Time(Coord crd, Colors clr)	// Affiche la clock à un certain endroit dans la console
{
	UI_Dsp_Int(crd, (int)time, clr, updateDelay);	 // affiche un int dans la console
}
// Si tu veux afficher le nom de la clock, fais le manuellement, parce que affiche le nom à chaque fois dans une loop ça prend du jus

void GameClock::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String( crd,clockName, clr, time);		// Affiche le nom
}