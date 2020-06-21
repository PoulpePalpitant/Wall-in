
#include "../lvls/lvl_script.h"
#include "../lvls/lvl_1/lvl_1_events_checker.h"
#include "events.h"


// CHECK LES ÉVÈNEMENTS SPÉCIAUX
void Events_Listener()
{
	
	Handle_Lvl_Events();			//if (!already_Done_That_Event)
	//LVL1_Events(Current_Time, BOTSpwnedTOT);
	//LVL1_Msg_Events(Current_Time, BOTSpwnedTOT);
	//Global_Events();
}

void Lvl_Event_Handler(int eventId)
{
	// Swag_Event()		
	/*//
	
	if(event_is_Active())
	update event stuff

	*/
}

void Events_Handler()
{








}

void Handle_Lvl_Events()//
{
	switch (gCurrentLevel)
	{
	case 1: Lvl_1_Event_Listener();	// Check quels sont les events
		Lvl_1_Event_Handler();		// Appliquent les events




	}
	
	//Global_Events();

}



void EventQueue::Add(Event* event)
{
	queue[tail + 1 % EV_QUEUE_SIZE] = event;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro



}
void EventQueue::Remove()
{


}
void EventQueue::Update_Events_In_Queue()
{


	

}


//  TU RÉPÈTE DU CODE ET C'EST PAS UNE BONNE CHOSE



void EventManager::Update_Listeners()
{
	if (listener.head == listener.tail) return;		// Il n'y a rien dans la queue


	for (int i = listener.head; i != listener.tail; i = (i + 1) % EV_QUEUE_SIZE)		// Parcours toute la liste
	{
		listener.queue[i]->Listener();

	}

}
void EventManager::Update_Handlers()
{
	if (handler.head == handler.tail) return;		// Il n'y a rien dans la queue


	for (int i = handler.head; i != handler.tail; i = (i + 1) % EV_QUEUE_SIZE)		// Parcours toute la liste
	{
		handler.queue[i]->Event_();	//ici
	}




}