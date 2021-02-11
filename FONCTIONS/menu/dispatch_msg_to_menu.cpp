#pragma once 

// Tout les events
#include "events/Ev_Game_Title.h"
#include"events/Ev_Start_Game.h"
#include "menu_initializer.h"
#include "events/ev_lvl_choice.h"
#include "events/dr_tuto_choice.h"
#include "events/dr_quit_button.h"

#include "../lvls/lvl_script.h"
#include "../events/msg_dispatcher.h"
#include "dispatch_msg_to_menu.h"
#include "../inputs/action_input.h"

#include "../events/global_events/ev_update_heart.h" 
#include "../events/global_events/feedback/ev_good_job.h"

 int choosenLvl = 0;	
 
 static void Quick_STart(int lvl, bool skip)
 {
	 gCurrentLevel = lvl;
	 gSkipTutorial = skip;
	 gMenuInputs = false;

	 clrscr();
	 MsgQueue::Register(PLS_INTIALIZE_LVL);	// Start le niveau sélectionné mon gars
 }

void Dispatch_Msg_To_Menu()
{
	switch (gCurrentMsg)
	{
						
	case PLS_INTIALIZE_LVL:
		Menu_Initializer(); 
		
		// DEBUG
		//*******
		Quick_STart(1, 1);
		break;	
	
	case LVL_INITIALIZED:	
		OBS_Draw_Game_Title();
		Dr_Quit_Button();

		MsgQueue::Register(STAGE_ADVANCE);
		break;
		
	case STAGE_ADVANCE:
		if (gCurrentStage == 1)
		{
			Ev_Dr_Choose_Lvl();
		}
		else
			if (gCurrentStage == 3)
			{
				Ev_Er_Choose_Lvl();
				if(choosenLvl == 1)
					Dr_Tuto_Choice();
			}
		break;

	case PRESSED_KEY:
		if (gCurrentStage == 2)
		{
			switch (gMenuKey)	// Input de charactères
			{
			case 49:	/* Les numéros de 1 à 9 */
			case 50:	
			case 51:
				choosenLvl = gMenuKey - 48;
				if (gUnlockedLevels[choosenLvl - 1] )
				{
					//MsgQueue::Unregister_All();	// répare un bug de merde, lequel? lol EDIT: now I know. or not...
					MsgQueue::Register(STAGE_ADVANCE);
					Ev_Er_Choose_Lvl();
				}
			}
		}

		if (gCurrentStage >= 3)
		{
			if (gMenuKey == 27)				/* /* escape, retourne au choix de niveau */
			{
				if (choosenLvl == 1)
					Er_Tuto_Choice();	// Efface ce choix

				MsgQueue::Register(STAGE_ADVANCE);	// On passe au choix précédant
				gCurrentStage = 0;
			}
			else
				if (choosenLvl == 1)
				{
					if (gMenuKey == 78 || gMenuKey == 89)	 /*78 = n Pour n */ /*89 y pour yes */
					{
						if (gMenuKey == 78)						
							gSkipTutorial = true;
						else
						{
							tutoStep = 0;
						}


						OBS_Erase_Game_Title();	// Erase Title Screen
						Dr_Quit_Button(1);
						Er_Tuto_Choice();	// Efface ce choix
						gMenuInputs = false;
					}
				}
				else
				{
					gSkipTutorial = true;
					gMenuInputs = false;
					OBS_Erase_Game_Title();	// Erase Title Screen
					Dr_Quit_Button(1);

				}

			break;
		}
	}
}
