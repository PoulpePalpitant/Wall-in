
#include <mutex>

#include "../time/clock.h"
#include "modify_chain.h"
#include "../UI/console_output/render_list.h"
#include "../walls/wall_drawer.h"
//#include "../player/player.h"

ChainToModify* ListsOfChainToModify::start = NULL;
ChainToModify* ListsOfChainToModify::end = NULL;
bool ListsOfChainToModify::annihilating = false;	// On est en train d'effacer tout les walls

// Fonctions publiques du module stack
// -----------------------------------

bool ChainToModify::is_empty()
{
	return chain.top == NULL;		// Si le top est vide ou plein
}


void ChainToModify::push(Link* link)
{
	LinkToDestroy* top = new LinkToDestroy;
	chain.count++;

	if (is_empty())top->below = NULL; 	else top->below = chain.top;

	chain.top = top;
	chain.top->link = link;
}

bool ChainToModify::pop(Link*& data)	// Détruit l'item sur le dessus, mais conserve la donnée en référence
{
	data = NULL;

	while (data == NULL)
	{
		if (!is_empty())
		{
			LinkToDestroy* above = chain.top;

			data = chain.top->link;		// data devient l'item du top
			chain.top = chain.top->below;	// le top devient l'item en dessous

			delete above;			// pète le(ancien) top										// pt que ça bug icite
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
	int numChild;					// Nombre de child à ajouter à la liste de destruction

	numChild = parent->numChild;

	for (int i = 0; i < numChild; i++)	// 4 children max
	{
		if (parent->pWalls[i] != NULL)/*sécurité*/
		{
			chain->push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK à la liste(le child du wall, qui est lui le child du LINK Parent)	
		}
	}
}


// Wall and Link destruction
// *************************

void ListsOfChainToModify::Add_Chain_To_Modify(GrdCoord crd, Link* link, bool excludeParent, ModifyChain theModif)
{
	ChainToModify* it;	// itérateur

	// NOUVELLE CHAIN À DESTROY
	if (start == NULL)
		it = start = end = new ChainToModify;
	else
		it = end = end->nxt = new ChainToModify;
	
	Link * parentLink;	// Le Link qui est connecté au premier Link à détruire

	// 2 choix pour détruire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		it->selectedLink = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
	else
		it->selectedLink = link;	// le premier de la liste

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
				it->parentWall = it->selectedLink->pParent;	// Le wall connectant le parent au link à modifier
				parentLink = it->parentWall->pParent;	// Le parentLink du link à modifier
				parentLink->Unbound_Wall_Child(it->parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui était le parent de la chaîne de destruction		
				Modify_Element(it);	// Pète le link original
			}
			else 
			{	// Si le premier Link est une Root			
				Add_Children_To_List(it, it->selectedLink);	 // Ajoute tout de suite ses enfants
				it->selectedLink->Deactivate_Link();	 // Et on désactive tout de suite 	
			}
		}
	}

	it->modification = theModif;
	it->selectedLink = NULL;


 }

bool ListsOfChainToModify::Is_Empty()	//
{
	if (start)
		return false;
	else
		return true;
}

