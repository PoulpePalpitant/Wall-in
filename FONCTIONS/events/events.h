
#pragma once 

#include "../queue/queue.h"
#include "../math/math_stuff.h"

// CONST
const int MAX_NUM_EVENTS = 80;	// Nombre d'events max


class Event
{
	static Event* eventsID[MAX_NUM_EVENTS];			// TOUT LES EVENTS
	static int total;				// Le nombre d'event total actuel

	int ID;							// Retrouve l'event dans l'array
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas supposé être répété
	int steps;						// Le nombre de stade de l'event
	int curSteps = 0;					// Le stade actuelle
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction à invoker pour faire l'event

	void Define_Handler(void (*toDefine)())
	{
		this->Handler = toDefine;	// Assigne la fonction au pointer
	}

	void Handle_It() { this->Handler(); }		// Fait l'event :)

public:
	Countdown cd;							// Pour aider à me faire des events à plusieurs étapes
	static FixedQueue<int> toUpdate;		// La queue de tout les events actifs À UPDATER

	bool Is_Active()	{ return isActive;  }
	void Activate();
	void Deactivate();

	bool Is_Ignored() { return ignore; }
	void Ignore() { ignore = true; }
	void Remove_Ignore() { ignore = false; }
	
	/* Event à Multi Étapes*/				// TRÈS OPTIONNEL
	int Get_Current_Step() { return curSteps; }	// Le nombre de stade fait
	bool Stop_If_No_More_Steps();					// Plus rien à updater, on désactive
	void Advance() {curSteps++; }				// Avance l'event d'un stade
	bool Count() { if (cd.Count()) Advance(); }	// Dès que le compteur est finit, on avance au prochain step :)


	int Get_ID() { return ID; }					

	// THAT BIG MOVE
	static void Update_Active_Events();

	//	CONSTRUCTOR
	Event(void (*toDefine)(), int eventSteps = 1) {
		
		steps = eventSteps;	// Le nombre d'étape que contient l'event. 
		
		eventsID[total] = this;	// Criss l'event dans l'array
		ID = total;	// Associe l'ID
		total++;	// Avance le total 

		Define_Handler(toDefine);	// Ajoute le handler à l'event
	}
};

/* TEMPLATE POUR UN EVENT : HEADER*/
//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/



//#include "../../events/events.h"
//
//extern Event EV_DrawGameTitle;	// Déclaration
//
//void OBS_Draw_Game_Title();		// Observer d'event



//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/



/* TEMPLATE POUR UN EVENT : CPP  */ //EVENTS AT THE BOTTOM, GET USED TO IT
//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/


/*
static void EV_Ers_Game_Title()
{
 // do event stuff
 EV_EraGameTitle.Deactivate();
}

void OBS_Erase_Game_Title()
{
	EV_EraGameTitle.Activate();
}

Event EV_DrawGameTitle(Ev_Draw_Game_Title); // Def // 
*/

//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/