
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
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas suppos� �tre r�p�t�
	int steps;						// Le nombre de stade de l'event
	int curSteps = 0;					// Le stade actuelle
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction � invoker pour faire l'event

	void Define_Handler(void (*toDefine)())
	{
		this->Handler = toDefine;	// Assigne la fonction au pointer
	}

	void Handle_It() { this->Handler(); }		// Fait l'event :)

public:
	Countdown cd;							// Pour aider � me faire des events � plusieurs �tapes
	static FixedQueue<int> toUpdate;		// La queue de tout les events actifs � UPDATER

	bool Is_Active()	{ return isActive;  }
	void Activate();
	void Deactivate();

	bool Is_Ignored() { return ignore; }
	void Ignore() { ignore = true; }
	void Remove_Ignore() { ignore = false; }
	
	/* Event � Multi �tapes*/				// TR�S OPTIONNEL
	int Get_Current_Step() { return curSteps; }	// Le nombre de stade fait
	bool Stop_If_No_More_Steps();					// Plus rien � updater, on d�sactive
	void Advance() {curSteps++; }				// Avance l'event d'un stade
	bool Count() { if (cd.Count()) Advance(); }	// D�s que le compteur est finit, on avance au prochain step :)


	int Get_ID() { return ID; }					

	// THAT BIG MOVE
	static void Update_Active_Events();

	//	CONSTRUCTOR
	Event(void (*toDefine)(), int eventSteps = 1) {
		
		steps = eventSteps;	// Le nombre d'�tape que contient l'event. 
		
		eventsID[total] = this;	// Criss l'event dans l'array
		ID = total;	// Associe l'ID
		total++;	// Avance le total 

		Define_Handler(toDefine);	// Ajoute le handler � l'event
	}
};

/* TEMPLATE POUR UN EVENT : HEADER*/
//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/



//#include "../../events/events.h"
//
//extern Event EV_DrawGameTitle;	// D�claration
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