



#include "msg_dispatcher.h"
#include "events.h"



// DEF DES STATICS

Event* Event::eventsID[MAX_NUM_EVENTS] = {};	// TOUT LES EVENTS
FixedQueue<int>Event::toUpdate(MAX_NUM_EVENTS);	// Initialisation, une fois, de la queue d'event actifs à updater 
int Event::total;	// Nombre d'events dans le jeu

void Event::Activate()
{
	isActive = true;	
	toUpdate.Register(ID);	// Ajoute l'event à la liste à updater
}
void Event::Deactivate()
{
	isActive = false; 
	curSteps = 1;			// reset le nombre de steps
	toUpdate.Unregister();//	Retire l'event à la liste de "à updater"
}

// UPDATE TOUT LES EVENT EN COURS !!!!!!!!!!!!!!!!!!!!!!!!
void Event::Update_Active_Events()
{
	for (toUpdate.index = 0; toUpdate.index < toUpdate.Get_Total(); toUpdate.index++)		// Tant qu'on a des events qui n'ont pas été updaté
	{
		eventsID[toUpdate.Copy_Element(toUpdate.index)]->Handle_It();		// Ne jamais touché à toUpdate.index en dehors d'ici :()
	}															// Pour l'instant, un event pourrait en activer un autre, et rallonger cette loop!
}

bool Event::Stop_If_No_More_Steps()
{
	if (curSteps >= steps)		// > c'est un fail safe
	{
		Deactivate();			// We deactivate!!!
		return true;
	}
	else
		return false;
}




