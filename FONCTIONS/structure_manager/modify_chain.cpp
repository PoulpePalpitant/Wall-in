
#include <mutex>

#include "../time/clock.h"
#include "modify_chain.h"
#include "../UI/console_output/render_list.h"
#include "../walls/wall_drawer.h"
//#include "../player/player.h"

ChainToModify* ListsOfChainToModify::start = NULL;
ChainToModify* ListsOfChainToModify::end = NULL;
bool ListsOfChainToModify::annihilating = false;	// On est en train d'effacer tout les walls


//
//// LE STACK PILE
//// *************					/* va servir � manager la liste de link qu'on va devoir d�truire */
//
//// Types priv�s au module stack
//// ----------------------------
//
//// Une item du stack de link � d�truire
//struct LinkToDestroy
//{
//	Link* link = NULL; /*data*/
//	LinkToDestroy* below = NULL;
//};	
//struct Stack // une pile d'item chain�s
//{
//	LinkToDestroy* top; // indique le dessus de la pile
//	int count;	// don't need
//};
//
//static Stack S = {};	// Variable globale priv�e au module stack
//
//// Fonctions publiques du module stack
//// -----------------------------------
//
//bool empty()
//{
//	return S.top == NULL;		// Si le top est vide ou plein
//}
//
//void push(Link* link)
//{
//	LinkToDestroy* top = new LinkToDestroy;
//	S.count++;
//
//	if (empty())top->below = NULL; 	else top->below = S.top;
//
//	S.top = top;
//	S.top->link = link;
//}
//
//bool pop( Link* &data)	// D�truit l'item sur le dessus, mais conserve la donn�e en r�f�rence
//{
//	if (!empty())
//	{
//		LinkToDestroy* above = S.top;
//
//		data = S.top->link;		// data devient l'item du top
//		S.top = S.top->below;	// le top devient l'item en dessous
//
//		delete above;			// p�te le(ancien) top
//		S.count--;
//
//		return true;
//	}
//	return false;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void DestroyChainOfWalls::Add_Children_To_List(Link* parent)
//{
//	int numChild;					// Nombre de child � ajouter � la liste de destruction
//
//	numChild = parent->numChild;
//
//	for (int i = 0; i < numChild; i++)	// 4 children max
//	{
//		if (parent->pWalls[i] != NULL)/*s�curit�*/
//			push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK � la liste(le child du wall, qui est lui le child du LINK Parent)	
//	}
//}
//
//
//// Wall and Link destruction
//// *************************
//
//void DestroyChainOfWalls::Destroy_Chain_Of_Walls(GrdCoord crd, Link* link)
//{
//	Link* toDeactivate, *parentLink;	// Le Link qui est connect� au premier Link � d�truire
//	Wall* parentWall;					// Le mur � d�truire entre deux Link
//
//	// 2 choix pour d�truire: L'adresse du Link ou sa crd dans le grd de links
//	if (link == NULL)
//		toDeactivate = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
//	else
//		toDeactivate = link;	// le premier de la liste
//
//	if (toDeactivate->state != LinkState::ROOT)	// un root n'a pas de parent
//	{
//		parentWall = toDeactivate->pParent;	// Le wall connectant le parent au link � d�truire
//		parentLink = parentWall->pParent;	// Le parentLink du link � d�truire
//		parentLink->Unbound_Wall_Child(parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui �tait le parent de la cha�ne de destruction		
//		push(toDeactivate); // Ceci sera le premier �l�ment de la liste � d�truire
//	}
//	else {	// Si le premier Link est une Root
//		Add_Children_To_List(toDeactivate);	 // Ajoute tout de suite ses enfants
//		toDeactivate->Deactivate_Link();	 // Et on d�sactive
//	}
//
//	ConsoleRender::Create_Queue(100);	// Start l'animation de destruction
//
//	while (!empty())		// Tant qu'il reste des Links � d�truire
//	{
//		pop(toDeactivate);	// Prend un �l�ment da liste de Link � d�truire
//		
//		// V�rifie si ya des Kids
//		Add_Children_To_List(toDeactivate);	 // Ajoute les enfants du Link � la liste de destruction
//		parentWall = toDeactivate->pParent;	 // trouve le mur parent
//		toDeactivate->Deactivate_Link();	 // d�truit le Link				Je ne'ai pas s�par� deactivate Link et erase Link
//		parentWall->Deactivate_Wall();		 // D�sactive le mur				J'ai s�par� deactivate wall et erase wall
//		parentWall->UI_Draw_Or_Erase_Wall(true); // efface son mur on top		* alors tu draw, ou tu erase?
//		toDeactivate ->Clr_Link();		// Efface le Link		// Pourrait �tre mis � pars
//	}
//	
//	ConsoleRender::Stop_Queue();		// Finis l'animation de destruction
//
//	// Probl�me avec les animations dans ma renderlist: Je peux pas les canceller, et elles ne refl�tent pas l'�tat imm�diat du jeu. Ici, si le joueur d�cide de se d�placer sur 
//	// un link qui va �tre effacer, le joueur va �tre effac�
//}
//


