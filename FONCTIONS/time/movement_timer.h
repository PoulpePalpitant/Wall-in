#pragma once

#include "../UI/txtstyle.h"	
#include "../UI/coord.h"
#include "../math/math_stuff.h"
#include <vector>

/*
POST-MORTEM
	Le speed-timer c'est le truc que j'ai abusé un peu par faute de connaissance de gestion de framerate. 
	Au lieu de mettre "delta time" en paramètre de méthode "Update()" principlae, je l'ai sacré des ce timer.
	Tout ce qui touche à une certaines temporalité, passe par ici. Et ça l'a pt contribué à créer du lag à certains moment dans le jeu... i don't know
*/


const int MAX_TIMERS = 10000;

class SpeedTimer {	
private:
	static SpeedTimer* start, * end;
	SpeedTimer * nxt = NULL;

	static unsigned long long idTotal;				
	int id;							

	bool moving = false;			
	bool infinite = false;			
	float cdDuration = 0.f;			
	
	Countdown cd;					// Le nmbre de moves à faire avant de terminer un mouvement
	int spd = 0 ;					 

	bool tickedThisFrame = false;	
	bool resetThisFrame = false;	// Si le timer est reset, et qu'il fut tick pendant une frame, on ne tick pas une autre fois
	float timeLeft = cdDuration;	

	bool Update_Timer();				
	bool Catchup_Needed();			// Tick autant qu'il faut pour rattraper le temps
	bool Timer_Was_Reset() { return resetThisFrame; }		
public:
	static void Stop_All_Timers();	// some hardcore stuff, be careful

	void Add_Count(int times) { timeLeft += times * cdDuration; }	
	void Start_Timer(int speed, int numMove = 1, bool inf = false, int duration = 0);
	void Stop()
	{ 
		timeLeft = 0; 
		moving = false; 
		tickedThisFrame = false; 
		infinite = false;
	}	

	void Pause() { moving = false; }	
	void Resume() { moving = true; }	
	bool Is_On() { return moving;
	}		
	int Get_Moves_Left() { return cd.Get_Count(); }	
	float Get_Time_Left() { return timeLeft; }	
	int Get_Speed() { return spd; }

	// Doit être absolument utilisé avec un while
	bool Tick();	

	 // Overloaded assignment operator
	SpeedTimer& operator= (const SpeedTimer& speedTimer);


	// CONSTRUCTORINOS
	SpeedTimer();
	SpeedTimer(bool noId);	
	~SpeedTimer();
																
};

