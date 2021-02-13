
#pragma once 

#include "../queue/queue.h"
#include "../math/math_stuff.h"
#include "../time/movement_timer.h"



/*
POST-MORTEM
	
	Un Event c'est comme la solution passe partout un peu bâtard qui ne fonctionne pas vraiment comme un eventListener conventionel.

	Ce système fut utilisé en combinaison avec le SpeedTimer pour faire une sorte de gestion de "scripts" temporelles dans le code.
	Ceux-ci sont principalement de l'ordre des animations, des séquences de chaînes d'évènements (tutorial, histoire, "cinématique"), et même de "listener" d'event.
	Le plus gros problème avec cette façon réside dans le fait que les event sont bcp trop isolé et intéragissent très mal avec le système de messagerie. À plusieurs endroits dans le code, il fut nécessaire de modifier
	un event ou d'extraire de l'information de celui-ci, ce qui était impossible à faire sans avoir à créer manuellement des méthodes custom pour faire ça.
	Le fait que ces events étaient utilisé de pairs avec des switch statements étaient particulièrement chiant et innéfficace pour ce qui est de la mainetnance...
	Le nombre de step max est aussi complètement useless et source de bug.... et un peu la cause de pouquoi je définis les event comme staic, m'essemble...
*/



// Some rules: Tu peux pas terminer un event avec un advance(0)

const int MAX_NUM_EVENTS = 150;	// Nombre d'events max. Aurait du être un vector


class Event
{
	static Event* eventsID[MAX_NUM_EVENTS];			
	static int total;			

	int ID;							// Retrouve l'event dans l'array
	bool isActive = false;			
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction à invoker pour faire l'event

	int MAX_STEPS;					
	int curSteps = 0;			

	void Define_Handler(void (*toDefine)())
	{
		this->Handler = toDefine;	// Assigne la fonction au pointer
	}

	void Handle_It() { this->Handler(); }		// Fait l'event :)

public:
	static FixedList<int> toUpdate;		// La queue de tout les events actifs À UPDATER
	SpeedTimer delay;					// Permet de créer un délay entre chaque étapes de l'event
	
	bool Is_Active()	{ return isActive;  }
	void Activate();
	void Deactivate();
	
	void Start(int speed, int numMove = 1);			// Start l'event!
	void Advance(int speed, int numMove = 1);		// Avance l'event d'un stade
	void Cancel();									// Termine abruptement l'event 
	bool Stop_If_No_More_Steps();					

	int Get_Current_Step() { return curSteps; }		// Le nombre de stade fait
	void Go_To_Next_Step() { curSteps++; }			
	void Go_To_X_Step(int step) { curSteps = step; }// Sorte de Goto D: it's time for spaghet!
	


	int Get_ID() { return ID; }					

	// THAT BIG MOVE
	static void Update_Active_Events();
	static void Cancel_All();

	//	CONSTRUCTOR
	Event(void (*toDefine)(), int eventSteps = 1) {
		
		MAX_STEPS = eventSteps;	// Le nombre d'étape que contient l'event. 

		eventsID[total] = this;
		ID = total;	
		total++;	

		Define_Handler(toDefine);	
	}
};



/* TEMPLATE POUR UN EVENT : CPP  */ 

/*
static Event Ev_EventObject(EV_Event_Method , 2); 

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

				case 2:
				ev_EventObject.Advance(0);
				break;
			}
		}
}


*/

