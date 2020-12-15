
#include "update_game.h"

#include "../lvls/lvl_script.h"
#include "../inputs/action_input.h"
#include "../blast/blast.h" // testing
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

extern bool gPauseUpdates = false;		// le state du jeu
static std::string pauseMsg = "Hey! You PAUSED the game!";
static std::string pauseMsg_2 = "Press 'Space' To Go Back To The Menu ";


void Update_Game()		// Update tout ce qui se passe dans le jeu
{
	Update_Player_Action();

	if (!gPauseUpdates)	// GAME_PAUSED
	{
		blastP1.UPD_Blast_Shot();		// Devrais �tre un event global	

		UPD_Cycles_Stuff();		// Mouvement et spawn des bots
		Peek_Lvl_Script();		// En ce moment, �a sert pas mal juste � peek le spawnscript...
		Do_Stuff_this_Cycle();	// Bouge et spawn les bots. 
		MsgQueue::Dispatch_Messages();	// Envoie tout les messages pour v�rifier si on update les events
		ListsOfChainToModify::Update_Chain_Modification();	// Un processus de destruction des murs
		P1.Upd_Teleporter();	// Check si le teleporteur est d�truit
		
		// Certaines animations 
		// ********************
		DrawItemSpawnList::Draw_Item_Spawn();	// Les items qui spawnent	// J'AI INVERS� UPDATE CHAIN MODIF AVEC �A
		DrawModifierQueue::Update_Modifier_Queue();			// Une animation quelconque
		DrawWalls::Draw_Them_Walls();	// draw les putains de walls

		Event::Update_Active_Events();	// Update tout les events dans la queue d'events � updater

	}
}


void Update_Game_NOT_60FPS()	// � Remove
{
	P1.Upd_Player_Timeout();	// Si le joueur est en timeout, on update �a
}

// Fait une action selon l'input du joueur
void Update_Player_Action()
{
	if (!gBlockInputs)
	{
		if (!gPauseUpdates)
		{
			if (blastP1.Is_Active() && action != PAUSE)	// Emp�che de refresh l'action. Ceci est le buffer du blast
				return;

			switch (action)
			{
			case PAUSE:
				gPauseUpdates = true;
				ConsoleRender::Add_String(pauseMsg, { Find_Ctr_X((int)std::size(pauseMsg)) , 2 }, BRIGHT_WHITE);			// Besoin d'un max screen size
				ConsoleRender::Add_String(pauseMsg_2, { Find_Ctr_X((int)std::size(pauseMsg_2)) ,gConHeight}, GRAY);			// Besoin d'un max screen size
				if (gDayStarted)
				{
					Press_R_To_Retry_On_Pause(1);
					gRetryCheckpoint = true;
				}
				break;

			case CHANGE_BLAST:
				Change_Blast();		// trying stuff
				break;

			case BLAST:
				if (!ChoiceTime::Is_Choice_Time() && !gBlockBlast)
				{
					static GrdCoord grdCrd;	// Position du joueur
					grdCrd = P1.Get_Grd_Coord();

					static Link* link;	// Link se trouvant sur la position du joueur
					link = &linkGrid->link[grdCrd.c][grdCrd.r];

					bool cancelBlast = false;
					bool consumeQueue = true;
					bool blastTransfer = false; // Transfer ne compte pas comme un tir normal. C'est plut�t une destruction d'un wall existant, suivi d'un tir dans une autre direction. 
					BlastAmmo *ammo;	


					blastP1.Set_Strength(WallStrength::REGULAR);	// dflt

					// Action Sp�ciale: Un transfer
					// Le Transfer � lieu quand le joueur se trouve sur un Link FREE. Si il tire dans une autre direction que le parent du Link, le Link FREE est d�truit et un blast � lieu. C'est comme si on transf�rait le Wall
					if (link->Get_State() == LinkState::FREE)
					{

						// Si on tir dans la m�me direction que son parent wall		
						if (StructureManager::Is_Parent_In_This_Direction(link, keyDirection))
							cancelBlast = true; // rien va se passer
						else
						{
							blastP1.Set_Strength(link->Get_Parent()->Get_Strgt());// La force du tir est d�termin� par le  wall!!!
							ListsOfChainToModify::Add_Chain_To_Modify(grdCrd);	// On destroy le Link que l'on veut transf�rer  /	// ensuite on fait un tir
							consumeQueue = false;
							blastTransfer = true;	// it is true!
						}

						// SI LE LINK EST D'UN CERTAIN DTYPE, LE BLAST modifier DEVRAIT PRENDRE SA PROPRI�T�! le blast ne devrait pas prendre la propri�t� de la queue
					}

					if (blastP1.Is_Player_Shooting_Border(keyDirection))
					{
						UI_Invalide_Action();
						cancelBlast = true; // rien va se passer
					}

					if (!blastTransfer && !cancelBlast)	// Check si le joueur a ass� d'ammo pour tirer
					{
						ammo = &blastP1.Get_Ammo_Manager();		// WATCHOUT, va pt retourner l'adresse d'une variable temporaire ou je sais pas trop
						cancelBlast = !ammo->Shoot();			// Failure to shoot means we cancel that blast
					}

					if (!cancelBlast)
						blastP1.Setup_Blast(grdCrd, keyDirection, consumeQueue);
					else
						Ev_Wrong_Action_Add();			// Flash le joueur

				}
				else
				{


					Blast_Disabled_While_CD();		// Check si c'est � cause de �a
					Ev_Wrong_Action_Add();			// Flash le joueur
					ConsoleRender::Add_Char(P1.Get_XY(), P1.Get_Sym(), LIGHT_PURPLE);		// Really dumb shit
				}
				break;

			case MOVE:
				if (!gChoiceTime)	
					Move_Player(P1, keyDirection);	// bouge le joueuruu!
				break;

			case TELEPORT:
				if (!blastP1.Is_Active())
				{
					if (!P1.Get_Teleporter().Teleport_Player())	// BAM! Teleport
						Ev_Wrong_Action_Add();			// Flash le joueur
				}
				else
					return;	// Conserve l'action de t�l�porter
				break;
			}
		}
		else
			if (action == UNPAUSE)
			{
				gPauseUpdates = false;
				ConsoleRender::Add_String("                         ", { Find_Ctr_X((int)std::size(pauseMsg)) , 2 });			// Besoin d'un max screen size / DONE
				ConsoleRender::Add_String(pauseMsg_2, { Find_Ctr_X((int)std::size(pauseMsg_2)) ,gConHeight }, GRAY,0, true);		// 
				if (gDayStarted)
				{
					Press_R_To_Retry_On_Pause(1, true);
					gRetryCheckpoint = true;
				}
			}
	}

	// Faut reset l'action
	action = IDLE;
	keyDirection = NONE;	// et la keydirection
}

/*
	� Pt modifier un jour:si tu fais un transfert sur une bordure, tu d�truis le wall, mais le blast ne franchis aucune distance si tu fais un transfert horizontale, la longueur maximale n'est pas limit� � un wall...
*/