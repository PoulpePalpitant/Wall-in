
#include "update_game.h"

#include "../lvls/lvl_script.h"
#include "../inputs/action_input.h"
#include "../blast/blast.h" 
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "../player/player_move.h"
#include "../structure_manager/structure_manager.h"
#include "../time/timerOP.h"
#include "../UI/console_output/render_list.h"
#include "../blast/change_blast.h"
#include "../events/events.h"
#include "../events/msg_dispatcher.h"
#include "../time/cycles.h"
#include "../walls/wall_drawer.h"
#include "../items/item_spw_drawer.h"
#include "../items/item_spawner.h"
#include "../blast/mod_queue_animator.h"
#include "../animation/UI_invalid_move.h"
#include "../choice/choice_time.h"
#include "../events/global_events/ev_countdown.h"
#include "../console/sweet_cmd_console.h"
#include "../events/global_events/ev_to_proceed.h"
#include "../events/global_events/feedback/ev_wrong_action.h"
#include "../teleporter/teleporter.h"

extern bool gPauseUpdates = false;		
static std::string pauseMsg = "Hey! You PAUSED the game!";
static std::string pauseMsg_2 = "Press 'Space' To Go Back To The Menu ";


void Update_Game()		
{
	Update_Player_Action();

	if (!gPauseUpdates)	// GAME_PAUSED
	{
		blastP1.UPD_Blast_Shot();		

		UPD_Cycles_Stuff();		// Mouvement et spawn des bots
		Peek_Lvl_Script();		// Ça sert pas mal juste à peek le spawnscript finalement...
		Do_Stuff_this_Cycle();	// Bouge et spawn les bots. 
		MsgQueue::Dispatch_Messages();	
		ListsOfChainToModify::Update_Chain_Modification();	// Un processus de destruction des murs
		
		// Certaines animations 
		// ********************
		DrawItemSpawnList::Draw_Item_Spawn();	
		DrawModifierQueue::Update_Modifier_Queue();		// Animation de l'UI
		DrawWalls::Draw_Them_Walls();					

		Event::Update_Active_Events();	
	}
}


void Update_Game_NOT_60FPS()	// À Remove un jour
{
	P1.Upd_Player_Timeout();	// Si le joueur est en timeout, on update ça
}

// Fait une action selon l'input du joueur
void Update_Player_Action()
{
	if (!gBlockInputs)
	{
		if (!gPauseUpdates)
		{
			if (blastP1.Is_Active() && action != PAUSE)	// Empêche de refresh l'action. Ceci est le buffer du blast
				return;
			
			switch (action)
			{
			case PAUSE:
				gPauseUpdates = true;
				ConsoleRender::Add_String(pauseMsg, { Find_Ctr_X((int)std::size(pauseMsg)) , 1 }, BRIGHT_WHITE);			
				ConsoleRender::Add_String(pauseMsg_2, { Find_Ctr_X((int)std::size(pauseMsg_2)) ,gConHeight}, GRAY);			
				if (gLevelStarted)
				{
					Press_X_To_Proceed(2);
					gRetryCheckpoint = true;
				}
				break;

			case BLAST:
				if (!ChoiceTime::Is_Choice_Time() && !gBlockBlast)
				{
					static GrdCoord grdCrd;	
					grdCrd = P1.Get_Grd_Coord();

					static Link* link;		// Link se trouvant sur la position du joueur
					link = &linkGrid->link[grdCrd.c][grdCrd.r];

					bool cancelBlast = false;
					bool consumeQueue = true;
					bool blastTransfer = false; // Transfer ne compte pas comme un tir normal. C'est plutôt une destruction d'un wall existant, suivi d'un tir dans une autre direction. 
					BlastAmmo *ammo;	


					blastP1.Set_WallType(WallType::REGULAR);	

					// Le Transfer à lieu quand le joueur se TROUVE sur un Link FREE. Si il tire dans une autre direction que le parent du Link, le Link FREE est détruit et un blast à lieu. 
					if (link->Get_State() == LinkState::FREE)
					{
						if (StructureManager::Is_Parent_In_This_Direction(link, keyDirection))
							cancelBlast = true; 
						else
						{
							blastP1.Set_WallType(link->Get_Parent()->Get_Type());
							blastP1.Setup_Modifier(link->Get_Modifier());		// dumb shit beurks fixes, yey!

							ListsOfChainToModify::Add_Chain_To_Modify(grdCrd);	// On destroy le Link que l'on veut transférer  / ensuite on fait un tir
							consumeQueue = false;
							blastTransfer = true;	
						}
					}

					if (blastP1.Is_Player_Shooting_Border(keyDirection))
					{
						UI_Invalide_Action();
						cancelBlast = true; 
					}

					if (!blastTransfer && !cancelBlast)	// Check si le joueur a assé d'ammo pour tirer
					{
						ammo = &blastP1.Get_Ammo_Manager();		
						cancelBlast = !ammo->Shoot();			
					}

					if (!cancelBlast)
					{
						blastP1.Setup_Blast(grdCrd, keyDirection, consumeQueue);
						P1.Get_Teleporter().Remove_Teleport_Location();
					}
					else
						Ev_Wrong_Action_Add();			

				}
				else
				{
					Blast_Disabled_While_CD();		// Check si c'est à cause de ça
					Ev_Wrong_Action_Add();			
					ConsoleRender::Add_Char(P1.Get_XY(), P1.Get_Sym(), LIGHT_PURPLE);		
				}
				break;

			case MOVE:
				if (!gChoiceTime)	
					Move_Player(P1, keyDirection);	// bouge le joueuruu!
				break;

			case TELEPORT:
				if (blastP1.Is_Active())
					return;	// Conserve l'action
				else
					if (!P1.Get_Teleporter().Teleport_Player())	// BAM! Teleport
						Ev_Wrong_Action_Add();			
				break;
			}
		}
		else
			if (action == UNPAUSE)
			{
				gPauseUpdates = false;
				ConsoleRender::Add_String("                         ", { Find_Ctr_X((int)std::size(pauseMsg)) , 1 });			
				ConsoleRender::Add_String(pauseMsg_2, { Find_Ctr_X((int)std::size(pauseMsg_2)) ,gConHeight }, GRAY,0, true);	
				if (gLevelStarted)
				{
					Press_X_To_Proceed(2, true);
					gRetryCheckpoint = true;
				}
			}
	}

	// Faut reset l'action
	action = IDLE;
	keyDirection = NONE;	// et la keydirection
}
