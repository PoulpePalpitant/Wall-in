
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
#include "global_events/ev_spwn_player.h"
#include "global_events/ev_final_push.h"
#include "global_events/ev_resize_from_grids.h"
#include "../items/item_spw_drawer.h"			// spawner les items
#include "../blast/mod_queue_animator.h"






// GLOBAL

MsgType gCurrentMsg = LITERALLY_NOTHING;		// Prend un msg qui sera interprété par les event Listeners


// STATIC
MsgType MsgQueue::queue[MSG_QUEUE_SIZE];	// La liste de tout les messages enregistré pendant une frame
int MsgQueue::head = 0;
int MsgQueue::tail = 0;		// début, fin d'indice du array
int MsgQueue::total = 0;



/* EVENT QUEUES !!!*/

void MsgQueue::Unregister()	// retire le message de la queue
{
	head = (head + 1) % MSG_QUEUE_SIZE;	// Retire l'élément au début de la queue
	total--;
}

void MsgQueue::Register(MsgType msg)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (total < MSG_QUEUE_SIZE)//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = msg;			// Ajoute l'élément sur la tail au bout 
		tail = (tail + 1) % MSG_QUEUE_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro
		total++;
	}
	else
		return;
}

void MsgQueue::Dispatch_Messages()		// Prend un message enregistré de la liste à envoyé
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
	case 1: Dispatch_Msg_To_Lvl_1();break;			// Check les events à faire
	case 2:// Lvl_2_Upd_Events();break;			// Check les events à faire
	case 3:// Lvl_3_Upd_Events();break;			// Check les events à faire
	case 4:// Lvl_4_Upd_Events();break;			// Check les events à faire
	case 5:// Lvl_5_Upd_Events();break;			// Check les events à faire
	case 6:// Lvl_6_Upd_Events();break;			// Check les events à faire
	case 7: break;// Lvl_7_Upd_Events();break;			// Check les events à 			
	}
}

void Dispatch_To_Global()	// Update tout les autres qui sont pas dans des modules indépendants
{
	switch (gCurrentMsg)
	{
		/* Level */

	case BLAST_REACHED_BORDER:
		if(!gBorderShown)
			Ev_Border_Splash();		// fait un tit splash
		break; 		

	case FINAL_PUSH: 
		Ev_Final_Push(); // Msg que la dernière attaque s'en vient
		break;

	case PRESSED_ENTER: 
		lastKey = KeyPressed::ENTER;
		break;

	case STAGE_ADVANCE:
		gCurrentStage++;	// Passe au prochain stage
		break;

		//Ev_Flash_Map_Corners();	// Fait flaser les coins de la map pendant un bref instant, si le joueur tir sur un mur
		
		/* GRIDS*/
	case GRIDS_RESIZED: 
		Ev_Resize_From_Grids();
		break;

	case LINK_ACTIVATED:
		break;

	case LINK_DEACTIVATED:
		break;

	case WALL_ACTIVATED:
		break;

	case WALL_DEACTIVATED:
		break;
		
		/* UI */
	case SHOW_HEALTH:break;
	case HIDE_HEALTH:break;
	
	case SHOW_MOD_QUEUE:
		DrawModifierQueue::Show_Queue_UI();
		break;

	case HIDE_NEXT_QUEUE:
		DrawModifierQueue::Hide_Queue_UI();
		break;





		/* PLAYER*/
	case LOCK_PLAYER: 
		Ev_Block_Inputs(true);
		break;

	case FREE_PLAYER: 
		Ev_Block_Inputs(false);
		break;

	case SPAWN_PLAYER:	
		Ev_Spawn_Player();		// Cinématique d'apparition du joueur
		break;

	case PLAYER_SPAWNED:
		break;
		/* ITEMS */

	case ITEM_SPAWNED: 
		//Draw_Item_Spawn();
		break;
		/* BOTS */
	case STOP_BOTS:			Ev_Stop_Bot_Cycles(); break;
	case STOP_BOT_MOVE:		Ev_Stop_Bot_Move();break;
	case STOP_BOT_SPAWNS:	Ev_Stop_Bot_Spawn();break;
	case START_BOTS:		Ev_Start_Bot_Cycles	();break;
	case START_BOT_MOVE:	Ev_Start_Bot_Move();break;
	case START_BOT_SPAWNS:	Ev_Start_Bot_Spawn();break;

	case BUMPED_BORDER: 
		//Ev_Dr_Map_Borders_1();
		break;

		/* Clavier*/

	case BLOCK_ALL_INPUTS:
		gBlockInputs = true;
		break;

	case UNBLOCK_ALL_INPUTS: 
		gBlockInputs = false;
		break;

	case ACTIVATE_BLAST:
		gBlockBlast = false;
		break;

	case DEACTIVATE_BLAST:
		gBlockBlast = true;
		break;
		// Tout les events qui sont trigger par ça  
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