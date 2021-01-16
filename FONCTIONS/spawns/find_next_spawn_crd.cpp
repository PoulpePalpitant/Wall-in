
#include "../grid/AllGrids.h"
#include "valid_spwn_intervals.h"
#include "bots_to_spawn.h"
//#include "rng.h"	// no need apparently

#include "find_next_spawn_crd.h"

using namespace bots_to_spawn;		// Sp�cifies les crd valides de spawn durant ce cycle

struct RandomCrd {	// Random coord
	bool border;
	bool spawn;
};

//	Pour copier les valeurs des nouveaux bot g�n�raux. Ceci �vite de changer attributs de base du prochain spawn en cas d'�chec de cr�ation
static SpwCrd spwCrd = {};				// Attributs pour trouver le prochain spawn de bot
static RandomCrd rdmCrd = {};			// Randomness des prochains spawns
static bool cancelSpwn = false;			

// Trouve la bordure de spawn 
// --------------------------

static void Find_BoxSide()		// NOTE: Si tu fournis un spawn number, �a brise compl�tement le random des intervalles
{
	if (rdmCrd.border)	// Veux Dire qu'aucune boxside n'est sp�cifi�. On va en choisir une au hasard
	{
		if (rdmCrd.spawn)		// Si la coordonn�e de spawn est random					
		{
			spwCrd.border = ValidSpwnIntervals::Pick_Primary_Border();// Doit trouver une bordure avec un intervalle prioritaire	

			if (spwCrd.border == -1)	// Plus d'intervalles prioritaires de disponibles
			{
				if (gAllSides)					// Tout les bordures				   //				// YO SI CETTE LISTE EST AUSSI GRANDE QUE LE NOMBRE DE SPAWN COORD SUR UNE BORDURE, TU DEVRAIS CANCELLER LE 
					spwCrd.border = rand() % 4;	//	Bordure random					   //				// RESTE DES SPAWNS EN FAISANT BREAK; ET EN SETTANT LE NUMSPAWN � 0!
				else
					if (gVerticalSpawns) // Bordures LEFT & RIGHT
					{
						rand() % 2 == 0 ? spwCrd.border = LEFT : spwCrd.border = RIGHT;	// Spawn sur les bordures gauches ou droites

						if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border)) 	// Check si la bordure est toute bloqu�
							Find_Opposite_Dir((Direction)spwCrd.border);		// Si oui, Prend la bordure en face
						else
							return;	// hey that's valid						
					}
					else
						if (gHorizontalSpawns)	// Bordures UP & DOWN
						{
							rand() % 2 == 0 ? spwCrd.border = UP : spwCrd.border = DOWN;	// Spawn sur les bordures haut et bas

							if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border)) 	// Check si la bordure est toute bloqu�
								Find_Opposite_Dir((Direction)spwCrd.border);		// Si oui, Prend la bordure en face
							else
								return;	// we good here						
						}
			}
		}
	}	
	
	if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border)) 	// Check si la bordure est toute bloqu�
		cancelSpwn = true;	// cancel that, no space here
}

// Trouve le num�ro du spawn sur la bordure, si non-acessible, en choisit un random
// --------------------------------------------------------------------------------

static void Find_Spwn_Num()		
{
	do
	{
		spwCrd.spwNum = ValidSpwnIntervals::Pick_Valid_Spawn(spwCrd.border, rdmCrd.spawn, spwCrd.spwNum);

	} while (spwCrd.spwNum == -1);		// Tant et aussi longtemps qu'on a pas trouv� un spawn valide
}

// Copy les attributs g�n�riques qui dictent quels seront les Crd de spawn valides durant ce cycle
static void Copy_Generic_Attributes()
{
	int Fuckyou;
	if(spwCrd.border != gBoxSide)			
		spwCrd.border = bots_to_spawn::gBoxSide;
	
	Fuckyou = bots_to_spawn::gSpwNum;				//	Wow lol. Merci

	if (spwCrd.spwNum != gSpwNum)
		spwCrd.spwNum = bots_to_spawn::gSpwNum;
	
	if(rdmCrd.border != gRandomBoxSide)		
		rdmCrd.border = bots_to_spawn::gRandomBoxSide;
	if(rdmCrd.spawn != gRandomSpwn)			
		rdmCrd.spawn= bots_to_spawn::gRandomSpwn;
}

// Copy UNE bunch d'attributs sp�cifiques pour le spawn imm�diat. Si la liste est vide, le spawn n'aura que les attributs g�n�riques
static void Add_Specific_Attributes()			
{
	if (Pop(spwCrd))	// Prend une crd sp�cifique de la liste
	{
		if (spwCrd.border == -1)				// Si �gal -1, on conserve l'attribut g�n�ral
			spwCrd.border = (Direction)gBoxSide;

		if (spwCrd.spwNum == -1)		// Si �gal -1, on rend le spawn random
			rdmCrd.spawn = true;		// la coord sera COMPLETEMENT random, ou sp�cifique(pas d'interval, parce que un interval peut �tre trop grand pour une bordure diff�rente)
		else
			rdmCrd.spawn = false;
	}
}

// Trouve le prochain spawn 
// ----------------------------------------

SpwCrd Find_Spwn_Coord()
{
	cancelSpwn = false;	// Si rien n'est disponible, on cancel

	Copy_Generic_Attributes();	// on doit copier les attributs g�n�riques, parcequ'on risque de les modifier. Si on les modifient, les prochains spawns de ce cycle vont spawner tout croche
	Add_Specific_Attributes();	// Trouve une crd sp�cifique dans la liste. Si la liste est vide, ne change rien

	Find_BoxSide();	// Trouve la bordure 

	if(!cancelSpwn)	
		Find_Spwn_Num();// Trouve le num�ro du spawn
	

	return spwCrd;	// SOFLOCK: Si aucun spawn est valide
}