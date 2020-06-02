
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

		data = S.top->link;
		S.top = S.top->below;

		delete above;
		S.count--;

		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void DestroyChainOfWalls::Add_Children_To_List(Link* parent)
//{
//	int numChild;					// Nombre de child � ajouter � la liste de destruction
//
//	numChild = parent->numChild;
//
//	for (int i = 0; i < numChild; i++)	// 3 children max
//	{
//		if (parent->pChild[i] != NULL)
//			push(parent->pChild[i]);	// Ajoute child Link � la liste
//	}
//}
//
//
//// Wall and Link destruction
//// *************************
//
//static GrdCoord;	// variable global, priv� au cpp
//
//void DestroyChainOfWalls::Destroy_Chain_Of_Walls(GrdCoord crd)
//{
//	Link* parent, * child;			// 
//
//	Wall* wallBtwn;					// Le mur � d�truire entre deux Link
//
//
//	parent = &linkGrid->link[crd.c][crd.r]; // le premier de la liste
//	
//	for (int i = 0; i < 3 - 1; i++)	// On d�cale pas le dernier �l�ment
//	{
//		if (parent->pParent->pChild[i] = NULL)								// D�cale les childs du parent du premier Link � d�truire
//			parent->pParent->pChild[i] = parent->pParent->pChild[i + 1];	// pour optimiser la prochaine ligne
//	}
//
//	Add_Children_To_List(parent);	// Ajoute les enfants du Link � la liste de destruction
//	pop(child);						// Prend un �l�ment da liste � d�truire
//	parent->Deactivate_Link();		// d�truit le Link
//
//	//wallBtwn =
//
//
//		parent = child;
//
//
//	/*
//	
//	-delete parent
//	-find wall
//	-delete wall
//
//	Rinse, Wash, repeat
//	*/
//
//
//
//
//	// Acc�s au Link. doit pouvoir ajouter � la liste tout ses childs
//	// Get_Child(int child);
//	// return child[1]
//
//	//wall
//}
