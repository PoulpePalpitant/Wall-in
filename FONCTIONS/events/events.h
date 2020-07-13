
#pragma once 

#include "../queue/queue.h"
#include "../math/math_stuff.h"
#include "../time/movement_timer.h"

// CONST
const int MAX_NUM_EVENTS = 80;	// Nombre d'events max


class Event
{
	static Event* eventsID[MAX_NUM_EVENTS];			// TOUT LES EVENTS
	static int total;				// Le nombre d'event total actuel

	int ID;							// Retrouve l'event dans l'array
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas suppos� �tre r�p�t�
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction � invoker pour faire l'event

	int steps;						// Le nombre de stade de l'event
	int curSteps = 0;				// Le stade actuelle

	void Define_Handler(void (*toDefine)())
	{
		this->Handler = toDefine;	// Assigne la fonction au pointer
	}

	void Handle_It() { this->Handler(); }		// Fait l'event :)

public:
	static FixedList<int> toUpdate;		// La queue de tout les events actifs � UPDATER
	SpeedTimer delay;					// Permet de cr�er un d�lay entre chaque �tapes de l'event

	bool Is_Active()	{ return isActive;  }
	void Activate();
	void Deactivate();

	bool Is_Ignored() { return ignore; }
	void Ignore() { ignore = true; }
	void Remove_Ignore() { ignore = false; }
	
	/* Event � Multi �tapes*/				// TR�S OPTIONNEL
	int Get_Current_Step() { return curSteps; }	// Le nombre de stade fait
	bool Stop_If_No_More_Steps();					// Plus rien � updater, on d�sactive
	void Advance(int speed, int numMove = 1);		// Avance l'event d'un stade
	void Start(int speed, int numMove = 1);			// Start l'event!
	void Cancel();									// Termine abruptement l'event 
	


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
//void Ev_Draw_Game_Title();		// Event function



//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/



/* TEMPLATE POUR UN EVENT : CPP  */ //EVENTS AT THE BOTTOM, GET USED TO IT
//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/


/*
static Event Ev_EventObject(EV_Event_Method , 2); // Def //

void EV_Event_Method()
{
	if (!Ev_EventObject.Is_Active())
	{
		// initialisation

		Ev_EventObject.Activate();
		Ev_EventObject.Start(0);
	}
	else
		if (Ev_EventObject.delay.Move_Tick())
		{
			switch (Ev_EventObject.Get_Current_Step())
			{
				case 1:// do event stuff
				Ev_EventObject.Advance(0);
				break;
				case 2:// do event stuff
				Ev_EventObject.Advance(0);
				break;
				// maybe trigger a message here
			}
		}
}



*/

//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/