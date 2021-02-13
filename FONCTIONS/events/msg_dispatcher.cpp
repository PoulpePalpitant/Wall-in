
#include "msg_dispatcher.h"

/*Lvl DISPATCH	*/
#include "../lvls/lvl_script.h"
#include "../menu/dispatch_msg_to_menu.h"
#include "../menu/events/Ev_Start_Game.h"
#include "../lvls/lvl_1/dispatch_msg_to_lvl_1.h"
#include "../lvls/lvl_2/dispatch_msg_to_lvl_2.h"
#include "../lvls/lvl_3/dispatch_msg_to_lvl_3.h"


/* Global Events*/
#include "global_events/feedback/ev_border_splash.h"
#include "global_events/feedback/ev_draw_map.h"
#include "global_events/ev_stop_bots.h"
#include "global_events/ev_start_bots.h"
#include "global_events/ev_block_inputs.h"
#include "global_events/ev_spwn_player.h"
#include "global_events/ev_final_hour_1.h"
#include "global_events/ev_resize_from_grids.h"
#include "../items/item_spw_drawer.h"			
#include "../blast/mod_queue_animator.h"
#include "../spawns/ev_spawn_Jerry.h"
#include "global_events/ev_wait_last_bot.h"
#include "global_events/ev_victory_screen.h"
#include "global_events/ev_defeat_screen.h"
#include "global_events/ev_back_to_menu.h"
#include "global_events/ev_checkpoint.h"
#include "../time/spawn_cycle.h"
#include "global_events/feedback/ev_red_borders.h"
#include "../DB/database.h"

// other necessities
#include "../time/cycles.h"



// GLOBAL
static int msgIndex = 0;						// Va chercher l'index dans la queue de messages. Si = à tail, veut dire qu'il a atteint la fin
MsgType gCurrentMsg = LITERALLY_NOTHING;		

// STATIC
MsgType MsgQueue::queue[MSG_QUEUE_SIZE] = {};	// La liste de tout les messages enregistré pendant une frame
int MsgQueue::head = 0;
int MsgQueue::tail = 0;		// début, fin d'indice du array
int MsgQueue::total = 0;



/* EVENT QUEUES !!!*/

void MsgQueue::Unregister()	
{
	head = (head + 1) % MSG_QUEUE_SIZE;
	total--;
}

void MsgQueue::Register(MsgType msg)	
{
	if (total < MSG_QUEUE_SIZE)
	{
		queue[tail] = msg;			
		tail = (tail + 1) % MSG_QUEUE_SIZE;	
		total++;
	}
	else
	{
		Unregister_All();

		queue[tail] = PLS_INTIALIZE_LVL;		// Fix un crash
		tail = (tail + 1) % MSG_QUEUE_SIZE;		
		total++;
	}
}
void MsgQueue::Unregister_All()
{
	gCurrentMsg = LITERALLY_NOTHING;	// Annule le message actuel

	for (int i = 0; i < MSG_QUEUE_SIZE; i++)
		queue[i] = LITERALLY_NOTHING;

	head = tail = total = 0;
	msgIndex = tail;	// Annule le dispatching de message pour cette frame
}

void MsgQueue::Reset_Total() 
{
	total = 0; 
}


void MsgQueue::Dispatch_Messages()		
{
	if (head == tail) return;	

	for ( msgIndex = head; msgIndex != tail; msgIndex = (msgIndex + 1) % MSG_QUEUE_SIZE)
	{
		gCurrentMsg = queue[msgIndex];	

		Dispatch_To_Global();	// Global first
		Dispatch_To_Lvl();		// Lvl second
		Unregister();			
	}
}

void Dispatch_To_Lvl()	
{
	switch (gCurrentLevel)
	{
	case 0:	Dispatch_Msg_To_Menu(); break;			
	case 1: Dispatch_Msg_To_Lvl_1();break;			
	case 2: Dispatch_Msg_To_Lvl_2();break;			
	case 3: Dispatch_Msg_To_Lvl_3();break;			
	}
}

void Dispatch_To_Global()	
{
	switch (gCurrentMsg)
	{
		/* Level */
	case RETURN_TO_MENU:
		Go_Back_To_Menu();
		break;

	case CHECKPOINT_REACHED:
		Ev_Reach_Checkpoint();
		break;

	case FINAL_HOUR: 
		if (gCurrentLevel <= 3)
			Ev_Final_Hour_1(); 
		break;

	case PRESSED_ENTER: 
		lastKey = KeyPressed::ENTER;
		break;

	case STAGE_ADVANCE:
		gCurrentStage++;	// Passe au prochain stage
		break;

	case VICTORY:
		if (gCurrentLevel < 3)
		{
			if (gUnlockedLevels[gCurrentLevel] != 1)
			{
				gUnlockedLevels[gCurrentLevel] = 1;
				gLastLvlUnlocked = gCurrentLevel + 1;
			}
		}
		else
			gLastLvlUnlocked = -1;


		gCurrentPuzzle[gCurrentLevel - 1] = 0;

		Save();	// save that data avant la victory screen !

		Ev_Victory_Screen();
		break;	
	
	case DEFEAT:
		if (gLevelStarted)
			Ev_Fast_Defeat_Screen();
		break;


		/* GRIDS*/
	case GRIDS_RESIZED: 
		Ev_Resize_From_Grids();
		break;
		
		/* UI */
	case SHOW_MOD_QUEUE:
 		DrawModifierQueue::Show_Queue_UI();
		break;

	case HIDE_MOD_QUEUE:
		DrawModifierQueue::Hide_Queue_UI();
		break;

		/* BLAST */

	case BLAST_REACHED_BORDER:
		if (!gBorderShown)
			Add_Border_Splash();		// fait un tit splash
		break;


		/* PLAYER*/
	case LOCK_PLAYER: 
		Ev_Block_Inputs(true);
		break;

	case FREE_PLAYER: 
		Ev_Block_Inputs(false);
		break;

	case SPAWN_PLAYER:	
		Set_Ev_Spawn_Player();		// Cinématique d'apparition du joueur
		break;

		/* ITEMS */
	case ENABLE_ITEM_SPAWN:
		stopItmSpwCycle = false;
		break;

	case DISABLE_ITEM_SPAWN:
		stopItmSpwCycle = true;
		break;

		/* BOTS */
	case RESET_SPW_TOT:		Reset_Spw_Cycle(); break;
	case STOP_BOTS:			Ev_Stop_Bot_Cycles(); break;
	case STOP_BOT_MOVE:		Ev_Stop_Bot_Move();break;
	case STOP_BOT_SPAWNS:	Ev_Stop_Bot_Spawn();break;
	case START_BOTS:		Ev_Start_Bot_Cycles	();break;
	case START_BOT_MOVE:	Ev_Start_Bot_Move();break;
	case START_BOT_SPAWNS:	Ev_Start_Bot_Spawn();break;
	case JERRY_DIED:		Update_Dead_Jerrys(); break;

		/* Clavier*/
	case BLOCK_ALL_INPUTS:
		gBlockInputs = true;
		break;

	case UNBLOCK_ALL_INPUTS: 
		gBlockInputs = false;
		break;

	case ENABLE_BLAST:
		gBlockBlast = false;
		break;

	case DISABLE_BLAST:
		gBlockBlast = true;
		blastP1.Cancel();
		break;
	}
}