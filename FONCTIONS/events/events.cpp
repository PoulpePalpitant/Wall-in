



#include "msg_dispatcher.h"
#include "events.h"
#include "global_events/ev_pause_game.h"



// DEF DES STATICS

Event* Event::eventsID[MAX_NUM_EVENTS] = {};	// TOUT LES EVENTS
FixedQueue<int>Event::toUpdate(MAX_NUM_EVENTS);	// Initialisation, une fois, de la queue d'event actifs � updater 
int Event::total;	// Nombre d'events dans le jeu

void Event::Activate()
{
	isActive = true;	
	toUpdate.Register(ID);	// Ajoute l'event � la liste � updater
}
void Event::Deactivate()
{
	isActive = false; 
	toUpdate.Unregister();	//	Retire l'event � la liste de "� updater"
}

// UPDATE TOUT LES EVENT EN COURS !!!!!!!!!!!!!!!!!!!!!!!!
void Event::Update_Active_Events()
{

	for (toUpdate.index = 0; toUpdate.index < toUpdate.Get_Total(); toUpdate.index++)		// Tant qu'on a des events qui n'ont pas �t� updat�
	{
		eventsID[toUpdate.Copy_Element(toUpdate.index)]->Handle_It();		// Ne jamais touch� � toUpdate.index en dehors d'ici :()
	}															// Pour l'instant, un event pourrait en activer un autre, et rallonger cette loop!
}

bool Event::Stop_If_No_More_Steps()
{
	if (curSteps > steps)		// > c'est un fail safe
	{
		Deactivate();			// We deactivate!!!
		return true;
	}
	else
		return false;
}

// Avance l'event d'un stade. Surtout bon pour de l'animation en ce moment. Mais peut aussi �tre utilis� pour cr�er un peu de d�lay entre les choses
void Event::Advance(int speed, int numMove)
{
	if (!delay.Is_Moving()) // Si ya pu aucun moves � faire,
	{
		curSteps++;	// Avance d'un Step 

		if (!Stop_If_No_More_Steps()) // D�sactive l'event quand il � atteint son stade final		
			delay.Start_Timer(speed, numMove);	// Cr�er un nouveau d�lay entre le prochain update
	}
}			

void Event::Start(int speed, int numMove )			// Start l'event!	blob blob
{
	curSteps = 1;	// First Step 
	delay.Start_Timer(speed, numMove);	// Cr�er un nouveau d�lay entre le prochain update
}

void Event::Cancel()									// Termine abruptement l'event 
{
	delay.End_Moving();		// stahpping it
	Deactivate();			// We deactivate!!!
}