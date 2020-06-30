
#include <mutex>

#include "../time/clock.h"
#include "destroy_chain.h"
#include "../UI/console_output/render_list.h"
//#include "../player/player.h"

//
//// LE STACK PILE
//// *************					/* va servir à manager la liste de link qu'on va devoir détruire */
//
//// Types privés au module stack
//// ----------------------------
//
//// Une item du stack de link à détruire
//struct LinkToDestroy
//{
//	Link* link = NULL; /*data*/
//	LinkToDestroy* below = NULL;
//};	
//struct Stack // une pile d'item chainés
//{
//	LinkToDestroy* top; // indique le dessus de la pile
//	int count;	// don't need
//};
//
//static Stack S = {};	// Variable globale privée au module stack
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
//bool pop( Link* &data)	// Détruit l'item sur le dessus, mais conserve la donnée en référence
//{
//	if (!empty())
//	{
//		LinkToDestroy* above = S.top;
//
//		data = S.top->link;		// data devient l'item du top
//		S.top = S.top->below;	// le top devient l'item en dessous
//
//		delete above;			// pète le(ancien) top
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
//	int numChild;					// Nombre de child à ajouter à la liste de destruction
//
//	numChild = parent->numChild;
//
//	for (int i = 0; i < numChild; i++)	// 4 children max
//	{
//		if (parent->pWalls[i] != NULL)/*sécurité*/
//			push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK à la liste(le child du wall, qui est lui le child du LINK Parent)	
//	}
//}
//
//
//// Wall and Link destruction
//// *************************
//
//void DestroyChainOfWalls::Destroy_Chain_Of_Walls(GrdCoord crd, Link* link)
//{
//	Link* toDeactivate, *parentLink;	// Le Link qui est connecté au premier Link à détruire
//	Wall* parentWall;					// Le mur à détruire entre deux Link
//
//	// 2 choix pour détruire: L'adresse du Link ou sa crd dans le grd de links
//	if (link == NULL)
//		toDeactivate = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
//	else
//		toDeactivate = link;	// le premier de la liste
//
//	if (toDeactivate->state != LinkState::ROOT)	// un root n'a pas de parent
//	{
//		parentWall = toDeactivate->pParent;	// Le wall connectant le parent au link à détruire
//		parentLink = parentWall->pParent;	// Le parentLink du link à détruire
//		parentLink->Unbound_Wall_Child(parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui était le parent de la chaîne de destruction		
//		push(toDeactivate); // Ceci sera le premier élément de la liste à détruire
//	}
//	else {	// Si le premier Link est une Root
//		Add_Children_To_List(toDeactivate);	 // Ajoute tout de suite ses enfants
//		toDeactivate->Deactivate_Link();	 // Et on désactive
//	}
//
//	ConsoleRender::Create_Queue(100);	// Start l'animation de destruction
//
//	while (!empty())		// Tant qu'il reste des Links à détruire
//	{
//		pop(toDeactivate);	// Prend un élément da liste de Link à détruire
//		
//		// Vérifie si ya des Kids
//		Add_Children_To_List(toDeactivate);	 // Ajoute les enfants du Link à la liste de destruction
//		parentWall = toDeactivate->pParent;	 // trouve le mur parent
//		toDeactivate->Deactivate_Link();	 // détruit le Link				Je ne'ai pas séparé deactivate Link et erase Link
//		parentWall->Deactivate_Wall();		 // Désactive le mur				J'ai séparé deactivate wall et erase wall
//		parentWall->UI_Draw_Or_Erase_Wall(true); // efface son mur on top		* alors tu draw, ou tu erase?
//		toDeactivate ->Clr_Link();		// Efface le Link		// Pourrait être mis à pars
//	}
//	
//	ConsoleRender::Stop_Queue();		// Finis l'animation de destruction
//
//	// Problème avec les animations dans ma renderlist: Je peux pas les canceller, et elles ne reflètent pas l'état immédiat du jeu. Ici, si le joueur décide de se déplacer sur 
//	// un link qui va être effacer, le joueur va être effacé
//}
//


//SI TOUT ÇA BUG EN TEMPS RÉEL, VOICI CE QUE TU DEVRA FAIRE
/*
- CHANGE TA LOGIQUE DE "STACK" POUR QUE LE "POP" RETIRE LE PREMIER ÉLÉMENT DE LA LISTE AU LIEU DU DERNIER

- CRÉER UNE NOUVELLE FONCTION QUI VA PRENDRE LA "PILE" ET L'UTILISER UNIQUEMENT POUR "EFFACER"
- CRÉER UN GESTIONNAIRE DE PILE, QUI VA PERMETTRE DE CRÉER PLUSIEURS PILES DE "À EFFACER". ET QUI VA POUVOIR EFFACER LES PILES DÈS QU'ON A FINIS D'AFFICHER


*/



// LE STACK PILE
// *************					/* va servir à manager la liste de link qu'on va devoir détruire */

