
#include "botlist.h"
#include "botmeta.h"
#include "../grid/AllGrids.h"

Bot BotList::bot[MAX_NUM_BOTS];	// LISTE DE TOUT LES BOTS


//int Search_In_List(int index)		// Cherche un bot correspondant à un certain index
//{
//	for (int i = 0; i < MAX_NUM_BOTS; i++)
//	{
//		if???
//	}
//}
int BotList::Find_Available_Bot()				// Rapport l'indice d'un bot available dans la liste
{
	if (Is_Full())
		return -1;

	for (int i = 0; i < MAX_NUM_BOTS; i++) {
		if (bot[i].Is_Dead())
			return i;
	}

	return -1;
}
bool BotList::Is_Full()						// check si tout les bots sont dead
{
	return gAllBotMeta.alive == MAX_NUM_BOTS;
}
bool BotList::Is_Empty()					// Check si tout les bots sont désactivés
{
	return !gAllBotMeta.alive;	// Si aucun n'est alive!
}


void BotList::Destroy_All_Bots()
{
	gGrids.Remove_All_Bots_From_Grid();	// gotta remove them from the grid 

	for (int i = 0; i < MAX_NUM_BOTS; i++) {
		if (!bot[i].Is_Dead())
		{
			Bot::UI_Erase_Bot(&bot[i]);// enlève
			bot[i].Destroy_Bot();
			bot[i] = {};
		}
	}

	if (!gAllBotMeta.alive) // no more bots
	{
		gAllBotMeta.alive = 0;
		return;
	}
	else
		throw "This Shit ain't working";
}





















//
//
////
////// si ça marche pas, t'aura pt besoin de crer un obj liste
////extern BotList botList = {};	// La liste de tout les bots
////
////
////bool BotList::Empty()	// La liste est vide ou non
////{
////	return botList.pBotEnd == NULL;	// La fin est null?, da shit is empty brah
////}
////
////// Delete un bot officiellement ... Quand même comploqué tout ça!
////// ------------------------------------------------------------
////void BotList::Destroy_Bot(Bot*& botToDel, Bot*& prev)
////{
////	Bot* next; next = botToDel->pNext;	// le pointeur de bottoDel va pointer vers ça à la fin
////
////	Bot::UI_Erase_Bot(botToDel);	// efface le bot: Sert surtout si le bot sort de la bordure
////
////	/* THAT'S AN OLDY*/
////
////	if (botToDel == pBotStrt && botToDel == pBotEnd)	// 1 élément dans la liste
////	{
////		delete botToDel;	// DELETE
////		botToDel = pBotStrt = pBotEnd = NULL;
////	}
////	else
////	{
////		if (botToDel == pBotStrt)
////			pBotStrt = botToDel->pNext;
////		else if (botToDel == pBotEnd)
////		{
////			pBotEnd = prev;
////			prev->pNext = NULL;
////		}
////		else
////			prev->pNext = botToDel->pNext;	// Le Bot précédent pointe maintenant vers celui qui se trouvait après le Delete
////
////		delete botToDel;	// On delete le bot Finalement. Le cycle de la vie
////		botToDel = next;	// Le pointeur du Bot va pointer vers le précédent maintenant
////	}
////
////
////	gAllBotMeta.Bot_Died();		// Record sa mort
////}
////
////// Ajoute un bot à la liste de bots
////// --------------------------------
////
////Bot* BotList::Add_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised) {
////
////	if (!pBotEnd)		// Liste vide
////	{
////		pBotStrt = pBotEnd = new Bot(type, spGrdCrd, isBotCustomised);
////	}
////	else 
////	{
////		static Bot* prevEnd; 
////		prevEnd = pBotEnd;		// Le pointeur sur le dernier de la liste(qui deviendra l'avant dernier)
////
////		pBotEnd = pBotEnd->pNext = new Bot(type, spGrdCrd, isBotCustomised);	// Le bot ajouté, est ajouté à la fin
////		prevEnd->pNext = pBotEnd;		// L'avant dernier pointe sur le dernier
////		//pBotEnd->pPrev = prevEnd;		// Le dernier point sur l'avant dernier
////
////	}
////	//botEnd->next = NULL; Se fait par défaut :O
////
////	// On oublie pas d'update le meta
////	gAllBotMeta.New_Bot();
////
////	return pBotEnd;		// L'adresse du bot créé
////}
//
//
////  J'ABANDONNE LA LISTE DE BOTS

