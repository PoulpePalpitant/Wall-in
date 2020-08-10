#pragma once

#include "bot.h"
#include "../grid/spawngrid.h"


class BotList
{
	friend class BotMove;
	/* OLDY */

private:
	// Naviguation sur la liste de bot
	//Bot* pBotStrt;	// Pointe vers le début de la liste de bots				À vérifier, ces trois trucs serait supposément initialisé à 0
	//Bot* pBotEnd;	// Pointe vers la fin de la liste de bots
public:
	//Bot* Add_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised);					// Ajoute un bot a la liste : Retourne un pointeur vers celui-ci
	//void Destroy_Bot(Bot* &botToDel, Bot*& prev);	// Enlève un bot de la liste (delete)
	//bool Empty();	// La liste est vide ou non

/* OLDY */

public:
	static Bot bot[MAX_NUM_BOTS];	// TOUS LES BOTS SONT ICI


	//int Search_In_List(int index);		// Cherche un bot correspondant à un certain index
	static int Find_Available_Bot();				// Rapport l'indice d'un bot available dans la liste
	static bool Is_Full();						// check si tout les bots sont dead
	static bool Is_Empty();					// Check si tout les bots sont désactivés
	static void Destroy_All_Bots();

};

extern BotList botList;