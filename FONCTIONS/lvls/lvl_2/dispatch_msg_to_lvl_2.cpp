

#include "dispatch_msg_to_lvl_2.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_2_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"

/* Level  events !*/
#include "../../events/global_events/ev_update_heart.h"
#include "events/ev_build_labyrinth.h"
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
		case 2:Ev_Lvl2_Training_1();break;
		case 3:Ev_Lvl2_Training_3();break;	// L'inversion de 3 et 2 n'est pas une erreur. 
		case 4:Ev_Lvl2_Training_2();break;
		case 5: /*gCurrentStage++;*/	// TEMP
			//ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
			//botList.Destroy_All_Bots();

			Clear_All_States(true, false);	// Pour resize le grid. Tu va devoir attendre 1 loop lol. ou plus maintenant
			Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage);	// PEUT PT CCAUSÉ DES BUGS SI NON TESTÉ
			Ev_Dr_Day_2();
			break;

		case 6:
			P1.Set_Hp(3);

			if (gSkipStory)
			{
				/*safety*/
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				botList.Destroy_All_Bots();

				P1.Set_Position({ 6,6 });
				P1.Er_Player();
				MsgQueue::Register(SPAWN_PLAYER);
				Just_Dr_Map_Borders();
				Just_Dr_Heart();
				Ev_Progress_Bar();
			}

			// Il va y avoir quelques items sur la map déjà :)
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITE{ 3,3 }MS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			// c'est trop hard xD

			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,4 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 10,10 }, false, true);
			//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 10,10 }, false, true);
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITE{ 3,3 }MS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 


			MsgQueue::Register(ENABLE_BLAST);	// quicker quick start
			MsgQueue::Register(START_BOTS); // Here they come baby
			MsgQueue::Register(ENABLE_ITEM_SPAWN); // items!
			gSkipStory = false;
			gDayStarted = true;
			break;
		}

		break;

	case PROCEED: 
		if (gCurrentStage == 6)	// Le stage ou à lieu le main game
		{
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
