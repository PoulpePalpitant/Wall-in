#pragma once

#include "menu_initializer.h"

#include "../inputs/action_input.h"
#include "../events/msg_dispatcher.h"
#include "../grid/managegrids.h"
#include "../console/sweet_cmd_console.h"

void Menu_Initializer()
{
	gChoiceTime = true;	// Le joueur doit sélectionner du texte
	Resize_Grids_To_Level(gGrids, 0);	// Resize tout les grids pour ce niveau :)
	Set_Dflt_WND();						// Dimension de la window mon gars
	MsgQueue::Register(LVL_INITIALIZED);// Envoie msg que le niveau à été intialisé
}