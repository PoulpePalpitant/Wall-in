

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

#include "update_game.h"

extern bool gIsRunning = true;		// le state du jeu
static std::string pauseMsg = "Hey! You PAUSED the game!";

void Update_Game()		// Update tout ce qui se passe dans le jeu
{
	Update_Player_Action();

	if (!GameLoopClock::pause)	// GAME_PAUSED
	{
		UPD_Bots_Cycles();		// Mouvement et spawn des bots
		Peek_Lvl_Script();		// En ce moment, ça sert pas mal juste à peek le spawnscript...
		Do_Stuff_this_Cycle();	// Bouge et spawn les bots
		MsgQueue::Dispatch_Messages();	// Envoie tout les messages pour vérifier si on update les events
		blastP1.UPD_Blast_Shot();		// Devrais être un event global	
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
				ConsoleRender::Add_String(pauseMsg, { Find_Ctr_X((int)std::size(pauseMsg)) ,4 }, BRIGHT_WHITE, 50);			// Besoin d'un max screen size
				break;

			case CHANGE_BLAST:
				Change_Blast();		// trying stuff
				break;

			case BLAST:
				if (!blastP1.Is_Active() && !gChoiceTime)
				{
					//static Blast* blast; 		blast = &blastP1;	// da blast

					static GrdCoord grdCrd;	// Position du joueur
					grdCrd = P1.Get_Grd_Coord();

					static Link* link;	// Link se trouvant sur la position du joueur
					link = &linkGrid->link[grdCrd.c][grdCrd.r];

					bool cancelBlast = false;

					// Action Spéciale: Un transfer
					// Le Transfer à lieu quand le joueur se trouve sur un Link FREE. Si il tire dans une autre direction que le parent du Link, le Link FREE est détruit et un blast à lieu. C'est comme si on transférait le Wall
					if (link->Get_State() == LinkState::FREE && link->Get_Type() != LinkType::BLOCKER)// Un blocker empêche les transfer?
					{
						// Si on tir dans la même direction que son parent wall		
						if (StructureManager::Is_Parent_In_This_Direction(link, keyDirection))
							cancelBlast = true; // rien va se passer
						else
							DestroyChainOfWalls::Destroy_Chain_Of_Walls(grdCrd);	// On destroy le Link que l'on veut transférer  /	// ensuite on fait un tir normal
					}

					if (!cancelBlast)
						blastP1.Setup_Blast(grdCrd, keyDirection /*  TU DOIS METTRE UN BLAST TYPE ICI  */);
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
				ConsoleRender::Add_String("                         ", { Find_Ctr_X((int)std::size(pauseMsg)) ,4 });			// Besoin d'un max screen size
			}
	}
	// Faut reset l'action
	action = IDLE;
}

/*
	À Pt modifier un jour:si tu fais un transfert sur une bordure, tu détruis le wall, mais le blast ne franchis aucune distance si tu fais un transfert horizontale, la longueur maximale n'est pas limité à un wall...
*/