// Types privés au module stack
// ----------------------------

// Une item du stack de link à détruire
struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};

struct Chain // une pile d'item chainés
{
	LinkToDestroy* top; // indique le dessus de la pile
	int count;	// don't need
};


// Fonctions publiques du module stack
// -----------------------------------

bool Chains_To_Destroy::empty()
{
	return chain.top == NULL;		// Si le top est vide ou plein
}

void Chains_To_Destroy::push(Link* link)
{
	LinkToDestroy* top = new LinkToDestroy;
	chain.count++;

	if (empty())top->below = NULL; 	else top->below = chain.top;

	chain.top = top;
	chain.top->link = link;
}

bool Chains_To_Destroy::pop(Link*& data)	// Détruit l'item sur le dessus, mais conserve la donnée en référence
{
	if (!empty())
	{
		LinkToDestroy* above = chain.top;

		data = chain.top->link;		// data devient l'item du top
		chain.top = chain.top->below;	// le top devient l'item en dessous

		delete above;			// pète le(ancien) top
		chain.count--;

		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DestroyChainOfWalls::Add_Children_To_List(Link* parent)
{
	int numChild;					// Nombre de child à ajouter à la liste de destruction

	numChild = parent->numChild;

	for (int i = 0; i < numChild; i++)	// 4 children max
	{
		if (parent->pWalls[i] != NULL)/*sécurité*/
			push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK à la liste(le child du wall, qui est lui le child du LINK Parent)	
	}
}


// Wall and Link destruction
// *************************

void DestroyChainOfWalls::Destroy_Chain_Of_Walls(GrdCoord crd, Link* link)
{
	Link* toDeactivate, * parentLink;	// Le Link qui est connecté au premier Link à détruire
	Wall* parentWall;					// Le mur à détruire entre deux Link

	// 2 choix pour détruire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		toDeactivate = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
	else
		toDeactivate = link;	// le premier de la liste

	if (toDeactivate->state != LinkState::ROOT)	// un root n'a pas de parent
	{
		parentWall = toDeactivate->pParent;	// Le wall connectant le parent au link à détruire
		parentLink = parentWall->pParent;	// Le parentLink du link à détruire
		parentLink->Unbound_Wall_Child(parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui était le parent de la chaîne de destruction		
		push(toDeactivate); // Ceci sera le premier élément de la liste à détruire
	}
	else {	// Si le premier Link est une Root
		Add_Children_To_List(toDeactivate);	 // Ajoute tout de suite ses enfants
		toDeactivate->Deactivate_Link();	 // Et on désactive
	}

	ConsoleRender::Create_Queue(100);	// Start l'animation de destruction

	while (!empty())		// Tant qu'il reste des Links à détruire
	{
		pop(toDeactivate);	// Prend un élément da liste de Link à détruire

		// Vérifie si ya des Kids
		Add_Children_To_List(toDeactivate);	 // Ajoute les enfants du Link à la liste de destruction
		parentWall = toDeactivate->pParent;	 // trouve le mur parent
		toDeactivate->Deactivate_Link();	 // détruit le Link				Je ne'ai pas séparé deactivate Link et erase Link
		parentWall->Deactivate_Wall();		 // Désactive le mur				J'ai séparé deactivate wall et erase wall
		parentWall->UI_Draw_Or_Erase_Wall(true); // efface son mur on top		* alors tu draw, ou tu erase?
		toDeactivate->Clr_Link();		// Efface le Link		// Pourrait être mis à pars
	}

	ConsoleRender::Stop_Queue();		// Finis l'animation de destruction

	// Problème avec les animations dans ma renderlist: Je peux pas les canceller, et elles ne reflètent pas l'état immédiat du jeu. Ici, si le joueur décide de se déplacer sur 
	// un link qui va être effacer, le joueur va être effacé
}

bool DestroyChainOfWalls::Add_Chain_ToDestroy(GrdCoord crd, Link* link)
{




	Link* toDeactivate, * parentLink;	// Le Link qui est connecté au premier Link à détruire
	Wall* parentWall;					// Le mur à détruire entre deux Link

	// 2 choix pour détruire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		toDeactivate = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
	else
		toDeactivate = link;	// le premier de la liste

	if (toDeactivate->state != LinkState::ROOT)	// un root n'a pas de parent
	{
		parentWall = toDeactivate->pParent;	// Le wall connectant le parent au link à détruire
		parentLink = parentWall->pParent;	// Le parentLink du link à détruire
		parentLink->Unbound_Wall_Child(parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui était le parent de la chaîne de destruction		
		push(toDeactivate); // Ceci sera le premier élément de la liste à détruire
	}
	else {	// Si le premier Link est une Root
		Add_Children_To_List(toDeactivate);	 // Ajoute tout de suite ses enfants
		toDeactivate->Deactivate_Link();	 // Et on désactive tout de suite 
	}

 }


bool DestroyChainOfWalls::Update_Destruction()
{


}
