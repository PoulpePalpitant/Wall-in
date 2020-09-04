

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

// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_2()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_2_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case LVL_INITIALIZED: 
		Ev_Build_Labyrinth();
		break;	

	case STAGE_ADVANCE:
		Event::Cancel_All();		// Tout les events en cours sont annulés
		//Clear_All_States();
		clrscr();

		switch (gCurrentStage)
		{
		case 1:Ev_Wake_Up_2();break;//gCurrentStage++;
		case 2://Ev_Lvl2_Training_1();break;
		case 3://Ev_Lvl2_Training_2();break;
		case 4://Ev_Lvl2_Training_3();break;
		case 5:
			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
			botList.Destroy_All_Bots();
			Ev_Dr_Day_2();
			break;

		case 6:
			// Ceci est temporaire pour débugger plus rapidement le bot script
			//P1.Set_Hp(1000);
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

			MsgQueue::Register(ENABLE_BLAST);	// quicker quick start
			MsgQueue::Register(START_BOTS); // Here they come baby
			MsgQueue::Register(ENABLE_ITEM_SPAWN); // items!
			gSkipStory = false;
			gDayStarted = true;
		}

		break;

	case PROCEED: 
		if (gCurrentStage == 5)
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
