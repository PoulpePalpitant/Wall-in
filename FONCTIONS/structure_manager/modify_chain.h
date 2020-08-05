#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"

// Les trois actions possibles pour la gestion des chaines de murs
enum ModifyChain
{
	DESTROY, BUFF, CORRUPT
};

// Une item du stack de link à détruire
struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};

struct Chain // une pile d'item chainés
{
	LinkToDestroy* top = NULL; // indique le dessus de la pile
	int count = 0;	// don't need
};

class ChainToModify
{
	friend class ListsOfChainToModify;

	SpeedTimer timer;	// Vitesse à laquelle on détruit les murs
	
	Chain chain;
	Link* selectedLink = NULL;
	Link *toErase = NULL;		// Le Link à effacer quand tu détruit une chaîne de mur. On l'efface APRÈS que le mur soit effacé
	ModifyChain modification;	// L'action qui sera faite sur les éléments de la chaîne

	Wall* parentWall;					// Le mur à détruire entre deux Link
	ChainToModify* nxt = NULL;
	


	bool empty();
	void push(Link* link);	// Ajoute un Link à détruire de la liste
	bool pop(Link*& data);	// Enlève un Link à détruire de la liste
};


class ListsOfChainToModify {
	friend class StructureManager;
private:
	static ChainToModify* start;
	static ChainToModify* end;


	static void Add_Children_To_List(ChainToModify* chain, Link* parent);

	static void Modify_Element(ChainToModify* chain);	// Détruit un élément de la chaîne
	
	static void Select_Modification(ChainToModify* chain);
	static void Delete_Parents(ChainToModify* chain);	// Détruit un élément de la chaîne ainsi que son parent wall
	static void Corrupt(ChainToModify* chain);			// Change le modifier de u link en Corrupted, et de ce fait, le wall aussi
	static void Buff_Walls(ChainToModify* chain);		// Buff les walls 

	static void Remove_Chain(ChainToModify* &toRemove, ChainToModify* &prev);
public:
	// Détruit la chaine de link et de mur dépendant d'un Link
	static void Annihilate_All_Links();	// Efface tout les murs et les links sur tout les grids
	static void Update_Chain_Modification();
	static void Add_Chain_To_Modify(GrdCoord crd = {}, Link* link = NULL, bool excludeParent = false, ModifyChain theModif = DESTROY);
};






