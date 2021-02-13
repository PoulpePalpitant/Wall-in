
#include "botlist.h"
#include "botmeta.h"
#include "../grid/AllGrids.h"
#include "../events/global_events/ev_back_to_menu.h"

Bot BotList::bot[MAX_NUM_BOTS];	

int BotList::Find_Available_Bot()				
{
	if (Is_Full())
		return -1;

	for (int i = 0; i < MAX_NUM_BOTS; i++) {
		if (bot[i].Is_Dead())
			return i;
	}

	return -1;
}
bool BotList::Is_Full()
{
	return gAllBotMeta.alive == MAX_NUM_BOTS;
}
bool BotList::Is_Empty()					
{
	return !gAllBotMeta.alive;	
}


void BotList::Destroy_All_Bots()
{
	gGrids.Remove_All_Bots_From_Grid();

	for (int i = 0; i < MAX_NUM_BOTS; i++) {
		if (!bot[i].Is_Dead())
		{
			Bot::UI_Erase_Bot(&bot[i]);
			bot[i].Destroy_Bot();
			bot[i] = {};
		}
	}

	if (!gAllBotMeta.alive) 
	{
		gAllBotMeta.alive = 0;
		return;
	}
	else
	{
		Go_Back_To_Menu();
	}
}

















