#pragma once

/*
POST-MORTEM:

	Un système de messagerie un peu bâtard.
	Au final, je crois que j'aurais probablement réussit à faire sans, surtout si on considère que les messages sont utilisés comme des méthodes.
	Néanmoins c'était quand même utile lorsque j'essayais de faire une histoire avec le jeu, et que j'essayais de créer des triggers selon certaines intéractions du joueur.
*/

enum MsgType
{
	LITERALLY_NOTHING	// Null
	
	/* Game stuff*/
	, WAITING_TIME
	, PAUSE_GAME
	, UNPAUSE_GAME

	/*Level Stuff*/
	, PLS_INTIALIZE_LVL
	, STAGE_ADVANCE			
	, LVL_INITIALIZED
	, FINAL_HOUR
	, WAIT_LAST_BOT			
	, VICTORY
	, DEFEAT
	, PRESS_X_TO_PROCEED
	, PROCEED
	, LOAD_CHECKPOINT
	, CHECKPOINT_REACHED
	, RETURN_TO_MENU

	/* UI stuff */
	, SHOW_HEALTH
	, HIDE_HEALTH
	, SHOW_MOD_QUEUE
	, HIDE_MOD_QUEUE

	/* grid stuff */
	, GRIDS_RESIZED

	/* Walls and Links stuff*/
	, LINK_ACTIVATED
	, LINK_DEACTIVATED
	, WALL_ACTIVATED
	, WALL_DEACTIVATED

	/* Items */
	, ITEM_PICKUP
	, ITEM_DESTROYED
	, ITEM_SPAWNED
	, SPAWN_SPECIAL_ITEM
	, ENABLE_ITEM_SPAWN
	, DISABLE_ITEM_SPAWN

	/* Player Stuff*/
	, SPAWN_PLAYER
	, PLAYER_SPAWNED
	, LOCK_PLAYER		
	, FREE_PLAYER		
	, IS_A_DOUCHE
	, FIRST_HIT		
	, BUMPED_BORDER		
	, TOUCHED_ENNEMY
	, P1_LOST_HP
	, PLAYER_DEAD

	/* Ennemy Stuff*/
	, ENNEMY_KILLED
	, ENNEMY_SPWN
	, NO_BOTS_ALIVE
	, JERRY_DIED
	, SPECIAL_SPAWN
	, STOP_BOT_SPAWNS	
	, STOP_BOT_MOVE		
	, STOP_BOTS			
	, START_BOT_SPAWNS	
	, START_BOT_MOVE	
	, START_BOTS		
	, RESET_SPW_TOT		

	/* Blast Stuff*/
	, BLAST_REACHED_BORDER
	, WALL_TRANSFER
	, BLAST_HIT_ITEM
	, BULLETS_DEPLETED
	, ENABLE_BLAST	
	, DISABLE_BLAST	

	/* Window stuff*/
	, CHANGE_WINSIZE	

	/* Clavier*/
	, PRESSED_ENTER		
	, SELECTED_SOMETHING
	, PRESSED_KEY
	, BLOCK_ALL_INPUTS
	, UNBLOCK_ALL_INPUTS
};


// Dépasser la queue size softlock le jeu :(
const int MSG_QUEUE_SIZE = 10000;	

// GLOBAL
extern MsgType gCurrentMsg;		

class MsgQueue			
{
	static MsgType queue[MSG_QUEUE_SIZE];	// Un vecteur aurait été nice, au lieux d'un ringbuffer
	static int head, tail;					
	static int total;

	static void Unregister();
public:
	static void Register(MsgType msg);	
	static void Dispatch_Messages();
	static void Unregister_All();		
	static void Reset_Total();

};

void Dispatch_To_Lvl();	
void Dispatch_To_Global();	
