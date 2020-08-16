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

static int tempLevel = 0;

void Dispatch_Msg_To_Menu()
{
	// LISTE DE TOUT LES OBSERVATEURS. Les observateurs activent les events quand les conditions sont met

	switch (gCurrentMsg)
	{
						
	case PLS_INTIALIZE_LVL:Menu_Initializer(); break;	// Initialize plein de choses
	
	case LVL_INITIALIZED:	
		OBS_Draw_Game_Title();
		MsgQueue::Register(STAGE_ADVANCE);
		break;
		
	case STAGE_ADVANCE:
		if (gCurrentStage == 1)
		{
			Ev_Dr_Choose_Lvl();
			MsgQueue::Register(STAGE_ADVANCE);
		}
		else
			if (gCurrentStage == 3)
			{
				Ev_Er_Choose_Lvl();
				Dr_Skip_Story_Choice();
			}

	case LVL_ENDED:		
		break;

	case PRESSED_KEY:
		if (gCurrentStage == 2)
		{
			switch (gMenuKey)	// Input de charact�res
			{
			case 49:	/* Les num�ros de 1 � 9 */
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55: 
				tempLevel = gMenuKey - 48;
				Ev_Er_Choose_Lvl();
				MsgQueue::Unregister_All();	// r�pare un bug de merde
				MsgQueue::Register(STAGE_ADVANCE);
			}
		}

		if (gCurrentStage >= 3)
		{
			if (gMenuKey == 89 || gMenuKey == 78)	 /*78 = Y Pour Yes */
			{
				if (gMenuKey == 78)				/* n pour no */
					gSkipStory = true; 

				OBS_Erase_Game_Title();	// Erase Title Screen
				Er_Skip_Story_Choice();	// Efface ce choix
				gMenuInputs = false;

				gCurrentLevel = tempLevel;
				MsgQueue::Register(PLS_INTIALIZE_LVL);	// Start le niveau s�lectionn� mon gars
				//OBS_Start_Game();		// Passe au prochain niveau
			}

			if (gMenuKey == 27)				/* /* escape, retourne au choix de niveau */
			{
				Er_Skip_Story_Choice();	// Efface ce choix

				MsgQueue::Register(STAGE_ADVANCE);	// On passe au choix pr�c�dant
				gCurrentStage = 0;
				/* erase choice
				
				*/

			}
		}
	}
	
	// Afficher "Start"
	// Afficher "Quit"
	// Do stuff when: "Start"
	// Do stuff when: "Quit"



}
