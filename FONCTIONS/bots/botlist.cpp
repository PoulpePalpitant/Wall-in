
#include "botlist.h"
#include "botmeta.h"

// si ça marche pas, t'aura pt besoin de crer un obj liste
extern BotList botList = {};	// La liste de tout les bots


// Delete un bot officiellement ... Quand même comploqué tout ça!
// ------------------------------------------------------------
void BotList::Del_Bot(Bot * botToDel)
{

	// Utilise un destructor à la place?
	//delete botToDel->spwnWarning;	// Doit à tout prix détruire le spawn warning AVANT de détruire le bot

	//if (botToDel == botStrt && botToDel == botEnd)
	//	delete botToDel;
	//else
	//{
	//	if (botToDel == botStrt)			// Si le bot était le premier de liste
	//		botToDel->next->prev = NULL;	// Le pointeur suivant va pointer vers NULL, car il est maintenant le nouveau DÉbut de la liste!
	//	else
	//		if (botToDel == botEnd)				// Si le bot était le dernier de liste
	//			botToDel->prev->next = NULL;	// Le pointeur précédant est maintenant le nouveau fin de la liste
	//		else
	//		{
	//			botToDel->prev->next = botToDel->next;	// Le Bot précédent pointe maintenant vers celui qui se trouvait après le Delete
	//			botToDel->next->prev = botToDel->prev;	// Le bot suivant pointe sur le bot derrière celui qu'on delete
	//		}
	//} // delete botToDel;			// Version un peu plus efficace? mais moins lisible


	// Si le bot est au milieu de la liste
	if (botToDel != botStrt && botToDel != botEnd)
	{
		botToDel->prev->next = botToDel->next;	// Le Bot précédent pointe maintenant vers celui qui se trouvait après le Delete
		botToDel->next->prev = botToDel->prev;	// Le bot suivant pointe sur le bot derrière celui qu'on delete
	}
	else
	{	// Si le bot était le premier de liste
		if (botToDel == botStrt)
			botToDel->next->prev = NULL;	// Le pointeur suivant va pointer vers NULL, car il est maintenant le nouveau DÉbut de la liste!

		// Si le bot était le dernier de liste
		if (botToDel == botEnd)
			botToDel->prev->next = NULL;	// Le pointeur précédant est maintenant le nouveau fin de la liste
	}
	
	
	delete botToDel;		// On delete le bot Finalement. Le cycle de la vie

	gBotMetaReg.Bot_Died();		// Record sa mort
}

// Ajoute un bot à la liste de bots
// --------------------------------

Bot* BotList::Add_Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised) {

	if (!botEnd)		// Liste vide
	{
		botStrt = botEnd = new Bot(type, spGrdCrd, isBotCustomised);
	}
	else 
	{
		static Bot* prevEnd; prevEnd = botEnd;		// Le pointeur sur le dernier de la liste(qui deviendra l'avant dernier)

		botEnd = botEnd->next = new Bot(type, spGrdCrd, isBotCustomised);	// Le bot ajouté, est ajouté à la fin
		botEnd->prev = prevEnd;		// Le dernier point sur l'avant dernier
		prevEnd->next = botEnd;		// L'avant dernier pointe sur le dernier

	}
	//botEnd->next = NULL; Se fait par défaut :O

	// On oublie pas d'update le meta
	gBotMetaReg.New_Bot();

	return botEnd;		// L'adresse du bot créé
}
// Destroy tout les bots! (sort of...)
// ----------------------------------

void BotList::CLEANSE_THEM_ALL() {		// À noter que ça détruit juste les bots, ça enlève pas les spawnblock, ni l'affichage, c'est basically useless Lol

	this->iter;	// Si ça bug, utilise les "this"
	this->botStrt;

	while (iter = botStrt) // affectation (iterator = debut) suivi du test sur la valeur de it != NULL
	{
		botStrt = botStrt->next;
		delete iter;
	}
	
	botEnd = NULL;	// bonne pratique

}



