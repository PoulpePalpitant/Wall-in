#pragma once

#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include "../math/math_stuff.h"
#include <string>

class CDTimer {	// Timer de countdown
private:
	bool isRunning = false;	// Pause le countdown
	bool isFinished = false;
	float cdDuration = 0.f;	// Le dur�e maximale du timer en millisecondes.	par d�faut 0 secondes
	float timeLeft = cdDuration;	// Le temps qui reste avant la fin du CountDown
	
	Countdown cd;			// Le nombre de r�volution � faire avant d'arr�ter de stopper la clock
	unsigned long totalCD = 0;	// Le nombre de countdown total termin�

	void Restart_CountDown();						// R�-Enclanche le timer
public:	
	void Set_Cd_Duration(float duration) { cdDuration = duration; }	// Set la dur�e de base du CountDown.
	void End_CountDown() {	timeLeft = 0; isRunning = false; isFinished	= true;	}	// Finis abruptement le temps de CountDown
	void Start_CountDown(int nbCD = 1);				// Enclanche le temps. Va reset automatiquement si nbCD > 1
	void Pause_CountDown() { isRunning = false; }	// Pause le temps
	float Get_Time_Left() { return timeLeft; }	// Get le temps qui reste avant la fin du CountDown
	bool Is_Running() { return isRunning; }		// Check si le timer est en train de countdown
	bool Is_Finished() { return isFinished; }	// Check si le timer � Finis de faire son action

	/* crap*/
	bool Update_Time_Left_DT(float dt);		// R�duit le countdown
	bool Reduce_Time_Left(float percent);	// R�duit le countdown d'un certain pourcentage

	// KEY
	bool Tick_Timer();		// Update le temps �coul� � partir de delta time. Si �a tombe � z�ro, return false

	// UI
	std::string timerName = "Me Spell Cooldown : ";			
	void Set_Timer_Name(std::string name) { timerName = name; }			// Le nom de l'horloge
	void Dsp_Name(Coord crd, Colors clr = WHITE, time_t time = 0);		// Affiche le nom de la clock
	void Dsp_Time_Left(Coord crd, Colors clr = WHITE);					// Affiche le temps restant
};




/* FORMULE DE BASE POUR UN COUNTDOWN */

// timer.Set_Cd_Duration(speed); 	 // Set la dur�e du countdown une fois, mais ne l'active pas tout de suite
//
//if (updateTimer.Get_Time_Left <= 0)
//{
//	/* do stuff here*/
//	/* do stuff here*/
//	/* do stuff here*/
//	/* do stuff here*/
//	/* do stuff here*/
//	/* do stuff here*/
//	/* do stuff here*/
//
//	updateTimer.Start_CountDown();
//}
//else
//updateTimer.Tick_Timer();
