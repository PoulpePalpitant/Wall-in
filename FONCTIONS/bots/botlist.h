#pragma once

#include "bot.h"
#include "../grid/spawngrid.h"


class BotList
{
	friend class BotMove;

public:
	static Bot bot[MAX_NUM_BOTS];	// TOUS LES BOTS SONT ICI


	static int Find_Available_Bot();		// Rapport l'indice d'un bot available dans la liste
	static bool Is_Full();					
	static bool Is_Empty();					
	static void Destroy_All_Bots();

};

extern BotList botList;