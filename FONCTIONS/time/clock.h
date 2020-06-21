#pragma once

#include <thread>
#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include <string>

using Time = int;


// L'horloge

class GameClock{	
private:

	// Le thread qui va permettre le clock d'op�rer ind�pendamment de main
	std::thread th;

	// Le timer qui servira � incr�menter le temps
	time_t origin, realTime , timePassed;	

	bool running = false;	// Pause l'horloge

	// Le temps updat� par le timer
	time_t time = 0;

	void Reset_Time() { time = 0; running = false; }		// reset le temps
	void Update_Time();		// Update le temps �coul�

public:		// Cette clock est thread�, le temps avance continuellement � tr�s petites intervalles
	void Start_Clock();	// Enclanche le temps. Conserve les donn�es reli� au temps �coul�
	void Pause_Clock();		// Pause le temps
	void Tick();		// Update le temps �coul�

	time_t Get_Time() { return time; }	// Get le temps

	// UI
	int updateDelay = 5;							// Le temps qui s�pare chaque display de l'horloge, exprim� en millisecondes 
	std::string clockName = "Me Clock : ";			// Le nom de l'horloge
	void Set_Clock_Name(std::string name) { clockName = name; }
	void Dsp_Time(Coord crd, Colors clr = WHITE);	// Affiche le temps
	void Dsp_Name(Coord crd, Colors clr = WHITE, time_t time = 0);			// Affiche le nom de la clock
};

// Exemple de thread dans le main, utilisant une m�thode dans un objet
// thread Clockydy(&GameClock::Infinite_Dsp, &LvlClock, crd, WHITE);			
/// FOUND THE SOLUTION : Si ta un default argument(ici Color = White), tu dois quand m�me mettre quekchose en param�tre! Sinon �a ne marche pas!!!


	// POUR PASSER une r�f�rence dans un thread, tu es obliger d'utiliser		std::ref("mavariable")
	//	Exemple fonctionel : std::thread destroyTHREAD(&DestroyChainOfWalls::LameStaticFunction, false, std::ref(fuck), swag);


extern GameClock gameClockTEST;
extern time_t gCrntLvLTime;	 // Temps total �coul� depuis le d�but d'un niveau
