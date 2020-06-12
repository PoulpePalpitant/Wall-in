
#include "botlist.h"
#include "botmeta.h"

// si �a marche pas, t'aura pt besoin de crer un obj liste
extern BotList botList = {};	// La liste de tout les bots


bool BotList::Empty()	// La liste est vide ou non
{
	return botList.pBotEnd == NULL;	// La fin est null?, da shit is empty brah
}

// Delete un bot officiellement ... Quand m�me comploqu� tout �a!
// ------------------------------------------------------------
void BotList::Destroy_Bot(Bot*& botToDel, Bot*& prev)
{
	Bot* next; next = botToDel->pNext;	// le pointeur de bottoDel va pointer vers �a � la fin

	Bot::UI_Erase_Bot(botToDel);	// efface le bot: Sert surtout si le bot sort de la bordure

	/* THAT'S AN OLDY*/
	//// Si le bot est au milieu de la liste
	//if (botToDel != pBotStrt && botToDel != pBotEnd)
	//{
	//	botToDel->pPrev->pNext = botToDel->pNext;	// Le Bot pr�c�dent pointe maintenant vers celui qui se trouvait apr�s le Delete
	//	botToDel->pNext->pPrev = botToDel->pPrev;	// Le bot suivant pointe sur le bot derri�re celui qu'on delete
	//}
	//else
	//{
	//	if (botToDel == pBotStrt && botToDel == pBotEnd)	// The Purge
	//		botToDel = pBotStrt = pBotEnd = NULL;
	//	else
	//		if (botToDel == pBotStrt)	// Si le bot �tait le premier de liste
	//		{
	//			pBotStrt = botToDel->pNext;
	//			pBotStrt->pNext->pPrev = pBotStrt;
	//			botToDel->pNext->pPrev = NULL;	// Le pointeur suivant va pointer vers NULL, car il est maintenant le nouveau D�but de la liste!
	//		}
	//		else if (botToDel == pBotEnd) // Si le bot �tait le dernier de liste
	//		{
	//			pBotEnd = botToDel->pPrev; 
	//			pBotEnd->pPrev->pNext = pBotEnd;
	//			botToDel->pPrev->pNext = NULL;	// Le pointeur pr�c�dant est maintenant le nouveau fin de la liste
	//		}
	//}

	/// yes

	if (botToDel == pBotStrt && botToDel == pBotEnd)	// 1 �l�ment dans la liste
	{
		delete botToDel;	// DELETE
		botToDel = pBotStrt = pBotEnd = NULL;
	}
	else
	{
		if (botToDel == pBotStrt)
			pBotStrt = botToDel->pNext;
		else if (botToDel == pBotEnd)
		{
			pBotEnd = prev;
			prev->pNext = NULL;
		}
		else
			prev->pNext = botToDel->pNext;	// Le Bot pr�c�dent pointe maintenant vers celui qui se trouvait apr�s le Delete

		delete botToDel;	// On delete le bot Finalement. Le cycle de la vie
		botToDel = next;	// Le pointeur du Bot va pointer vers le pr�c�dent maintenant
	}


	gBotMetaReg.Bot_Died();		// Record sa mort
}

// Ajoute un bot � la liste de bots
// --------------------------------

Bot* BotList::Add_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised) {

	if (!pBotEnd)		// Liste vide
	{
		pBotStrt = pBotEnd = new Bot(type, spGrdCrd, isBotCustomised);
	}
	else 
	{
		static Bot* prevEnd; 
		prevEnd = pBotEnd;		// Le pointeur sur le dernier de la liste(qui deviendra l'avant dernier)

		pBotEnd = pBotEnd->pNext = new Bot(type, spGrdCrd, isBotCustomised);	// Le bot ajout�, est ajout� � la fin
		prevEnd->pNext = pBotEnd;		// L'avant dernier pointe sur le dernier
		//pBotEnd->pPrev = prevEnd;		// Le dernier point sur l'avant dernier

	}
	//botEnd->next = NULL; Se fait par d�faut :O

	// On oublie pas d'update le meta
	gBotMetaReg.New_Bot();

	return pBotEnd;		// L'adresse du bot cr��
}


//// Destroy tout les bots! (sort of...)
//// ----------------------------------
//
//void BotList::CLEANSE_THEM_ALL() {		// � noter que �a d�truit juste les bots, �a enl�ve pas les spawnblock, ni l'affichage, c'est basically useless Lol
//
//	this->pIter;	// Si �a bug, utilise les "this"
//	this->pBotStrt;
//
//	while (pIter = pBotStrt) // affectation (iterator = debut) suivi du test sur la valeur de it != NULL
//	{
//		pBotStrt = pBotStrt->pNext;
//		delete pIter;
//	}
//	
//	pBotEnd = NULL;	// bonne pratique
//
//}