//SI TOUT �A BUG EN TEMPS R�EL, VOICI CE QUE TU DEVRA FAIRE
/*
- CHANGE TA LOGIQUE DE "STACK" POUR QUE LE "POP" RETIRE LE PREMIER �L�MENT DE LA LISTE AU LIEU DU DERNIER

- CR�ER UNE NOUVELLE FONCTION QUI VA PRENDRE LA "PILE" ET L'UTILISER UNIQUEMENT POUR "EFFACER"
- CR�ER UN GESTIONNAIRE DE PILE, QUI VA PERMETTRE DE CR�ER PLUSIEURS PILES DE "� EFFACER". ET QUI VA POUVOIR EFFACER LES PILES D�S QU'ON A FINIS D'AFFICHER


*/

// Fonctions publiques du module stack
// -----------------------------------

bool ChainToModify::empty()
{
	return chain.top == NULL;		// Si le top est vide ou plein
}

void ChainToModify::push(Link* link)
{
	LinkToDestroy* top = new LinkToDestroy;
	chain.count++;

	if (empty())top->below = NULL; 	else top->below = chain.top;

	chain.top = top;
	chain.top->link = link;
}

bool ChainToModify::pop(Link*& data)	// D�truit l'item sur le dessus, mais conserve la donn�e en r�f�rence
{
	data = NULL;

	while (data == NULL)
	{
		if (!empty())
		{
			LinkToDestroy* above = chain.top;

			data = chain.top->link;		// data devient l'item du top
			chain.top = chain.top->below;	// le top devient l'item en dessous

			delete above;			// p�te le(ancien) top										// pt que �a bug icite
			chain.count--;
		}
		else
			return false;
		
		if (data == NULL)
			continue; 

		if (data->Get_State() == LinkState::DEAD)		// Le link s'est fait but� avant qu'on l'aille but�!
			data = NULL;

	}	

	timer.Start_Timer(WALL_DRAW_SPEED);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ListsOfChainToModify::Add_Children_To_List(ChainToModify* chain, Link* parent)
{
	int numChild;					// Nombre de child � ajouter � la liste de destruction

	numChild = parent->numChild;

	for (int i = 0; i < numChild; i++)	// 4 children max
	{
		if (parent->pWalls[i] != NULL)/*s�curit�*/
		{
			chain->push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK � la liste(le child du wall, qui est lui le child du LINK Parent)	
		}
	}
}


// Wall and Link destruction
// *************************

void ListsOfChainToModify::Add_Chain_To_Modify(GrdCoord crd, Link* link, bool excludeParent, ModifyChain theModif)
{
	ChainToModify* it;	// it�rateur

	// NOUVELLE CHAIN � DESTROY
	if (start == NULL)
		it = start = end = new ChainToModify;
	else
		it = end = end->nxt = new ChainToModify;
	
	Link * parentLink;	// Le Link qui est connect� au premier Link � d�truire

	// 2 choix pour d�truire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		it->selectedLink = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
	else
		it->selectedLink = link;	// le premier de la liste

	if (excludeParent || theModif == BUFF || theModif == CORRUPT)
	{
		Add_Children_To_List(it, it->selectedLink);	 // Ajoute tout de suite ses enfants

		// Le Modifier Blocker utilise la destruction. Mais la destruction d�truit aussi le link original. Pour �viter �a, on doit l'exclure, tout en enlevant le lieu qui l'uni � ses child
		if (theModif == DESTROY)
		{
			link->Unbound_All_Child(); 
		}
			
		// ET C'EST tout, on ne d�truit pas le link
	}
	else
	{
		if (theModif == DESTROY)
		{
			if (it->selectedLink->state != LinkState::ROOT)	// un root n'a pas de parent
			{
				// D�connecte le parent du link � d�truire
				it->parentWall = it->selectedLink->pParent;	// Le wall connectant le parent au link � modifier
				parentLink = it->parentWall->pParent;	// Le parentLink du link � modifier
				parentLink->Unbound_Wall_Child(it->parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui �tait le parent de la cha�ne de destruction		
				Modify_Element(it);	// P�te le link original
			}
			else 
			{	// Si le premier Link est une Root			
				Add_Children_To_List(it, it->selectedLink);	 // Ajoute tout de suite ses enfants
				it->selectedLink->Deactivate_Link();	 // Et on d�sactive tout de suite 	
			}
		}
	}

	it->modification = theModif;
	it->selectedLink = NULL;


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


void ListsOfChainToModify::Delete_Parents(ChainToModify* chain)	// D�truit un �l�ment de la cha�ne ainsi que son parent wall
{
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	chain->selectedLink->Deactivate_Link();	 // D�truit le Link			
	chain->parentWall->Deactivate_Wall();		 // D�sactive le mur,	ensuite on attend que le mur c'est effac� continuer l'op�ration			
	chain->parentWall->Set_Drawer(true);
	chain->toErase = chain->selectedLink;
}
void ListsOfChainToModify::Corrupt(ChainToModify* chain)			// Change le modifier de u link en Corrupted, et de ce fait, le wall aussi
{
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	
	// JE TESTE CECI: ne pas corrupt de free link
	if(chain->selectedLink->Get_State() != LinkState::FREE)
		chain->selectedLink->Convert_Modifier(CORRUPTER);	// corrupt le link(r�affiche aussi)

	chain->parentWall->Set_Strength_From_Parent();				// Rend le mur weak
	chain->parentWall->Set_Drawer();					// et le redraw
}
void ListsOfChainToModify::Buff_Walls(ChainToModify* chain)		// Buff les walls 
{	
	chain->parentWall = chain->selectedLink->pParent;	 // trouve le mur parent
	chain->parentWall->Set_Strength_From_Parent(WallStrength::STRONG);		 // buff le mur,ensuite on attend que le mur soit r�afficher pour continuer l'op�ration
	chain->parentWall->Set_Drawer();	// Redraw taht damn wall
}
void ListsOfChainToModify::Select_Modification(ChainToModify* chain)
{
	if (chain->modification == DESTROY)
		Delete_Parents(chain);			// Delete le link s�lectionn�, ainsi que son parent wall. Pour le joueur, le mur s'efface d'abord, ensuite le link se fait effacer. Il se fait effacer dans la grosse loop

	if (chain->modification == BUFF)
		Buff_Walls(chain);				// Buff simplement le parent wall. Le link reste inchang�

	if (chain->modification == CORRUPT)
		Corrupt(chain);					// Corromp le link et affaiblit le mur tu suite. Mais dans le fond, affiche d'abord le link corrompu et redraw ensuite le  nouveau mur
}


void ListsOfChainToModify::Modify_Element(ChainToModify* chain)
{
	/* check la direction ici, si tu destroy dans le sens de la ROOT, ou des CHILD*/
	// Ajout du parent
	
	// Ajout des child
	Add_Children_To_List(chain, chain->selectedLink);	 // Ajoute les enfants du Link � la liste de destruction

	if (chain->selectedLink->pParent)	// Il se peut que son parent soit d�truit � partir d'une liste pr�c�dante
	{
		Select_Modification(chain);	// 
	}

	chain->selectedLink = NULL;	// we got nothing selected anymore
}

/*
	Notes sur la destruction: Il semblerait que le joueur va pouvoir  tirer sur des Links faisant partie d'une cha�ne qui est en train d'�tre d�truite
*/

void ListsOfChainToModify::Update_Chain_Modification()
{
	static ChainToModify* it;
	static ChainToModify* prev;
	
	prev = NULL;
	it = start;

	while (it)		// Tant qu'on a pas parcouru tout les cha�nes 
	{
		if (it->parentWall)	// Parentwall de s�lectionn� pour un redraw
		{
			if (it->parentWall->drawer.timer.Is_On()/* && it->parentWall->Get_State()()is bel et bien dead*/)	// Destruction ou affichage du mur n'est pas encore termin�
			{
				prev = it;
				it = it->nxt;	//Next chain to modify
				continue;		 // Le mur est d�sactiv� d�s qu'on commence � l'effacer
			}
			else
				it->parentWall = NULL;	// d�selectionne le parentwall. finit le redraw
		}
		else
		{
			if (!it->selectedLink)			// On a pas de link de s�lectionn� pour la modification
			{
				if(it->modification == DESTROY)	// dumb stuff
					if (it->toErase) // the dumbest shit
						if (it->toErase->Get_State() == LinkState::DEAD)
							it->toErase->Clr_Link();	// Efface le link

				if (!it->pop(it->selectedLink))	// Prend un �l�ment da liste de Link 
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


	// Si ya pas de link � d�sactiv�. check si ya un wall � d�sactiv�s
	// Si non, POP
	// si ya un wall � d�sactiv�, update la destruction
	// if Destroy_Wall()			est finit


	}
}

// Destroy wall()			Reprend ou t'en �tais

void ListsOfChainToModify::Annihilate_All_Links()	// Efface tout les murs et les links sur le Grid
{
	annihilating = true;

	int col = linkGrid->Get_Cols();
	int row = linkGrid->Get_Rows();

	for (int c = 0; c < col ; c++)
	{
		for (int r = 0; r < row ; r++)
		{
			/* Ceci est un dumb fix rapide, car un glitch visuel fait en sorte que certains root Link ne sont pas effac�*/
			if (linkGrid->link[c][r].Get_State() == LinkState::ROOT)
			{
				linkGrid->link[c][r].Clr_Link();
			}

			if(linkGrid->link[c][r].Get_State() != LinkState::DEAD)
				Add_Chain_To_Modify({ c,r });
		}
	}

	annihilating = false;
}
