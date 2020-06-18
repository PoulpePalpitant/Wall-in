#pragma once

#include <thread>
#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include <string>

using Time = int;


// L'horloge

class GameClock{	
private:

	// Le thread qui va permettre le clock d'opérer indépendamment de main
	std::thread th;

	// Le timer qui servira à incrémenter le temps
	time_t origin, realTime , timePassed;	

	bool running = false;	// Pause l'horloge

	// Le temps updaté par le timer
	time_t time = 0;

	void Reset_Time() { time = 0; running = false; }		// reset le temps
	void Update_Time();		// Update le temps écoulé

public:		// Cette clock est threadé, le temps avance continuellement à très petites intervalles
	void Start_Clock();	// Enclanche le temps. Conserve les données relié au temps écoulé
	void Pause_Clock();		// Pause le temps
	void Tick();		// Update le temps écoulé

	time_t Get_Time() { return time; }	// Get le temps

	// UI
	int updateDelay = 5;							// Le temps qui sépare chaque display de l'horloge, exprimé en millisecondes 
	std::string clockName = "Me Clock : ";			// Le nom de l'horloge
	void Set_Clock_Name(std::string name) { clockName = name; }
	void Dsp_Time(Coord crd, Colors clr = WHITE);	// Affiche le temps
	void Dsp_Name(Coord crd, Colors clr = WHITE, time_t time = 0);			// Affiche le nom de la clock
};

// Exemple de thread dans le main, utilisant une méthode dans un objet
// thread Clockydy(&GameClock::Infinite_Dsp, &LvlClock, crd, WHITE);			
/// FOUND THE SOLUTION : Si ta un default argument(ici Color = White), tu dois quand même mettre quekchose en paramètre! Sinon ça ne marche pas!!!



class CDTimer {	// Timer de countdown
private:
	bool isRunning = false;	// Pause le countdown

	float cdDuration = 0.f;	// Le durée maximale du timer en millisecondes.	par défaut 0 secondes
	float timeLeft = cdDuration;	// Le temps qui reste avant la fin du CountDown


public:	
	void Set_Cd_Duration(float duration) { cdDuration = duration; }	// Set la durée de base du CountDown.
	void End_CountDown() { timeLeft = 0; isRunning = false; }	// Finis abruptement le temps de CountDown
	void Restart_CountDown() { timeLeft = cdDuration; }			// Refresh le countdown
	void Tick_Timer(float dt);	// Update le temps écoulé à partir de delta time
	void Start_CountDown();			// Enclanche le temps. Conserve les données relié au temps écoulé
	void Pause_CountDown() { isRunning = false; }	// Pause le temps

	float Get_Time_Left() { return timeLeft; }	// Get le temps qui reste avant la fin du CountDown

	// UI
	std::string timerName = "Me Spell Cooldown : ";			
	void Set_Timer_Name(std::string name) { timerName = name; } // Le nom de l'horloge
	void Dsp_Name(Coord crd, Colors clr = WHITE, time_t time = 0);		// Affiche le nom de la clock
	void Dsp_Time_Left(Coord crd, Colors clr = WHITE);				// Affiche le temps restant

	
};




extern GameClock gameClockTEST;
extern time_t gCrntLvLTime;	 // Temps total écoulé depuis le début d'un niveau
extern long double gLvlTime;	// test de temps du lvl 