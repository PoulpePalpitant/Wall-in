#pragma once

#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include "../math/math_stuff.h"
#include <string>

class MovementTimer {	// Timer qui me permet de bouger des affaires dans mon jeu
private:
	bool moving = false;			// Pause le countdown
	float cdDuration = 0.f;			// Le durée maximale du timer en millisecondes.	par défaut 0 secondes
	
	Countdown cd;						// Le nombre de mouvement à faire avant de terminer un mouvement
	float spd = 0 ;						// Vitesse 
	Distance intval = 1;				// Distance parcouru à chaque fois

	float timeLeft = cdDuration;	// Le temps qui reste avant la fin du CountDown

	unsigned long totalCD = 0;	// Le nombre de countdown total terminé

	void Stop_If_Too_Fast();
public:
	// KEY
	bool Move_Tick();	// Update le temps écoulé à partir de delta time
	
	void Start_Timer(float speed, int numMove = 1, int interval = 1); //Set la durée de base du CountDown.
	void End_Moving() { timeLeft = 0; moving = false; }	// Finis abruptement le temps de CountDown
	void Pause_Move() { moving = false; }	// Pause le temps
	float Get_Time_Left() { return timeLeft; }	// Get le temps qui reste avant la fin du CountDown
	int Get_Moves_Left() { return cd.Get_Count(); }	
	bool Is_Moving() { return moving; }		// Check si le timer est en train de countdown

	Distance Get_Move_Distance() { return intval; }
};
















/* FORMULE DE BASE POUR UN COUNTDOWN */

// timer.Set_Cd_Duration(speed); 	 // Set la durée du countdown une fois, mais ne l'active pas tout de suite
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
