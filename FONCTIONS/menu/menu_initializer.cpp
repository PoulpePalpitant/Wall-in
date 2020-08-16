#pragma once

#include "menu_initializer.h"

#include "../choice/choice_time.h"
#include "../events/msg_dispatcher.h"
#include "../grid/managegrids.h"
#include "../console/sweet_cmd_console.h"

static std::string start = "Start";
static std::string stop = "Stop";

void Menu_Initializer()
{
	Resize_Grids_To_Level(gGrids, 0);	// Resize tout les grids pour ce niveau :)


	///* CREATE CHOICE_TIME!!!!*/
	//GrdCoord crd = { linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() / 2 };
	//ChoiceTime::Add_Choice(start, TXT_CONST.EMPTY, crd);					// Le joueur doit sélectionner du texte
	//ChoiceTime::Add_Choice(stop, TXT_CONST.EMPTY, { crd.c, crd.r + 7 });	// Le joueur doit sélectionner du texte
	//MsgQueue::Register(SPAWN_PLAYER);
	MsgQueue::Register(LVL_INITIALIZED);// Envoie msg que le niveau à été intialisé

}