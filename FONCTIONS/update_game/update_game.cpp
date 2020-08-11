
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


extern bool gIsRunning = true;		// le state du jeu
static std::string pauseMsg = "Hey! You PAUSED the game!";

void Update_Game()		// Update tout ce qui se passe dans le jeu
{
	Update_Player_Action();

	if (!GameLoopClock::pause)	// GAME_PAUSED
	{
		blastP1.UPD_Blast_Shot();		// Devrais être un event global	

		UPD_Cycles_Stuff();		// Mouvement et spawn des bots
		Peek_Lvl_Script();		// En ce moment, ça sert pas mal juste à peek le spawnscript...
		Do_Stuff_this_Cycle();	// Bouge et spawn les bots
		MsgQueue::Dispatch_Messages();	// Envoie tout les messages pour vérifier si on update les events

		ItemSpawner::UPD_Item_Spawn_Timers();
		DrawItemSpawnList::Draw_Item_Spawn();	// Les items qui spawnent
		DrawWalls::Draw_Them_Walls();			// draw les putains de walls
		ListsOfChainToModify::Update_Chain_Modification();
		DrawModifierQueue::Update_Modifier_Queue();

		Event::Update_Active_Events();	// Update tout les events dans la queue d'events à updater
	}
}


void Update_Game_NOT_60FPS()	// à Remove
{
	P1.Upd_Player_Timeout();	// Si le joueur est en timeout, on update ça
}

// Fait une action selon l'input du joueur
void Update_Player_Action()
{
	if (!gBlockInputs)
	{
		if (!GameLoopClock::pause)
		{
			switch (action)
			{
			case PAUSE:
				GameLoopClock::pause = true;
				ConsoleRender::Add_String(pauseMsg, { Find_Ctr_X((int)std::size(pauseMsg)) , 2 }, BRIGHT_WHITE, 50);			// Besoin d'un max screen size
				break;

			case CHANGE_BLAST:
				Change_Blast();		// trying stuff
				break;

			case BLAST:
				if (!blastP1.Is_Active() && !ChoiceTime::Is_Choice_Time() && !gBlockBlast)
				{
					//static Blast* blast; 		blast = &blastP1;	// da blast

					static GrdCoord grdCrd;	// Position du joueur
					grdCrd = P1.Get_Grd_Coord();

					static Link* link;	// Link se trouvant sur la position du joueur
					link = &linkGrid->link[grdCrd.c][grdCrd.r];

					bool cancelBlast = false;

					// Action Spéciale: Un transfer
					// Le Transfer à lieu quand le joueur se trouve sur un Link FREE. Si il tire dans une autre direction que le parent du Link, le Link FREE est détruit et un blast à lieu. C'est comme si on transférait le Wall
					if (link->Get_State() == LinkState::FREE)
					{
						// Si on tir dans la même direction que son parent wall		
						if (StructureManager::Is_Parent_In_This_Direction(link, keyDirection))
							cancelBlast = true; // rien va se passer
						else
							ListsOfChainToModify::Add_Chain_To_Modify(grdCrd);	// On destroy le Link que l'on veut transférer  /	// ensuite on fait un tir normal

						// SI LE LINK EST D'UN CERTAIN DTYPE, LE BLAST modifier DEVRAIT PRENDRE SA PROPRIÉTÉ!
					}

					if (blastP1.Is_Player_Shooting_Border(keyDirection))
					{
						UI_Invalide_Action();
						cancelBlast = true; // rien va se passer
					}

					if (!cancelBlast)
					{
						blastP1.Setup_Blast(grdCrd, keyDirection);
					}
				}
				else
				{
					Blast_Disabled_While_CD();		// Check si c'est à cause de ça
					P1.Set_Timeout(300);			// Freeze le joueur pour une durée de temps 
					ConsoleRender::Add_Char(P1.Get_XY(), P1.Get_Sym(), LIGHT_PURPLE);		// Really dumb shit
				}
					
				break;

			case MOVE:
				if (!blastP1.Is_Active() && !gChoiceTime)	// Le joueur ne peut bouger durant un blast
					Move_Player(P1, keyDirection);	// bouge le joueuruu!
				break;

			}
		}
		else
			if (action == UNPAUSE)
			{
				GameLoopClock::pause = false;
				ConsoleRender::Add_String("                         ", { Find_Ctr_X((int)std::size(pauseMsg)) , 2 });			// Besoin d'un max screen size
			}
	}
	// Faut reset l'action
	action = IDLE;
	keyDirection = NONE;	// et la keydirection

}

/*
	À Pt modifier un jour:si tu fais un transfert sur une bordure, tu détruis le wall, mais le blast ne franchis aucune distance si tu fais un transfert horizontale, la longueur maximale n'est pas limité à un wall...
*/