void ListsOfChainToModify::Remove_Chain(ChainToModify* &toRemove, ChainToModify* &prev)	// BUG DE DELETE: Soit ici
{
	if (toRemove == start && toRemove == end)
	{
		start = end = NULL;
		delete toRemove;
		toRemove = NULL;	// safety
	}
	else
		if (toRemove == start)
		{
			start = start->nxt;
			delete toRemove;
			toRemove = start;	// Continuation
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
void ListsOfChainToModify::Remove_All()	// dangerous stuff!!
{
	ChainToModify* prev, * toRemove;

	prev = NULL;
	toRemove = start;

	//start->EMPTY();
	while (toRemove)
	{
		Remove_Chain(toRemove,prev);	// bam
	}

	start = end = NULL;
}

void ListsOfChainToModify::Delete_Parents(ChainToModify* chain)	// Détruit un élément de la chaîne ainsi que son parent wall
{
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	chain->selectedLink->Deactivate_Link();	 // Détruit le Link			
	chain->parentWall->Deactivate_Wall();		 // Désactive le mur,	ensuite on attend que le mur c'est effacé continuer l'opération			
	chain->parentWall->Set_Drawer(true);
	chain->toErase = chain->selectedLink;
}
void ListsOfChainToModify::Corrupt(ChainToModify* chain)			// Change le modifier de u link en Corrupted, et de ce fait, le wall aussi
{
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	
	// JE TESTE CECI: ne pas corrupt de free link
	if(chain->selectedLink->Get_State() != LinkState::FREE)
		chain->selectedLink->Convert_Modifier(CORRUPTER);	// corrupt le link(réaffiche aussi)

	chain->parentWall->Set_Strength_From_Parent();				// Rend le mur weak
	chain->parentWall->Set_Drawer();					// et le redraw
}
void ListsOfChainToModify::Buff_Walls(ChainToModify* chain)		// Buff les walls 
{	
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	chain->parentWall->Set_Strength_From_Parent(WallStrength::STRONG);		 // buff le mur,ensuite on attend que le mur soit réafficher pour continuer l'opération
	chain->parentWall->Set_Drawer();	// Redraw taht damn wall
}
void ListsOfChainToModify::Select_Modification(ChainToModify* chain)
{
	if (chain->modification == DESTROY)
		Delete_Parents(chain);			// Delete le link sélectionné, ainsi que son parent wall. Pour le joueur, le mur s'efface d'abord, ensuite le link se fait effacer. Il se fait effacer dans la grosse loop

	if (chain->modification == BUFF)
		Buff_Walls(chain);				// Buff simplement le parent wall. Le link reste inchangé

	if (chain->modification == CORRUPT)
		Corrupt(chain);					// Corromp le link et affaiblit le mur tu suite. Mais dans le fond, affiche d'abord le link corrompu et redraw ensuite le  nouveau mur
}


void ListsOfChainToModify::Modify_Element(ChainToModify* chain)
{
	/* check la direction ici, si tu destroy dans le sens de la ROOT, ou des CHILD*/
	// Ajout du parent
	
	// Ajout des child
	Add_Children_To_List(chain, chain->selectedLink);	 // Ajoute les enfants du Link à la liste de destruction

	if (chain->selectedLink->pParent)	// Il se peut que son parent soit détruit à partir d'une liste précédante
	{
		Select_Modification(chain);	// 
	}

	chain->selectedLink = NULL;	// we got nothing selected anymore
}

/*
	Notes sur la destruction: Il semblerait que le joueur va pouvoir  tirer sur des Links faisant partie d'une chaîne qui est en train d'être détruite
*/

void ListsOfChainToModify::Update_Chain_Modification()
{
	static ChainToModify* it;
	static ChainToModify* prev;
	
	prev = NULL;
	it = ListsOfChainToModify::start;

	while (it)		// Tant qu'on a pas parcouru tout les chaînes 
	{
		if (it->parentWall)	// Parentwall de sélectionné pour un redraw
		{
			if (it->parentWall->drawer.timer.Is_On()/* && it->parentWall->Get_State()()is bel et bien dead*/)	// Destruction ou affichage du mur n'est pas encore terminé
			{
				prev = it;
				it = it->nxt;	//Next chain to modify
				continue;		 // Le mur est désactivé dès qu'on commence à l'effacer
			}
			else
				it->parentWall = NULL;	// déselectionne le parentwall. finit le redraw
		}
		else
		{
			if (!it->selectedLink)			// On a pas de link de sélectionné pour la modification
			{
				if(it->modification == DESTROY)	// dumb stuff
					if (it->toErase) // the dumbest shit
						if (it->toErase->Get_State() == LinkState::DEAD)
							it->toErase->Clr_Link();	// Efface le link

				if (!it->pop(it->selectedLink))	// Prend un élément da liste de Link 
				{
					Remove_Chain(it, prev);
					continue;
				}
				
			}
			else
				while (it->timer.Tick())
				{
					Modify_Element(it);
				}
		}
		
		prev = it;
		it = it->nxt;	//Next chain to destroy


	// Si ya pas de link à désactivé. check si ya un wall à désactivés
	// Si non, POP
	// si ya un wall à désactivé, update la destruction
	// if Destroy_Wall()			est finit


	}
}

// Destroy wall()			Reprend ou t'en étais

void ListsOfChainToModify::Annihilate_All_Links()	// Efface tout les murs et les links sur le Grid
{
	int col;
	int row;
	WallGrid* wallGrid = NULL;

	// Enlève ceci si ça marche pas!
	ListsOfChainToModify::Remove_All(); // empty list of chain to modify/delete
	DrawWalls::Remove_All();			// cause des crash 
	//DrawWalls::Finish_All();

	annihilating = true;	// empêche la désactivation des links d'envoyer un msg à chaque fois que tu désactive un link
	 //V2 - Hard way





	col = linkGrid->Get_Cols();
	row = linkGrid->Get_Rows();
	for (int c = 0; c < col; c++)	// clear les links
		for (int r = 0; r < row; r++)
		{
			linkGrid->link[c][r].Deactivate_Link();
			linkGrid->link[c][r].Clr_Link();
		}

	wallGrid = wallGridHor;	// commence par wallgrid horizontal

	for (int i = 0; i < 2; i++)
	{
		col = wallGrid->Get_Cols();
		row = wallGrid->Get_Rows();
		for (int c = 0; c < col; c++)	// clear les walls
		{
			for (int r = 0; r < row; r++)
			{
				if (wallGrid->wall[c][r].state != WallState::DEAD)
				{
					wallGrid->wall[c][r].Set_Drawer(true, true);	// ERASE d'ABORd
					wallGrid->wall[c][r].Deactivate_Wall();	// Ensuite delete le shit
				}
			}
		}
		wallGrid = wallGridVer;	// finis par wallgrid vertical
	}


	//col = linkGrid->Get_Cols() - 1;
	//row = linkGrid->Get_Rows() - 1;

	// //V1 
	//for (int c = 0; c < col ; c++)
	//{
	//	for (int r = 0; r < row ; r++)
	//	{
	//		/* Ceci est un dumb fix rapide, car un glitch visuel fait en sorte que certains root Link ne sont pas effacé*/
	//		if (linkGrid->link[c][r].Get_State() == LinkState::ROOT)
	//		{
	//			linkGrid->link[c][r].Clr_Link();
	//		}

	//		if(linkGrid->link[c][r].Get_State() != LinkState::DEAD)
	//			Add_Chain_To_Modify({ c,r });
	//	}
	//}

	annihilating = false;
}
