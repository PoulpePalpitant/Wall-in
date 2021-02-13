#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"
#include "../events/global_events/clear_all_states.h"

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
	LinkToDestroy* top = NULL; 
	int count = 0;	
};

class ChainToModify
{
	friend class ListsOfChainToModify;

	SpeedTimer timer;	// Vitesse à laquelle on détruit les murs
	
	Chain chain = {};
	Link* selectedLink = NULL;
	Link *toErase = NULL;		// Le Link à effacer quand tu détruit une chaîne de mur. On l'efface APRÈS que le mur soit effacé
	ModifyChain modification;	// L'action qui sera faite sur les éléments de la chaîne

	Wall* parentWall = NULL;	// Le mur à détruire entre deux Link
	ChainToModify* nxt = NULL;
	


	bool is_empty();
	void push(Link* link);	
	bool pop(Link*& data);	

	~ChainToModify() 
	{
		Chain* toEmpty = &chain;
		LinkToDestroy* above;

		while (toEmpty->count)
		{
			above = chain.top;
			chain.top = chain.top->below;	
			delete above;								
			chain.count--;
		}	
	}
};

// Yikes!
class ListsOfChainToModify {
	friend class StructureManager;
	friend void Clear_All_States(bool eraseLinks);	// Gros reset button

private:
	static ChainToModify* start;
	static ChainToModify* end;

	static void Add_Children_To_List(ChainToModify* chain, Link* parent);

	static void Modify_Element(ChainToModify* chain);	
	
	static void Select_Modification(ChainToModify* chain);
	static void Delete_Parents(ChainToModify* chain);	
	static void Corrupt(ChainToModify* chain);			
	static void Buff_Walls(ChainToModify* chain);		

	static void Remove_Chain(ChainToModify* &toRemove, ChainToModify* &prev);
	static void Remove_All();	// dangerous stuff!!
public:
	static bool Is_Empty();	//
	static bool annihilating;	// On est en train d'effacer tout les walls

	static void Annihilate_All_Links();	// Efface tout les murs et les links sur tout les grids
	static void Update_Chain_Modification();
	static void Add_Chain_To_Modify(GrdCoord crd = {}, Link* link = NULL, bool excludeParent = false, ModifyChain theModif = DESTROY);
};






