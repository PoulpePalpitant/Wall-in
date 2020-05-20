#include <thread>

#include "clock.h"
#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
extern time_t gCrntLvLTime = 0;	 // Temps total �coul� depuis le d�but d'un niveau


void GameClock::Activate_Clock()			// Active l'horloge
{
	std::thread t1(this->Get_Time());

	while (!pause)	// Horloge d�sactiv�
	{
		Update_Time();		// Update le temps constamment
	}
	t1.join();
}

void GameClock::Pause_Clock()		// Arr�te le temps
{
	this->pause = true;
}

void GameClock::Unpause_Clock()		// Re-d�marre le temps
{
	this->pause = false;	// La clock n'est plus sur pause!
	Activate_Clock();	// Red�marre la clock
}

void GameClock::Update_Time()
{
	start = clock();			// D�but du timer
	end = clock();				// Fin du timer
	timePassed =  end - start;	// Temps �coul�
	gCrntLvLTime += timePassed;	// Incr�mentation du de la clock
}

// UI
void GameClock::Dsp_Time(Coord crd, Colors clr)	// Affiche la clock � un certain endroit dans la console
{
	UI_Dsp_Int(crd, (int)time, clr, updateDelay);	 // affiche un int dans la console
}
// Si tu veux afficher le nom de la clock, fais le manuellement, parce que affiche le nom � chaque fois dans une loop �a prend du jus

void GameClock::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String( crd,clockName, clr, time);		// Affiche le nom
}