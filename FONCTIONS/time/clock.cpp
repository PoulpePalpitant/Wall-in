
#include <thread>
#include <chrono>

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "clock.h"


extern time_t gCrntLvLTime = 0;	 // Temps total écoulé depuis le début d'un niveau
extern GameClock gameClockTEST = {};	// TESTETSTESTETSTETSTETSTETSTETSTETSTESTETSTETSSTT


void GameClock::Start_Clock()			// Active l'horloge
{
	if (this->running)	// Already running
		return;
	else
		running = true;
	
	origin = clock();	// setup le point d'origine

	// possibilité
	// std::thread * pClockThread = NULL;		
	// pClockThread = new std::thread(Update_Time , this);
	// et quand tu le join , tu devrais le delete, et le setter à null

	// Le thread de l'horloge
	this->th = std::thread(&GameClock::Update_Time, this); //YES

}

void GameClock::Pause_Clock()		// Arrête le temps
{
	this->running = false;	
	th.join();				// Stop le thread du timer

}

void GameClock::Unpause_Clock()		// Re-démarre le temps
{
	this->running = false;	// La clock n'est plus sur pause!
	Start_Clock();	// Redémarre la clock
}

void GameClock::Update_Time()
{
	while (running)	// Horloge désactivé
	{	
		// tu peux mettre une update speed avec std::this_thread::sleep_for(std::chrono::milliseconds(updateDelay));	// Attend 5 miliseconde entre chaque update!!!
		realTime = clock();			// Fin du timer
		time = realTime - origin;	// Actualisation du temps
	}
}

// UI
void GameClock::Dsp_Time(Coord crd, Colors clr)	// Affiche la clock à un certain endroit dans la console
{
	UI_Dsp_String(crd, std::to_string(time), clr, updateDelay);	 // affiche un int sous forme de string dans la console
	// Si tu veux afficher le nom de la clock, fais le manuellement, parce que affiche le nom à chaque fois dans une loop ça prend du jus
}
void GameClock::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String(crd, clockName, clr, time);		// Affiche le nom

}

// Affiche le temps à l'infinie!!!
void GameClock::Infinite_Dsp(Coord crd, Colors clr)
{
	while (true) {
		this->Dsp_Time(crd, clr);	// Affiche la clock à un certain endroit dans la console
	//NO	MORE	std::this_thread::sleep_for(std::chrono::seconds(1));	// Attend une seconde entre chaque affichage!!!
	}
}


