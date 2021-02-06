
#pragma once 

#include "../queue/queue.h"
#include "../math/math_stuff.h"
#include "../time/movement_timer.h"



/*
POST-MORTEM
	
	Un Event c'est comme la solution passe partout un peu b�tard qui ne fonctionne pas vraiment comme un eventListener conventionel.

	Ce syst�me fut utilis� en combinaison avec le SpeedTimer pour faire une sorte de gestion de "scripts" temporelles dans le code.
	Ceux-ci sont principalement de l'ordre des animations, des s�quences de cha�nes d'�v�nements (tutorial, histoire, "cin�matique"), et m�me de "listener" d'event.
	Le plus gros probl�me avec cette fa�on r�side dans le fait que les event sont bcp trop isol� et int�ragissent tr�s mal avec le syst�me de messagerie. � plusieurs endroits dans le code, il fut n�cessaire de modifier
	un event ou d'extraire de l'information de celui-ci, ce qui �tait impossible � faire sans avoir � cr�er manuellement des m�thodes custom pour faire �a.
	Le fait que ces events �taient utilis� de pairs avec des switch statements �taient particuli�rement chiant et inn�fficace pour ce qui est de la mainetnance...
	Le nombre de step max est aussi compl�tement useless et source de bug.... et un peu la cause de pouquoi je d�finis les event comme staic, m'essemble...
*/



// Some rules: Tu peux pas terminer un event avec un advance(0)

const int MAX_NUM_EVENTS = 150;	// Nombre d'events max. Aurait du �tre un vector


class Event
{
	static Event* eventsID[MAX_NUM_EVENTS];			
	static int total;			

	int ID;							// Retrouve l'event dans l'array
	bool isActive = false;			
	void (*Handler)();				// POINTEURS DE FONCTION	- Sera la fonction � invoker pour faire l'event

	int MAX_STEPS;					
	int curSteps = 0;			

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
		
		MAX_STEPS = eventSteps;	// Le nombre d'�tape que contient l'event. 

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

