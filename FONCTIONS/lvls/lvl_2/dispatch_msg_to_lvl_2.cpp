

#include "dispatch_msg_to_lvl_2.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_2_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"
#include "../../time/spawn_cycle.h"

/* Level  events !*/
#include "../../events/global_events/ev_update_heart.h"
#include "events/ev_build_labyrinth.h"
#include "events/ev_lvl2_training.h"
#include "events/ev_lvl2_training_1.h"
#include "events/ev_lvl2_training_2.h"
#include "events/ev_lvl2_training_3.h"

/* Msg events*/
#include "msg_events/ev_day_2.h"
#include "msg_events/ev_waking_up_2.h"


// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"
#include "../../grid/managegrids.h"
#include "../../items/item_spawner.h"

// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_2()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_2_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case STAGE_ADVANCE:
		if (gCurrentStage < 6)
		{
			Event::Cancel_All();		// Tout les events en cours sont annulés
			clrscr();
		}
		switch (gCurrentStage)
		{
		case 1:Ev_Wake_Up_2();break;//gCurrentStage++;
		case 2:Ev_Lvl2_Training();break;
		case 3:Ev_Lvl2_Training_1();break;
		case 4:Ev_Lvl2_Training_2();break;
		case 5:Ev_Lvl2_Training_3();break;	// L'inversion de 3 et 2 n'est pas une erreur. Or is it?
		case 6: /*gCurrentStage++;*/	// TEMP
			//ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
			//botList.Destroy_All_Bots();

			Clear_All_States(true, false);	// Pour resize le grid. Tu va devoir attendre 1 loop lol. ou plus maintenant
			Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage);	// PEUT PT CCAUSÉ DES BUGS SI NON TESTÉ
			Ev_Dr_Day_2();
			break;

		case 7:
			P1.Set_Hp(3);
			if (gSkipStory)
			{
				/*safety*/
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				botList.Destroy_All_Bots();
				P1.Set_Position({ 6,6 });

				if (gCurrentCheckPoints[gCurrentLevel + 1] == 0)	// Si le checkpoint actuel est autre que ZÉRO
				{
					P1.Er_Player();
					Just_Dr_Map_Borders();
					Ev_Progress_Bar();
					MsgQueue::Register(SPAWN_PLAYER);
				}
				else
				{
					Ev_Progress_Bar();	// Besoin d'une version FASTER qui élimine ce qui à été fait avant
					P1.Dr_Player();
					MsgQueue::Register(FREE_PLAYER);
				}
				Just_Dr_Heart();
				//Ev_Dr_Heart();
			}

			// Il va y avoir quelques items sur la map déjà :)
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITE{ 3,3 }MS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			// c'est trop hard xD

			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6,4 }, false, true);
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITE{ 3,3 }MS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 


			MsgQueue::Register(ENABLE_BLAST);	// quicker quick start
			MsgQueue::Register(START_BOTS); // Here they come baby
			gSkipStory = false;
			gDayStarted = true;
			break;
		}

		break;

	case LOAD_CHECKPOINT:						// Restart le level, met en ajustant le Checkpoint
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		clrscr();
		gSpawnCycleTot = Get_Lvl_Checkpoint();	// Le lvl va commencer à ce point dans le script
		break;

	case PROCEED: 
		if (gCurrentStage == 7)	// Le stage ou à lieu le main game
		{
			gCurrentCheckPoints[gCurrentLevel - 1] = 0;	// Restart le checkpoint
			MsgQueue::Register(PLS_INTIALIZE_LVL);
			clrscr();
			
			if (P1.Get_State() != DEAD)	// hey, Niveau suivant!!
			{
				gCurrentStage = 0;
				gCurrentLevel = 3;
				Ev_Thks_For_Playing();
			}
		}
		else
			MsgQueue::Register(STAGE_ADVANCE);
		break;	

		/* Items*/
	case ITEM_PICKUP:
		if (gCurrentStage <= 1)
		{
			break;break;
		}
		break;
	}
}
