
/*Lvl Events*/
#include "../lvls/lvl_script.h"

#include "../menu/menu_script.h"
#include "../menu/events/Ev_Start_Game.h"
#include "../lvls/lvl_1/lvl_1_upd_events.h"







/* Global Events*/
#include "global_events/ev_flash_map_corners.h"
#include "global_events/ev_border_splash.h"


#include "events.h"



// au début du niveau, ajoute tout les checkeux d'event dans la liste de checkeux

void Update_Events()	// Par ici qu'on va updater tout les events. 
{

	//switch (gCurrentLevel)
	//{
	//case 1: Lvl_1_Upd_Events();break;			// Check les events à faire
	//case 2:// Lvl_2_Upd_Events();break;			// Check les events à faire
	//case 3:// Lvl_3_Upd_Events();break;			// Check les events à faire
	//case 4:// Lvl_4_Upd_Events();break;			// Check les events à faire
	//case 5:// Lvl_5_Upd_Events();break;			// Check les events à faire
	//case 6:// Lvl_6_Upd_Events();break;			// Check les events à faire
	//case 7:// Lvl_7_Upd_Events();break;			// Check les events à 			
	//}

	Upd_Global_Events();
}
void Upd_Global_Events()	// Update tout les autres qui sont pas dans des modules indépendants
{
	MessageQueue::Update();		// Update tout les events concerné par des messages
	// Event Wowow
	// Event swager
	// Event swager
	// Event swager
	// Event swager
	// Secret event
	// Event swager
	// Event swager
	// Event swager
	// Event swager
	// Event swager
	// Event swager
	// Event Wowow
	// Event Wowow
	// Event Wowow   	 
}


/* EVENT QUEUES !!!*/


EventType MessageQueue::queue[QUEUE_SIZE];	// La liste de tout les messages enregistré pendant une frame
int MessageQueue::head = 0; 
int MessageQueue::tail = 0;		// début, fin d'indice du array
int MessageQueue::total = 0;

void MessageQueue::Unregister()	// retire le message de la queue
{
	head = (head +  1) % QUEUE_SIZE;	// Retire l'élément au début de la queue
	total--;
}

void MessageQueue::Register(EventType msg)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (total < QUEUE_SIZE)//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = msg;			// Ajoute l'élément sur la tail au bout 
		tail = (tail + 1) % QUEUE_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro
		total++;
	}
	else
		return;
}

void MessageQueue::Update()
{
	if (head == tail) return;	// Liste vide

	for (int msg = head; msg != tail; msg = (msg + 1) % QUEUE_SIZE)
	{
		switch (queue[msg])
		{
		case BLAST_REACHED_BORDER:	
			// Envoie du msg BLAST_REACHED_BORDER dans le module MENU.
			// Le module menu ajoute le message à sa queue d'update
			// Si un event est trigger

			Ev_Border_Splash(); break; ;		// fait un tit splash
			//Ev_Flash_Map_Corners();	// Fait flaser les coins de la map pendant un bref instant, si le joueur tir sur un mur

		case PRESSED_ENTER: Ev_Start_Game();break;
			// Tout les events qui sont trigger par ça  


		}
		
		Unregister();	// Retire le message de la queue. Malheureusement, je ne peux pas faire des events sur une quelconque durée avec cette méthode, car je ne peut pas remove des messages entre la head et la tail. Je dois systématiquement remove
	}

	
}









//// CHECK LES ÉVÈNEMENTS SPÉCIAUX
//void Events_Listener()
//{
//	
//	//Handle_Lvl_Events();			//if (!already_Done_That_Event)
//	//LVL1_Events(Current_Time, BOTSpwnedTOT);
//	//LVL1_Msg_Events(Current_Time, BOTSpwnedTOT);
//	//Global_Events();
//}
//
//void Lvl_Event_Handler(int eventId)
//{
//	// Swag_Event()		
//	/*//
//	
//	if(event_is_Active())
//	update event stuff
//
//	*/
//}

/*
void RingBuffer::Add(int data)
{
	queue[tail + 1 % QUEUE_SIZE] = data;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro



}
void RingBuffer::Remove()
{
	(head += 1) % QUEUE_SIZE;

}

void EventManager::Update_Listeners()
{
	if (listener.head == listener.tail) return;		// Il n'y a rien dans la queue


	for (int i = listener.head; i != listener.tail; i = (i + 1) % QUEUE_SIZE)		// Parcours toute la liste
	{
		listener.queue[i]->Listener();

	}

}

*/