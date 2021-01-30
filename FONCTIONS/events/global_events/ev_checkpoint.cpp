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
#include "feedback/ev_good_job.h"
#include "ev_spwn_player.h"
#include "ev_update_heart.h"
#include "../../events/global_events/feedback/ev_drain_health.h"
#include "feedback/ev_ammo_depleted.h"

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
		while (ev_ReachCheckpoint.delay.Tick())
		{
			if (ev_ReachCheckpoint.Get_Current_Step() == 2)
			{
				// Initialize le prochain puzzle et clear la map
				MsgQueue::Register(LOCK_PLAYER);	// It has to be done
				P1.Er_Player();						// Efface son char
				P1.Get_Teleporter().Remove_Teleport_Location();	// Pour pas cheater

				Init_Puzzle();

				if (gCurrentPuzzle[gCurrentLevel - 1] != NUM_PUZZLES[gCurrentLevel - 1] - 1)	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
					Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair

				MsgQueue::Register(ENABLE_BLAST);
				gSpwBotTimer.Resume();
				gSpwBotTimer.Add_Count(3);

				ev_ReachCheckpoint.Cancel();
			}
			else
				if (!gAllBotMeta.alive && P1.Get_HP())
				{
					// Nouvelle version avec plusieurs scripts
					Stop_Ev_Hp_Drain_Msg();
					Clear_Map();						// Effacer la map est satisfaisant
					P1.Dr_Player();						// doit redraw le joueur quand on fait ça
					Ev_Rainbow_Borders();				// fait flasher tout de manière gratifiante
					Ev_Good_Job();						// Félicite le joueur
					P1.Set_Hp(1);

					gCurrentPuzzle[gCurrentLevel - 1]++;// Le checkpoint est officiellement updaté
					ev_ReachCheckpoint.delay.Stop();
					ev_ReachCheckpoint.Advance(300); // Une tite pause avant de continuer!!
					MsgQueue::Register(DISABLE_BLAST);
				}
		}
	}
}

