#include "items.h"


#include "../player/player.h"

ItemMeta Item::meta = {};	// info sur le groupe d'items

							/*
	LES SPAWNS DISPONIBLES SONT LESQUELLES?

	L'intervalle manager fonctionne comme suit:
	Chaque liste représente une colonne du linkgrid :											instance[3] = colonne #3 dans le grid;
	Chaque valeurs présentes dans les intervalles de ces listes sont des row du Linkgrid:		instance[colonne].start.min	= 2(row);
	Ne pas oublier que la valeur max de chaque intervalles est tjrs ingorés
	Donc pour accéder à une coord :	

	instance[5].start -> Start est un intervalle. Il contient une valeur min et max	: tout les valeurs >= à min et < max sont les rows disponibles
	instance[5].start.min = 2(row)		-> crd{5,2}
*/

//
//void Item::Set_UI()
//{
//	switch (itemType)
//	{
//	case ItemType::REGULAR:			  break;
//	case ItemType::BUFFER:		sym = 254;	clr = LIGHT_GREEN;		  break;
//	case ItemType::BLOCKER:		sym = 158; 	clr = LIGHT_RED;		  break;
//	case ItemType::CORRUPTED:	sym = 207;	clr = LIGHT_RED;		break;
//	case ItemType::COLOR_A:		sym = 176;	clr = LIGHT_YELLOW;	  break;
//	case ItemType::COLOR_B: 	sym = 176;	clr = LIGHT_AQUA;	break;
//	case ItemType::BLIND_COLOR:	sym = 176;	clr = BRIGHT_WHITE;	  break;
//	case ItemType::HEALTH:		sym = '0';	clr = LIGHT_GREEN;	  break;
//	}
//}
//
