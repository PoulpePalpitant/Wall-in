#pragma once

#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include "../math/math_stuff.h"
#include <string>

class SpeedTimer {	// Timer qui me permet de bouger des affaires dans mon jeu
private:
	bool moving = false;			// Pause le countdown
	bool infinite = false;			// Le timer va se reset à l'infini!
	float cdDuration = 0.f;			// Le durée maximale du timer en millisecondes.	par défaut 0 secondes
	
	Countdown cd;					// Le nmbre de moves à faire avant de terminer un mouvement
	int movesThisFrame = 0;	// old way			// Nombre de fois que le timer à reset durant une frame(quand la vitesse est très rapide, il faut tick plusieurs fois)
	int spd = 0 ;					// Vitesse 

	bool tickedThisFrame = false;	// MÉTHODE #2 // We ticked this frame
	bool resetThisFrame = false;	// MÉTHODE #2 // Si le timer est reset, et qu'il fut tick pendant une frame, on ne tick pas une autre oifs

	float timeLeft = cdDuration;	// Le temps qui reste avant la fin du CountDown
	unsigned long totalSteps = 0;	// Le nombre de countdown total terminé

	void katch_Up();				// Tick autant qu'il faut pour rattraper le temps
	bool Update_Timer();				// Reset le countdown si il en reste
	bool Catchup_Needed();				// Tick autant qu'il faut pour rattraper le temps
	bool Timer_Was_Reset() { return resetThisFrame; }		// Le countdown fut reset durant cette frame. On tick pas sur la même frame qu'un reset à lieu
public:
	// KEY
	bool OLD_Tick();		// Update le temps écoulé à partir de delta time
	bool Updates_Left();	// Dans un while, fait les updates que ta de besoin selon le le nombre de moves durant une frame
	
	void Add_Count(int times) { timeLeft += times * cdDuration; }	// Ajoute du temps
	void Start_Timer(int speed, int numMove = 1, bool inf = false); //Set la durée de base du CountDown.
	void Stop() { timeLeft = 0; moving = false; tickedThisFrame = false; infinite = false; }	// Finis abruptement le temps de CountDown
	void Pause() { moving = false; }	// Pause le temps
	void Resume() { moving = true; }	// Pause le temps
	bool Is_On() { return moving; }		// Check si le timer est en train de countdown
	int Get_Moves_Left() { return cd.Get_Count(); }	
	float Get_Time_Left() { return timeLeft; }	// Get le temps qui reste avant la fin du CountDown
	int Get_Speed() { return spd; }

	// Doit être absolument utilisé avec un while
	bool Tick();	// Update le temps écoulé à partir de delta time
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
