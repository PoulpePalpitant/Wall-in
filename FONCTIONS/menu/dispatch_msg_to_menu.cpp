#pragma once 

// Tout les events
#include "events/Ev_Game_Title.h"
#include"events/Ev_Start_Game.h"
#include "menu_initializer.h"
#include "events/ev_lvl_choice.h"
#include "events/dr_skip_choice.h"

#include "../lvls/lvl_script.h"
#include "../events/msg_dispatcher.h"
#include "dispatch_msg_to_menu.h"
#include "../inputs/action_input.h"

#include "../events/global_events/ev_update_heart.h" // for testing
#include "../UI/console_output/Test.h"

 int choosenLvl = 0;	
 
 static void Quick_STart(int lvl, bool skip)
 {
	 gCurrentLevel = lvl;
	 gSkipStory = skip;
	 gMenuInputs = false;

	 clrscr();
	 MsgQueue::Register(PLS_INTIALIZE_LVL);	// Start le niveau sélectionné mon gars
 }

void Dispatch_Msg_To_Menu()
{
	// LISTE DE TOUT LES OBSERVATEURS. Les observateurs activent les events quand les conditions sont met

	switch (gCurrentMsg)
	{
						
	case PLS_INTIALIZE_LVL:
		Menu_Initializer(); 
		
		// DEBUG
		//*******
		Quick_STart(1, true);

		break;	// Initialize plein de choses
	
	case LVL_INITIALIZED:	
		OBS_Draw_Game_Title();
		MsgQueue::Register(STAGE_ADVANCE);
		break;
		
	case STAGE_ADVANCE:
		if (gCurrentStage == 1)
		{
			Ev_Dr_Choose_Lvl();
			/* test de créatio de coeurs*/
			//Ev_Test_Affichage();
			//Start_Ev_Dr_Heart(3);
			//Fill_Heart_Randomly(true);
			//Fill_Outisde_Heart(false);
		}
		else
			if (gCurrentStage == 3)
			{
				Ev_Er_Choose_Lvl();
				Dr_Skip_Story_Choice();
				//if(tempLevel == 1)
				//	Start_Ev_Dr_Heart(2); // tasety

				//Fill_Heart_Randomly(false);
				//Fill_Outisde_Heart(true);

			}
		break;

	case PRESSED_KEY:
		if (gCurrentStage == 2)
		{
			switch (gMenuKey)	// Input de charactères
			{
			case 49:	/* Les numéros de 1 à 9 */
			case 50:	
			//case 51:
			//case 52:
			//case 53:
			//case 54:
			//case 55: 
				choosenLvl = gMenuKey - 48;
				MsgQueue::Unregister_All();	// répare un bug de merde
				MsgQueue::Register(STAGE_ADVANCE);
				Ev_Er_Choose_Lvl();
				//
				//if(tempLevel == 2)
				//	Start_Ev_Dr_Heart(1);
			}
		}

		if (gCurrentStage >= 3)
		{
			if (gMenuKey == 78 || gMenuKey == 89)	 /*78 = Y Pour Yes */ /*89 n pour no */
			{
				if (gMenuKey == 78)				
					gSkipStory = true; 

				if (P1.Set_On_Grid())
					P1.Set_Position({ 6,7 });

				OBS_Erase_Game_Title();	// Erase Title Screen
				Er_Skip_Story_Choice();	// Efface ce choix
				gMenuInputs = false;
				//gCurrentLevel = choosenLvl;

				//OBS_Start_Game();		// Passe au prochain niveau
			}

			if (gMenuKey == 27)				/* /* escape, retourne au choix de niveau */
			{
				Er_Skip_Story_Choice();	// Efface ce choix

				MsgQueue::Register(STAGE_ADVANCE);	// On passe au choix précédant
				gCurrentStage = 0;
				/* erase choice
				
				*/

			}
			break;
		}
	}
	// Afficher "Start"
	// Afficher "Quit"
	// Do stuff when: "Start"
	// Do stuff when: "Quit"



}
