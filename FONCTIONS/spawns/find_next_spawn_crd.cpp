
#include "../grid/AllGrids.h"
#include "invalid_spwns.h"
#include "bots_to_spawn.h"
//#include "rng.h"	// no need apparently

#include "find_next_spawn_crd.h"

using namespace bots_to_spawn;		// Spécifies les crd valides de spawn durant ce cycle

struct RandomCrd {	// Random coord
	bool border;
	bool spawn;
};

//	Pour copier les valeurs des nouveaux bot généraux. Ceci évite de changer attributs de base du prochain spawn en cas d'échec de création
static SpwCrd spwCrd;				// Attributs pour trouver le prochain spawn de bot
static RandomCrd rdmCrd;			// Randomness des prochains spawns


// Trouve la bordure de spawn 
// --------------------------

static void Find_BoxSide()		
{

	if (rdmCrd.border)	// Veux Dire qu'aucune boxside n'est spécifié. On va en choisir une au hasard
	{
		if (gVerticalBorder)
			rand() % 2 == 0 ? spwCrd.border = LEFT : spwCrd.border = RIGHT;	// Spawn sur les bordures gauches ou droites
		else
			if (gHorizontalBorder)
				rand() % 2 == 0 ? spwCrd.border = UP : spwCrd.border = DOWN;	// Spawn sur les bordures haut et bas
			else
				spwCrd.border = rand() % 4;	//	Bordure random
	}
}
// Trouve le numéro du spawn sur la bordure
// ----------------------------------------

static void Find_Spwn_Num()		
{
	// Si le spawn est invalidé, par la présence d'un block. On va trouver une autre COORD, Mais pas un nouveau côté de BoxSide
	if (rdmCrd.spawn)
	{
		if (gBoxSide % 2 == 0)	// border horizontaux
			spwCrd.spwNum = rand() % SpawnGrid::Get_MaxSpwnCrdX(); // Setup ça au début du niveau
		else
		{
			spwCrd.spwNum = rand() % SpawnGrid::Get_MaxSpwnCrdY();
		}
	}
	else
		if (gCrdInterval.active) // Si l'intervalle est activé autre chose que Zéro 				
			spwCrd.spwNum = rand() % (gCrdInterval.max - gCrdInterval.min + 1) + gCrdInterval.min;	// Création d'une coord à l'int. de l'interval
}

// Copy les attributs génériques qui dictent quels seront les Crd de spawn valides durant ce cycle
static void Copy_Generic_Attributes()
{
	if(spwCrd.border != gBoxSide)			spwCrd.border = gBoxSide;
	if(spwCrd.spwNum != gSpwNum)			spwCrd.spwNum = gSpwNum;
	if(rdmCrd.border != gRandomBoxSide)		rdmCrd.border = gRandomBoxSide;
	if(rdmCrd.spawn != gRandomSpwn)			rdmCrd.spawn= gRandomSpwn;
}

// Copy UNE bunch d'attributs spécifiques pour le spawn immédiat. Si la liste est vide, le spawn n'aura que les attributs génériques
static void Add_Specific_Attributes()			
{
	if (Pop(spwCrd))	// Prend une crd spécifique de la liste
	{
		if (spwCrd.border == -1)				// Si égal -1, on conserve l'attribut général
			spwCrd.border = (Direction)gBoxSide;

		if (spwCrd.spwNum == -1)		// Si égal -1, on rend le spawn random
			rdmCrd.spawn = true;		// la coord sera COMPLETEMENT random, ou spécifique(pas d'interval, parce que un interval peut être trop grand pour une bordure différente)
	}
}

// Vérifie si la coordonnée de spawn est une coordonnée valide
static bool Validate_Coord()
{
	if (!spawnGrid->Is_Inbound(spwCrd.border, spwCrd.spwNum))		//chck si la coord est inbound d'abord
		return false;
	
	if (InvalidSpwCrd::Check_Invalid_Coord_Lists(spwCrd))	//Mmm je devrais pas m'arranger pour ne juste pas générer une coord une deuxième fois? à la place...
		return false;

	//InvalidSpwCrd::Add_Invalid_Coord_To_List(spwCrd);	// why?		si spawn block, thats why
		//return false;

	return true;

}


// Trouve le prochain spawn 
// ----------------------------------------

SpwCrd Find_Spwn_Coord()
{
	bool validSpwn;

	Copy_Generic_Attributes();	// on doit copier les attributs génériques, parcequ'on risque de les modifier. Si on les modifient, les prochains spawns de ce cycle vont spawner tout croche
	Add_Specific_Attributes();	// Trouve une crd spécifique dans la liste. Si la liste est vide, ne change rien


	//spawn.c = genBoxSide;
	//spawn.r = genInterval?;
	do
	{
		validSpwn = true; // La coord Commence par être valide

		Find_BoxSide();	// Trouve la bordure 
		Find_Spwn_Num();// Trouve le numéro du spawn
	

			//spawnGrid->border[Spw.border].spawn[Spw.spw];

		// VALIDATION
		if (!Validate_Coord())				//La Coord, ou le Spawn? mm
		{
			validSpwn = false;
			rdmCrd.spawn = true;			// En ce moment, si un spawn foire, on en cherche un autre randomnly
			continue;	// no validos
		}

	// Si le spawn y foire, on change les proprités de CE spawn uniquement, pas les Generic Attributes.
	 // Ce qui va être chagé : Le randomness de la coordonnée en gros [Boxside][SpwNum]

		// faudrait que je me fasse une liste des spawn qui ont été fait sur l'interval, parce que la ça se peut qu'une coord survient 2fois. Et dans ce cas, on en choisit une autre au hasard, c'est juste pas efficace
		// et une liste pour chaque boxside		-> almost done
	} while (validSpwn == false);

	return spwCrd;	// SOFLOCK: Si aucun spawn est valide
}