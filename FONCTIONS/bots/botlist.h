#pragma once

#include "bot.h"


class BotList
{
private:
	// Naviguation sur la liste de bot
	Bot* pBotStrt;	// Pointe vers le d�but de la liste de bots				� v�rifier, ces trois trucs serait suppos�ment initialis� � 0
	Bot* pBotEnd;		// Pointe vers la fin de la liste de bots
	Bot* pIter;		// L'iterator qui permet de parcouri la liste des bots
public:
	Bot* Add_Bot();					// Ajoute un bot a la liste : Retourne un pointeur vers celui-ci
	Bot* Add_Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised);					// Ajoute un bot a la liste : Retourne un pointeur vers celui-ci
	void Del_Bot(Bot* botToDel);	// Enl�ve un bot de la liste (delete)
	void CLEANSE_THEM_ALL();		// useless for now
};

extern BotList botList;	// La liste de tout les bots

