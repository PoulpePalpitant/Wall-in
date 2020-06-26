#pragma once 

// Tout les events
#include "events/Ev_Game_Title.h"
#include"events/Ev_Start_Game.h"
#include "menu_initializer.h"



#include "../events/msg_dispatcher.h"
#include "dispatch_msg_to_menu.h"

void Dispatch_Msg_To_Menu()
{
	// LISTE DE TOUT LES OBSERVATEURS. Les observateurs activent les events quand les conditions sont met

	switch (gCurrentMsg)
	{
						
	case PLS_INTIALIZE_LVL:Menu_Initializer(); break;	// Initialize plein de choses
	
	case LVL_INITIALIZED:	
		OBS_Draw_Game_Title();
		break;
		
	case LVL_ENDED:		
		break;

	case PRESSED_ENTER: 
		OBS_Erase_Game_Title();	// Erase Title Screen
		OBS_Start_Game();		// Passe au prochain niveau
		break;
	
	}
	
	// Afficher "Start"
	// Afficher "Quit"
	// Do stuff when: "Start"
	// Do stuff when: "Quit"



}
