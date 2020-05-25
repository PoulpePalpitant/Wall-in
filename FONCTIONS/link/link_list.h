#pragma once

#include "link.h"


class LinkList
{
private:
	// Naviguation sur la liste de bot
	Link* pBotStrt;	// Pointe vers le début de la liste de bots				À vérifier, ces trois trucs serait supposément initialisé à 0
	Link* pBotEnd;		// Pointe vers la fin de la liste de bots
	Link* pIter;		// L'iterator qui permet de parcouri la liste des bots
public:
	Link* Add_Link();					// Ajoute un bot a la liste : Retourne un pointeur vers celui-ci
	void Del_Link(Link* botToDel);	// Enlève un bot de la liste (delete)
};

extern LinkList linkList;	// La liste de tout les bots

