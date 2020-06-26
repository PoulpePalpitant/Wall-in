
#include "msg_dispatcher.h"

/*Lvl DISPATCH	*/
#include "../lvls/lvl_script.h"

#include "../menu/dispatch_msg_to_menu.h"
#include "../menu/events/Ev_Start_Game.h"
#include "../lvls/lvl_1/dispatch_msg_to_lvl_1.h"





/* Global Events*/
#include "global_events/feedback/ev_flash_map_corners.h"
#include "global_events/feedback/ev_border_splash.h"
#include "global_events/feedback/ev_draw_map.h"
#include "global_events/ev_stop_bots.h"
#include "global_events/ev_start_bots.h"
#include "global_events/ev_block_inputs.h"

// GLOBAL

MsgType gCurrentMsg = LITERALLY_NOTHING;		// Prend un msg qui sera interpr�t� par les event Listeners


// STATIC
MsgType MsgQueue::queue[MSG_QUEUE_SIZE];	// La liste de tout les messages enregistr� pendant une frame
int MsgQueue::head = 0;
int MsgQueue::tail = 0;		// d�but, fin d'indice du array
int MsgQueue::total = 0;



/* EVENT QUEUES !!!*/

void MsgQueue::Unregister()	// retire le message de la queue
{
	head = (head + 1) % MSG_QUEUE_SIZE;	// Retire l'�l�ment au d�but de la queue
	total--;
}

void MsgQueue::Register(MsgType msg)	// Ajoute le message � la liste des message � traiter pour ce cycle
{
	if (total < MSG_QUEUE_SIZE)//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = msg;			// Ajoute l'�l�ment sur la tail au bout 
		tail = (tail + 1) % MSG_QUEUE_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'�l�ment z�ro
		total++;
	}
	else
		return;
}

void MsgQueue::Dispatch_Messages()		// Prend un message enregistr� de la liste � envoy�
{
	if (head == tail) return;	// Liste vide

	for (int msg = head; msg != tail; msg = (msg + 1) % MSG_QUEUE_SIZE)
	{
		gCurrentMsg = queue[msg];	// Prend le message

		Dispatch_To_Global();	// Global first?
		Dispatch_To_Lvl();		// Lvl second
		Unregister();
	}
}

void Dispatch_To_Lvl()	// Par ici qu'on va updater tout les events du niveau
{
	switch (gCurrentLevel)
	{
	case 0:	Dispatch_Msg_To_Menu(); break;			// Update les events du menu
	case 1: Dispatch_Msg_To_Lvl_1();break;			// Check les events � faire
	case 2:// Lvl_2_Upd_Events();break;			// Check les events � faire
	case 3:// Lvl_3_Upd_Events();break;			// Check les events � faire
	case 4:// Lvl_4_Upd_Events();break;			// Check les events � faire
	case 5:// Lvl_5_Upd_Events();break;			// Check les events � faire
	case 6:// Lvl_6_Upd_Events();break;			// Check les events � faire
	case 7: break;// Lvl_7_Upd_Events();break;			// Check les events � 			
	}
}

void Dispatch_To_Global()	// Update tout les autres qui sont pas dans des modules ind�pendants
{
	switch (gCurrentMsg)
	{
	case BLAST_REACHED_BORDER:
		Ev_Border_Splash(); break; 		// fait un tit splash
		// Envoie du msg BLAST_REACHED_BORDER dans le module MENU.
		// Le module menu ajoute le message � sa queue d'update Si un event est trigger
	case PRESSED_ENTER: break;

		//Ev_Flash_Map_Corners();	// Fait flaser les coins de la map pendant un bref instant, si le joueur tir sur un mur

		/* Player*/
	case LOCK_PLAYER: Ev_Block_Inputs(true);
	case FREE_PLAYER: Ev_Block_Inputs(false);

		/* BOTS */
	case STOP_BOTS:			Ev_Stop_Bot_Cycles(); break;
	case STOP_BOT_MOVE:		Ev_Stop_Bot_Move();break;
	case STOP_BOT_SPAWNS:	Ev_Stop_Bot_Spawn();break;
	case START_BOTS:		Ev_Start_Bot_Cycles	();break;
	case START_BOT_MOVE:	Ev_Start_Bot_Move();break;
	case START_BOT_SPAWNS:	Ev_Start_Bot_Spawn();break;

	case BUMPED_BORDER: Ev_Draw_Map_Borders_1(); break;
		// Tout les events qui sont trigger par �a  
	}

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