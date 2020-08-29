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
	 


	///* CREATE CHOICE_TIME!!!!*/
	//GrdCoord crd = { linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() / 2 };
	//ChoiceTime::Add_Choice(start, TXT_CONST.EMPTY, crd);					// Le joueur doit s�lectionner du texte
	//ChoiceTime::Add_Choice(stop, TXT_CONST.EMPTY, { crd.c, crd.r + 7 });	// Le joueur doit s�lectionner du texte
	//MsgQueue::Register(SPAWN_PLAYER);
	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(LVL_INITIALIZED);// Envoie msg que le niveau � �t� intialis�

}