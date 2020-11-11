#include "ev_checkpoint.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../console/sweet_cmd_console.h"
#include "../../lvls/lvl_script.h"
#include "../../time/spawn_cycle.h"
#include "../../structure_manager/modify_chain.h"
#include "../../items/item_list.h"
#include "../../blast/mod_queue_animator.h"
#include "../../blast/mod_queue_animator_add.h"
#include "../../blast/mod_queue_animator_consume.h"
#include "../../blast/blast_modifier_queue.h"
#include "../../items/item_spw_drawer.h"
#include "../../bots/botmeta.h"
#include "../../player/player.h"
#include "feedback/ev_rainbow_borders.h"
#include "ev_spwn_player.h"
#include "ev_update_heart.h"
#include "feedback/ev_good_job.h"

static Event ev_ReachCheckpoint(Ev_Reach_Checkpoint, 2);

void Ev_Reach_Checkpoint()				 // Affiche un écran qui gratifiant		
{
	if (!ev_ReachCheckpoint.Is_Active())
	{
		gSpwBotTimer.Pause();
		MsgQueue::Register(WAIT_LAST_BOT);

		ev_ReachCheckpoint.Activate();
		ev_ReachCheckpoint.Start(0);
		ev_ReachCheckpoint.delay.Start_Timer(100000, 1, true);
	}
	else
	{
		if (!gAllBotMeta.alive && P1.Get_HP())
		{
			if (gSpawnCycleTot == LVL1_CHECKPOINT[gCurrentCheckPoints[gCurrentLevel - 1]])	// On a bel et bien reach le checkpoint
			{
				//ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				//blastP1.Clear_Blast();					 // stop and clear
				//ItemsOnGrid::Remove_All();				 // enlève tout les items spawné
				//DrawModifierQueue::addNew.Remove_All();  // empty drawer qui ajoute des mod
				//DrawModifierQueue::consume.Remove_All(); // empty le drawer qui consume des mod
				//DrawItemSpawnList::Remove_All();		 // hardcore
				//BlastModifierQueue::Reset();
				
				// Pour debug
				//gGrids.Dr_Spawngrid();

				P1.Reset_Hp_And_Heart(3);	// Restore la vie du joueur
				Clear_Map();
				Ev_Rainbow_Borders();		// fait flasher tout de manière gratifiante
				gCurrentCheckPoints[gCurrentLevel - 1]++;	// Le checkpoint est officiellement updaté
				
				if (!Are_Equal(P1.Get_Grd_Coord(), LVL1_CHECKPOINT_P1_CRD[gCurrentCheckPoints[gCurrentLevel - 1]]))	// déplace le joueur si il ne se trouve pas sur le bon spawn point
				{
					P1.Set_Position(LVL1_CHECKPOINT_P1_CRD[gCurrentCheckPoints[gCurrentLevel - 1]]);
					Set_Ev_Spawn_Player(3);
				}
				else
					P1.Dr_Player();

				blastP1.Get_Ammo_Manager().Set_Ammo_For_Checkpoint();
				gSpwBotTimer.Resume();
				gSpwBotTimer.Add_Count(5);	// Ajoute une tite pause à chaque fois que le checkpoint à été atteint!
				Ev_Good_Job();	// Félicite le joueur
				ev_ReachCheckpoint.Cancel();
			}
		}
	}
}

