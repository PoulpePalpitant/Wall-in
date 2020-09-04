
#pragma once 

#include "../queue/queue.h"
#include "../math/math_stuff.h"
#include "../time/movement_timer.h"

// Some rules: Tu peux pas terminer un event avec un advance(0)

// CONST
const int MAX_NUM_EVENTS = 80;	// Nombre d'events max


class Event
{
	static Event* eventsID[MAX_NUM_EVENTS];			// TOUT LES EVENTS
	static int total;				// Le nombre d'event total actuel

	int ID;							// Retrouve l'event dans l'array
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas supposé être répété
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction à invoker pour faire l'event

	int steps;						// Le nombre de stade de l'event
	int curSteps = 0;				// Le stade actuelle

	void Define_Handler(void (*toDefine)())
	{
		this->Handler = toDefine;	// Assigne la fonction au pointer
	}

	void Handle_It() { this->Handler(); }		// Fait l'event :)

public:
	static FixedList<int> toUpdate;		// La queue de tout les events actifs À UPDATER
	SpeedTimer delay;					// Permet de créer un délay entre chaque étapes de l'event
	
	void Safety();	// si, somehow, le timer est à OFF et que l'event est activé , on l'arrête
	bool Is_Active()	{ return isActive;  }
	void Activate();
	void Deactivate();

	bool Is_Ignored() { return ignore; }
	void Ignore() { ignore = true; }
	void Remove_Ignore() { ignore = false; }
	
	/* Event à Multi Étapes*/				// TRÈS OPTIONNEL
	int Get_Current_Step() { return curSteps; }		// Le nombre de stade fait
	void Go_To_Next_Step() { curSteps++; }			// Fait juste avancer d'un step
	void Go_To_X_Step(int step) { curSteps = step; }// Sorte de Goto D:
	bool Stop_If_No_More_Steps();					// Plus rien à updater, on désactive
	void Advance(int speed, int numMove = 1);		// Avance l'event d'un stade
	void Start(int speed, int numMove = 1);			// Start l'event!
	void Cancel();									// Termine abruptement l'event 
	


	int Get_ID() { return ID; }					

	// THAT BIG MOVE
	static void Update_Active_Events();
	static void Cancel_All();	// Gros moyen

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
//void Ev_Draw_Game_Title();		// Event function



//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/



/* TEMPLATE POUR UN EVENT : CPP  */ 
//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/


/*
static Event Ev_EventObject(EV_Event_Method , 2); // Def //

void EV_Event_Method()
{
	if (!ev_EventObject.Is_Active())
	{
		// initialisation

		ev_EventObject.Activate();
		ev_EventObject.Start(0);
	}
	else
		while (ev_EventObject.delay.Tick())
		{
			switch (ev_EventObject.Get_Current_Step())
			{
				case 1:// do event stuff
				ev_EventObject.Advance(0);
				break;
				case 2:// do event stuff
				ev_EventObject.Advance(0);
				break;
				// maybe trigger a message here

			case 3:

				ev_Lvl2_Training_1.Advance(800);
				break;

			case 4:
				ev_Lvl2_Training_1.Advance(340);
				break;

			case 5:
				ev_Lvl2_Training_1.Advance(0);
				break;

			case 6:
				ev_Lvl2_Training_1.Advance(400);
				break;

			case 7:
				ev_Lvl2_Training_1.Advance(800);
				break;

			case 8:
				ev_Lvl2_Training_1.Advance(600);
				break;

			case 9:
				ev_Lvl2_Training_1.Advance(900);
				break;

			case 10:
				ev_Lvl2_Training_1.Advance(350);
				break;

			case 11:
				ev_Lvl2_Training_1.Advance(0);
			
			
			}
		}
}



*/

//////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*///////*/*/*/*/