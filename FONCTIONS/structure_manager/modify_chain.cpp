

#include "../time/clock.h"
#include "modify_chain.h"
#include "../UI/console_output/render_list.h"
#include "../walls/wall_drawer.h"

ChainToModify* ListsOfChainToModify::start = NULL;
ChainToModify* ListsOfChainToModify::end = NULL;
bool ListsOfChainToModify::annihilating = false;	

// Fonctions publiques du module stack
// -----------------------------------

bool ChainToModify::is_empty()
{
	return chain.top == NULL;		
}


void ChainToModify::push(Link* link)
{
	LinkToDestroy* top = new LinkToDestroy;
	chain.count++;

	if (is_empty())top->below = NULL; 	else top->below = chain.top;

	chain.top = top;
	chain.top->link = link;
}

bool ChainToModify::pop(Link*& data)
{
	data = NULL;

	while (data == NULL)
	{
		if (!is_empty())
		{
			LinkToDestroy* above = chain.top;

			data = chain.top->link;			// data devient l'item du top
			chain.top = chain.top->below;	// le top devient l'item en dessous

			delete above;			
			chain.count--;
		}
		else
			return false;
		
		if (data == NULL)
			continue; 

		if (data->Get_State() == LinkState::DEAD)		// Le link s'est fait buté avant qu'on l'aille buté!
			data = NULL;

	}	

	timer.Start_Timer(WALL_DRAW_SPEED);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ListsOfChainToModify::Add_Children_To_List(ChainToModify* chain, Link* parent)
{
	int numChild;					

	numChild = parent->numChild;

	for (int i = 0; i < numChild; i++)	// 4 children max
	{
		if (parent->pWalls[i] != NULL)
		{
			chain->push(parent->pWalls[i]->pChild);	
		}
	}
}


// Wall and Link destruction
// *************************

void ListsOfChainToModify::Add_Chain_To_Modify(GrdCoord crd, Link* link, bool excludeParent, ModifyChain theModif)
{
	ChainToModify* it;	

	if (start == NULL)
		it = start = end = new ChainToModify;
	else
		it = end = end->nxt = new ChainToModify;
	
	Link * parentLink;	// Le Link qui est connecté au premier Link à détruire

	// 2 choix pour détruire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		it->selectedLink = &linkGrid->link[crd.c][crd.r]; 
	else
		it->selectedLink = link;	

	if (excludeParent || theModif == BUFF || theModif == CORRUPT)
	{
		Add_Children_To_List(it, it->selectedLink);	 // Ajoute tout de suite ses enfants

		// Le Modifier Blocker utilise la destruction. Mais la destruction détruit aussi le link original. Pour éviter ça, on doit l'exclure, tout en enlevant le lieu qui l'uni à ses child
		if (theModif == DESTROY)
		{
			link->Unbound_All_Child(); 
		}
		// ET C'EST tout, on ne détruit pas le link
	}
	else
	{
		if (theModif == DESTROY)
		{
			if (it->selectedLink->state != LinkState::ROOT)	// un root n'a pas de parent
			{
				// Déconnecte le parent du link à détruire
				it->parentWall = it->selectedLink->pParent;
				parentLink = it->parentWall->pParent;		
				parentLink->Unbound_Wall_Child(it->parentWall);	
				Modify_Element(it);	// Pète le link original
			}
			else 
			{	
				Add_Children_To_List(it, it->selectedLink);	
				
				if(it->selectedLink->Get_Modifier() == REGULAR)	
					it->selectedLink->Deactivate_Link();	
			}
		}
	}

	it->modification = theModif;
	it->selectedLink = NULL;


 }

bool ListsOfChainToModify::Is_Empty()	
{
	if (start)
		return false;
	else
		return true;
}

void ListsOfChainToModify::Remove_Chain(ChainToModify* &toRemove, ChainToModify* &prev)	
{
	if (toRemove == start && toRemove == end)
	{
		start = end = NULL;
		delete toRemove;
		toRemove = NULL;	
	}
	else
		if (toRemove == start)
		{
			start = start->nxt;
			delete toRemove;
			toRemove = start;	
		}
		else
			if (toRemove == end)
			{
				delete toRemove;
				toRemove = prev->nxt = NULL;
				end = prev;
			}
			else
			{
				prev->nxt = toRemove->nxt;
				delete toRemove;
				toRemove = prev->nxt;
			}
}
void ListsOfChainToModify::Remove_All()
{
	ChainToModify* prev, * toRemove;

	prev = NULL;
	toRemove = start;

	while (toRemove)
	{
		Remove_Chain(toRemove,prev);	
	}

	start = end = NULL;
}

void ListsOfChainToModify::Delete_Parents(ChainToModify* chain)	
{
	chain->parentWall = chain->selectedLink->pParent;	 

	// Tous les root qui possèdent un modifiers ne seront jamais détruits...
	if (!(chain->selectedLink->Get_Modifier() != REGULAR && chain->selectedLink->Get_State() == LinkState::ROOT))
		if (chain->selectedLink->Get_Modifier() != Modifier::FORCEFIELD)	
			chain->selectedLink->Deactivate_Link();	 		


	chain->parentWall->Deactivate_Wall();		 // Désactive le mur, ensuite on attend que le mur soit effacé pour continuer l'opération			
	chain->parentWall->Set_Drawer(true);
	chain->toErase = chain->selectedLink;
}
void ListsOfChainToModify::Corrupt(ChainToModify* chain)			
{
	chain->parentWall = chain->selectedLink->pParent;	 
	
	if(chain->selectedLink->Get_State() != LinkState::FREE)
		chain->selectedLink->Convert_Modifier(CORRUPTER);	

	chain->parentWall->Set_Strength_From_Parent();				// Rend le mur weak
	chain->parentWall->Set_Drawer();					
}
void ListsOfChainToModify::Buff_Walls(ChainToModify* chain)		
{	
	chain->parentWall = chain->selectedLink->pParent;	 
	chain->parentWall->Set_Strength_From_Parent(WallType::STRONG);		 // buff le mur,ensuite on attend que le mur soit réafficher pour continuer l'opération
	chain->parentWall->Set_Drawer();	
}
void ListsOfChainToModify::Select_Modification(ChainToModify* chain)
{
	if (chain->modification == DESTROY)
		Delete_Parents(chain);			// Delete le link sélectionné, ainsi que son parent wall. 

	if (chain->modification == BUFF)
		Buff_Walls(chain);				// Buff simplement le parent wall. Le link reste inchangé

	if (chain->modification == CORRUPT)
		Corrupt(chain);					// Corromp le link et affaiblit le mur tu suite. Mais dans le fond, affiche d'abord le link corrompu et redraw ensuite le  nouveau mur
}


void ListsOfChainToModify::Modify_Element(ChainToModify* chain)
{
	Add_Children_To_List(chain, chain->selectedLink);	 

	if (chain->selectedLink->pParent)	// Il se peut que son parent soit détruit à partir d'une liste précédante
	{
		Select_Modification(chain);	
	}

	chain->selectedLink = NULL;	
}

void ListsOfChainToModify::Update_Chain_Modification()
{
	static ChainToModify* it;
	static ChainToModify* prev;
	
	prev = NULL;
	it = ListsOfChainToModify::start;

	while (it)		
	{
		if (it->parentWall)
		{
			if (it->parentWall->drawer.timer.Is_On())	// Destruction ou affichage du mur n'est pas encore terminé
			{
				prev = it;
				it = it->nxt;	
				continue;		
			}
			else
				it->parentWall = NULL;	
		}
		else
		{
			if (!it->selectedLink)			// On a pas de link de sélectionné pour la modification
			{
				if(it->modification == DESTROY)	// dumb stuff
					if (it->toErase)			// the dumbest shit
						if (it->toErase->Get_State() == LinkState::DEAD)
							it->toErase->Er_Link();	

				if (!it->pop(it->selectedLink))	
				{
					Remove_Chain(it, prev);
					continue;
				}
				
			}
			else
				while (it->timer.Tick())
					Modify_Element(it);
		}
		
		prev = it;
		it = it->nxt;	//Next chain to destroy
	}
}

void ListsOfChainToModify::Annihilate_All_Links()	// Efface tout les murs et les links sur le Grid
{
	int col;
	int row;
	WallGrid* wallGrid = NULL;


	DrawWalls::Finish_All();			// Si des walls devait être afficher/ ou effacer, ou finis ça NOW
	ListsOfChainToModify::Remove_All();

	annihilating = true;				// empêche la désactivation des links d'envoyer un msg à chaque fois que tu désactive un link

	col = linkGrid->Get_Cols();
	row = linkGrid->Get_Rows();
	for (int c = 0; c < col; c++)	// clear les links
		for (int r = 0; r < row; r++)
		{
			linkGrid->link[c][r].Deactivate_Link();
			linkGrid->link[c][r].Er_Link();
		}

	wallGrid = wallGridHor;	

	for (int i = 0; i < 2; i++)
	{
		col = wallGrid->Get_Cols();
		row = wallGrid->Get_Rows();
		for (int c = 0; c < col; c++)	
		{
			for (int r = 0; r < row; r++)
			{
				{
					wallGrid->wall[c][r].Set_Drawer(true, true);	
					wallGrid->wall[c][r].Deactivate_Wall();
				}
			}
		}

		wallGrid = wallGridVer;
	}

	annihilating = false;
}
