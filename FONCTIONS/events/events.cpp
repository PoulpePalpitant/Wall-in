

#include "msg_dispatcher.h"
#include "events.h"
#include "global_events/ev_pause_game.h"


Event* Event::eventsID[MAX_NUM_EVENTS] = {};	
FixedList<int>Event::toUpdate(MAX_NUM_EVENTS);	
int Event::total = 0;	

void Event::Activate()
{
	isActive = true;	
	toUpdate.Register(ID);	// Ajoute l'event à la liste à updater
}

void Event::Deactivate()
{
	static int index;

	isActive = false; 
	if(toUpdate.Find_Element(ID, index))
		toUpdate.Unregister(index);	//	Retire l'event à la liste de "à updater"
}

void Event::Cancel_All()	
{
	// the inefficient, but correct way
	for (int id = 0; id < MAX_NUM_EVENTS; id++)
	{
		if (eventsID[id] && eventsID[id]->Is_Active())
			eventsID[id]->Deactivate();
	}
}


// UPDATE TOUT LES EVENT EN COURS !!!!!!!!!!!!!!!!!!!!!!!!
void Event::Update_Active_Events()
{
	for (toUpdate.index = 0; toUpdate.index < toUpdate.Get_Total(); toUpdate.index++)	
	{
		eventsID[toUpdate.Copy_Element(toUpdate.index)]->Handle_It();		// Ne jamais touché à toUpdate.index en dehors d'ici :()
	}																		// Pour l'instant, un event pourrait en activer un autre, et rallonger cette loop!
}

bool Event::Stop_If_No_More_Steps()
{
	if (curSteps > MAX_STEPS)	
	{
		Deactivate();		
		return true;
	}
	else
		return false;
}

// Avance l'event d'un stade. Surtout bon pour de l'animation en ce moment. Mais peut aussi être utilisé pour créer un peu de délay entre les choses
void Event::Advance(int speed, int numMove)
{
	if (!delay.Is_On()) 
	{
		curSteps++;	

		if (!Stop_If_No_More_Steps())	
			delay.Start_Timer(speed, numMove);	
	}
}			

void Event::Start(int speed, int numMove )			// Start l'event!	blob blob
{
	curSteps = 1;	
	delay.Start_Timer(speed, numMove);	
}

void Event::Cancel()									
{
	delay.Stop();		
	Deactivate();		
}