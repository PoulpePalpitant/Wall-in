#pragma once

#include <ctime>			// Pour les fonctions de temps
#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include <string>

// L'horloge

class GameClock{	
private:

	// Le timer qui servira � incr�menter le temps
	time_t start, end , timePassed;	

	bool pause = false;	// Pause l'horloge

	// Le temps updat� par le timer
	time_t time;

	void Update_Time();		// Update le temps �coul�
	void Reset_Time() { time = 0; }		// reset le temps

public:
	void Activate_Clock();	// Enclanche le temps. Conserve les donn�es reli� au temps �coul�
	void Pause_Clock();		// Pause le temps
	void Unpause_Clock();	// P�se sur "Play"!
	
	time_t Get_Time() { return time; }	// Get le temps

	// UI
	int updateDelay = 5;							// Le temps qui s�pare chaque display de l'horloge, exprim� en millisecondes 
	std::string clockName = "Me Clock : ";			// Le nom de l'horloge
	void Dsp_Time(Coord crd, Colors clr = WHITE);	// Affiche le temps
	void Dsp_Name(Coord crd, Colors clr = WHITE, time_t time = 0);			// Affiche le nom de la clock
};



extern time_t gCrntLvLTime;	 // Temps total �coul� depuis le d�but d'un niveau
