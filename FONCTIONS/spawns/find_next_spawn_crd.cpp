#include "find_next_spawn_crd.h"

#include "../grid/AllGrids.h"
#include "valid_spwn_intervals.h"
#include "bots_to_spawn.h"


using namespace bots_to_spawn;		// Sp�cifies les crd valides de spawn durant ce cycle

struct RandomCrd {	
	bool border;
	bool spawn;
};

//	Pour copier les valeurs des nouveaux bot g�n�raux. Ceci �vite de changer attributs de base du prochain spawn en cas d'�chec de cr�ation
static SpwCrd spwCrd = {};				
static RandomCrd rdmCrd = {};			
static bool cancelSpwn = false;			

static void Find_BoxSide()		// NOTE: Si tu fournis un spawn number, �a brise compl�tement le random des intervalles
{
	if (rdmCrd.border)	
	{
		if (rdmCrd.spawn)		
		{
			spwCrd.border = ValidSpwnIntervals::Pick_Primary_Border(); // Doit trouver une bordure avec un intervalle prioritaire	

			if (spwCrd.border == -1)	// Plus d'intervalles prioritaires de disponibles
			{
				if (gAllSides)					
					spwCrd.border = rand() % 4;	
				else
					if (gVerticalSpawns) 
					{
						rand() % 2 == 0 ? spwCrd.border = LEFT : spwCrd.border = RIGHT;	

						if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border)) 	// Check si la bordure est toute bloqu�
							Find_Opposite_Dir((Direction)spwCrd.border);		// Si oui, Prend la bordure en face
						else
							return;					
					}
					else
						if (gHorizontalSpawns)	
						{
							rand() % 2 == 0 ? spwCrd.border = UP : spwCrd.border = DOWN;	

							if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border)) 	
								Find_Opposite_Dir((Direction)spwCrd.border);		
							else
								return;						
						}
			}
		}
	}	
	
	if (ValidSpwnIntervals::Is_Border_Full(spwCrd.border))
		cancelSpwn = true;	// cancel that, no space here
}


static void Find_Spwn_Num()		
{
	do
	{
		spwCrd.spwNum = ValidSpwnIntervals::Pick_Valid_Spawn(spwCrd.border, rdmCrd.spawn, spwCrd.spwNum);

	} while (spwCrd.spwNum == -1);		// Tant et aussi longtemps qu'on a pas trouv� un spawn valide
}

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
			rdmCrd.spawn = true;		
		else
			rdmCrd.spawn = false;
	}
}

SpwCrd Find_Spwn_Coord()
{
	cancelSpwn = false;	

	Copy_Generic_Attributes();	// on doit copier les attributs g�n�riques, parcequ'on risque de les modifier. Si on les modifient, les prochains spawns de ce cycle vont spawner tout croche
	Add_Specific_Attributes();	// Trouve une crd sp�cifique dans la liste. Si la liste est vide, ne change rien

	Find_BoxSide();	// Trouve la bordure 

	if(!cancelSpwn)	
		Find_Spwn_Num();// Trouve le num�ro du spawn
	

	return spwCrd;	// SOFLOCK: Si aucun spawn est valide
}