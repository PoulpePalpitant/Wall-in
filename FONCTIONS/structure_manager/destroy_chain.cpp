
#include "destroy_chain.h"


// LE STACK PILE
// *************					/* va servir � manager la liste de link qu'on va devoir d�truire */

// Types priv�s au module stack
// ----------------------------

// Une item du stack de link � d�truire
struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};	
struct Stack // une pile d'item chain�s
{
	LinkToDestroy* top; // indique le dessus de la pile
	int count;	// don't need
};

static Stack S = {};	// Variable globale priv�e au module stack

// Fonctions publiques du module stack
// -----------------------------------

bool empty()
{
	return S.top == NULL;		// Si le top est vide ou plein
}

void push(Link* link)
{
	LinkToDestroy* top = new LinkToDestroy;
	S.count++;

	if (empty())top->below = NULL; 	else top->below = S.top;

	S.top = top;
	S.top->link = link;
}

bool pop( Link* &data)	// D�truit l'item sur le dessus, mais conserve la donn�e en r�f�rence
{
	if (!empty())
	{
		LinkToDestroy* above = S.top;

		data = S.top->link;		// data devient l'item du top
		S.top = S.top->below;	// le top devient l'item en dessous

		delete above;			// p�te le(ancien) top
		S.count--;

		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DestroyChainOfWalls::Add_Children_To_List(Link* parent)
{
	int numChild;					// Nombre de child � ajouter � la liste de destruction

	numChild = parent->numChild;

	for (int i = 0; i < numChild; i++)	// 4 children max
	{
		if (parent->pWalls[i] != NULL)/*s�curit�*/
			push(parent->pWalls[i]->pChild);	// Ajoute CHILD LINK � la liste(le child du wall, qui est lui le child du LINK Parent)	
	}
}


// Wall and Link destruction
// *************************

void DestroyChainOfWalls::Destroy_Chain_Of_Walls(GrdCoord crd, Link* link)
{
	Link* toDeactivate, *parentLink;	// Le Link qui est connect� au premier Link � d�truire
	Wall* parentWall;					// Le mur � d�truire entre deux Link
	
	// 2 choix pour d�truire: L'adresse du Link ou sa crd dans le grd de links
	if (link == NULL)
		toDeactivate = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
	else
		toDeactivate = link;	// le premier de la liste

	if (toDeactivate->state != LinkState::ROOT)	// un root n'a pas de parent
	{
		parentWall = toDeactivate->pParent;	// Le wall connectant le parent au link � d�truire
		parentLink = parentWall->pParent;	// Le parentLink du link � d�truire
		parentLink->Unbound_Wall_Child(parentWall);// On retire le lien unissant le parent Link au wall			ici, on retire 1child de la liste du Link qui �tait le parent de la cha�ne de destruction		
		push(toDeactivate); // Ceci sera le premier �l�ment de la liste � d�truire
	}
	else {	// Si le premier Link est une Root
		Add_Children_To_List(toDeactivate);	 // Ajoute tout de suite ses enfants
		toDeactivate->Deactivate_Link();	 // Et on d�sactive
	}

	while (!empty())		// Tant qu'il reste des Links � d�truire
	{
		pop(toDeactivate);	// Prend un �l�ment da liste de Link � d�truire
		
		// V�rifie si ya des Kids
		Add_Children_To_List(toDeactivate);	 // Ajoute les enfants du Link � la liste de destruction
		parentWall = toDeactivate->pParent;	 // trouve le mur parent
		toDeactivate->Deactivate_Link();	 // d�truit le Link				Je ne'ai pas s�par� deactivate Link et erase Link
		parentWall->Deactivate_Wall();		 // D�sactive le mur				J'ai s�par� deactivate wall et erase wall
		parentWall->UI_Draw_Or_Erase_Wall(); // efface son mur on top		* alors tu draw, ou tu erase?
	}

	//SI TOUT �A BUG EN TEMPS R�EL, VOICI CE QUE TU DEVRA FAIRE
	/*
	- CHANGE TA LOGIQUE DE "STACK" POUR QUE LE "POP" RETIRE LE PREMIER �L�MENT DE LA LISTE AU LIEU DU DERNIER
	- MUTEX CETTE FONCTION DE DESTRUCTION 
	- ENLEVER TOUT LES FONCTIONS ERASE DE CETTE FONCTION

	- CR�ER UNE NOUVELLE FONCTION QUI VA PRENDRE LA "PILE" ET L'UTILISER UNIQUEMENT POUR "EFFACER"
	- MUTEX CETTE FONCTION
	- CR�ER UN GESTIONNAIRE DE PILE, QUI VA PERMETTRE DE CR�ER PLUSIEURS PILES DE "� EFFACER". ET QUI VA POUVOIR EFFACER LES PILES D�S QU'ON A FINIS D'AFFICHER
	- MUTEX CETTE FONCTION

	ouf...

	*/	
}
