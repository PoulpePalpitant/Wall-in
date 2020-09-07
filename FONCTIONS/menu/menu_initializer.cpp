#pragma once

#include "menu_initializer.h"

#include "../choice/choice_time.h"
#include "../events/msg_dispatcher.h"
#include "../grid/managegrids.h"
#include "../console/sweet_cmd_console.h"
#include "../player/player.h"

void Menu_Initializer()
{
	P1.Set_Sym((unsigned char)197);	// it was very annoying 
	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(LVL_INITIALIZED);// Envoie msg que le niveau à été intialisé
}