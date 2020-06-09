#pragma once

#include "bot.h"
#include "../grid/spawngrid.h"

class BotList
{
friend class BotMove;

private:
	// Naviguation sur la liste de bot
	Bot* pBotStrt;	// Pointe vers le d�but de la liste de bots				� v�rifier, ces trois trucs serait suppos�ment initialis� � 0
	Bot* pBotEnd;	// Pointe vers la fin de la liste de bots
public:
	Bot* Add_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised);					// Ajoute un bot a la liste : Retourne un pointeur vers celui-ci
	void Destroy_Bot(Bot* &botToDel, Bot*& prev);	// Enl�ve un bot de la liste (delete)
	bool Empty();	// La liste est vide ou non
};

extern BotList botList;	// La liste de tout les bots

