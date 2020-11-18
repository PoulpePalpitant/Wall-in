#pragma once

#include "../UI/txtstyle.h"	// UI
#include "../UI/coord.h"
#include "../math/math_stuff.h"
#include <vector>

const int MAX_TIMERS = 10000;

class SpeedTimer {	// Timer qui me permet de bouger des affaires dans mon jeu
private:
	// Liste li� DE TIMERS
	static SpeedTimer* start, * end;
	SpeedTimer * nxt = NULL;

	static unsigned long long idTotal;				// Le nombre d'id total
	int id;							// l'id de chaque timers

	bool moving = false;			// Pause le countdown
	bool infinite = false;			// Le timer va se reset � l'infini!
	float cdDuration = 0.f;			// Le dur�e maximale du timer en millisecondes.	par d�faut 0 secondes
	
	Countdown cd;					// Le nmbre de moves � faire avant de terminer un mouvement
	int movesThisFrame = 0;	// old way			// Nombre de fois que le timer � reset durant une frame(quand la vitesse est tr�s rapide, il faut tick plusieurs fois)
	int spd = 0 ;					// Vitesse 

	bool tickedThisFrame = false;	// M�THODE #2 // We ticked this frame
	bool resetThisFrame = false;	// M�THODE #2 // Si le timer est reset, et qu'il fut tick pendant une frame, on ne tick pas une autre oifs

	float timeLeft = cdDuration;	// Le temps qui reste avant la fin du CountDown
	unsigned long totalSteps = 0;	// Le nombre de countdown total termin�

	void katch_Up();				// Tick autant qu'il faut pour rattraper le temps
	bool Update_Timer();				// Reset le countdown si il en reste
	bool Catchup_Needed();				// Tick autant qu'il faut pour rattraper le temps
	bool Timer_Was_Reset() { return resetThisFrame; }		// Le countdown fut reset durant cette frame. On tick pas sur la m�me frame qu'un reset � lieu
public:
	static void Stop_All_Timers();	// some hardcore stuff, be careful

	// KEY
	void Override_Ticks_Per_Frame();	// Permet de Tick le timer 1 fois de plus durant 1 frame. Si ta sett� le timer � Inifinite, et que tu utilise �a en boucle, il ya des bonnes chance que tu te softlock. Le timer peut tick selon le count restant, ou � l'infinie 
	bool OLD_Tick();		// Update le temps �coul� � partir de delta time
	bool Updates_Left();	// Dans un while, fait les updates que ta de besoin selon le le nombre de moves durant une frame
	
	void Add_Count(int times) { timeLeft += times * cdDuration; }	// Ajoute du temps
	void Start_Timer(int speed, int numMove = 1, bool inf = false, int duration = 0); //Set la dur�e de base du CountDown.
	void Stop()
	{ 
		timeLeft = 0; 
		moving = false; 
		tickedThisFrame = false; 
		infinite = false;
	}	// Finis abruptement le temps de CountDown

	void Pause() { moving = false; }	// Pause le temps
	void Resume() { moving = true; }	// Pause le temps
	bool Is_On() { return moving;
	}		// Check si le timer est en train de countdown
	int Get_Moves_Left() { return cd.Get_Count(); }	
	float Get_Time_Left() { return timeLeft; }	// Get le temps qui reste avant la fin du CountDown
	int Get_Speed() { return spd; }

	// Doit �tre absolument utilis� avec un while
	bool Tick();	// Update le temps �coul� � partir de delta time

	 // Overloaded assignment operator
	SpeedTimer& operator= (const SpeedTimer& speedTimer);


	// CONSTRUCTORINOS
	SpeedTimer();
	SpeedTimer(bool noId);	//		// n'ajoute pas de id dans lla liste des timers cr��s
	~SpeedTimer();
																
};



//		TO FIX
// ********

// Why? Parce que t'a eu l'id�e de mettre une fonction qui stop tout les timers. Et pour que celle-ci marche, elle doit parcourir la liste de tout
// tout les timers dans un array timers immuable. si tu delete un timer, l'id sera associ� � du garbage dans l'array,
// ce qui va faire crasher le jeu quand il va essayer d'y acc�der. Basically, je suis trop lazy pour g�rer une liste de timer dynamic
// shit










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
