
#include "../UI/direction.h"
#include "valid_spwn_intervals.h"

/* Variables static */

 int ValidSpwnIntervals::maxVer;	
 int ValidSpwnIntervals::maxHor;	
 IntervalList ValidSpwnIntervals::primary;	
 IntervalList ValidSpwnIntervals::scndary;	
 Interval* ValidSpwnIntervals::prev;		
 int ValidSpwnIntervals::bannedSpwn[4];	
 bool ValidSpwnIntervals::borderIsFull[4];
 bool ValidSpwnIntervals::allPrimeEmpty = true;	
 bool ValidSpwnIntervals::isPriority;	
 /* OUECH*/

bool ValidSpwnIntervals::Is_Secondary_List_Full(int border)
{
	if (border == LEFT || border == RIGHT)
		return bannedSpwn[border] == maxVer;	
	else
		return bannedSpwn[border] == maxHor;	
}
 bool ValidSpwnIntervals::Is_Border_Full(int border)			
{
	 if (Is_Secondary_List_Full(border))
		 if (primary.start[border] == NULL)
		 {
			 borderIsFull[border] = true;
			 return true;
		 }

	 return false;
}

bool ValidSpwnIntervals::Is_Secondary_List_Empty(int border)
{
	return (scndary.start[border] == NULL && bannedSpwn[border] == 0);	
}

void ValidSpwnIntervals::Modify_Min(Interval* intval, int newMin)
{
	intval->min = newMin;	
}

void ValidSpwnIntervals::Modify_Max(Interval* intval, int newMax) 
{
	intval->max = newMax;	
}

bool ValidSpwnIntervals::Are_Primary_Lists_Empty()			
{
	int arethey = 0;	// they are!

	for (int border = 0; border < 4; border++)
	{
		if (primary.numIntervals[border] == 0)
			arethey++;
	}

	if (arethey == 4)
		return true;
	else
		return false;
}

// Delete un intervalle quand il est vide
// --------------------------------------

void ValidSpwnIntervals::Destroy_Empty_Interval(IntervalList& list, Interval* intval, int border) 
{
	list.numIntervals[border]--;	

	if (intval == list.start[border] && intval == list.end[border])	
	{
		delete intval;									
		intval  = list.start[border] = list.end[border] = NULL;	

		if (isPriority)	// POURRAIT ÊTRE POTENTIELLEMENT ÉRRONÉ
			allPrimeEmpty = Are_Primary_Lists_Empty();	
	}
	else
	{
		if (intval == list.start[border])
		{
			list.start[border] = list.start[border]->nxt;
			

		}
		else
			if (intval == list.end[border])
			{
				list.end[border] = prev;
				prev->nxt = NULL;
			}
			else
				if (prev)	
					prev->nxt = intval->nxt;

		delete intval;	
	}
}

Interval* ValidSpwnIntervals::Find_Interval(int border, int spwNum, IntervalList* &theList)			
{
	static Interval* it; it = NULL;	
	static IntervalList *list;		
	static bool found; found = false;

	prev = NULL;	// À chaque fois qu'on cherche un nouvel item, on va reset le previous* ptr

	for (size_t i = 0; i < 2; i++)	// Faut vérifier les deux listes malheureusement. Puisque primary élimine des éléments de secondary
	{
		if (i % 2 == 0)
			list = &scndary;	// Vérifie la liste secondaire en premier
		else
			list = &primary;	// ensuite la primaire

		it = list->start[border];
		
		while (it)
		{
			if (it->min <= spwNum)
				if (it->max > spwNum)
				{
					found = true;
					break;					// La crd est dans cet interval	     intrv >= min      intrv < max 
				}

			prev = it;			
			it = it->nxt;	
		}

		if (found)
			break;
	}

	if (it)
		theList = list;		// Faut rapporter la bonne liste après :( mais pas la modifier si on a rien trouvé. i know its dumbo
		
	return it;		// Pourrait être NULL si liste vide, --=-=ou si valeure trop grande ou erronée!!!!-=-=-
}
void ValidSpwnIntervals::Initialize_Valid_Spawn_List()							// DOIT ÊTRE FAIT À CHAQUE DÉBUT DE NIVEAU!	
{
	for (int border = 0; border < 4; border++)
	{
		Reset_Secondary_List();	
	}
}

Interval* ValidSpwnIntervals::Set_First_Interval(int border)
{
	if (Is_Secondary_List_Empty(border))
	{
		scndary.start[border] = scndary.end[border] = new Interval;	

		scndary.start[border]->min = 0;	

		if (border == LEFT || border == RIGHT)
			scndary.start[border]->max = maxVer;
		else
			scndary.start[border]->max = maxHor;

		scndary.numIntervals[border] = 1;

		scndary.end[border]->nxt = NULL;
		return scndary.start[border];
	}
	else
		return NULL;	// Y'an avait déjà 1 ici. Il faut vider D'abord!!
}

Interval* ValidSpwnIntervals::Create_New_Interval(IntervalList& list, int border, int min, int max)
{
	static Interval* newIntval; newIntval = NULL;	// Fais des static cuz i dont know if it really helps

	newIntval = new Interval;
	newIntval->min = min;
	newIntval->max = max;
	newIntval->nxt = NULL;

	if (prev)	
	{
		prev = prev->nxt = newIntval;	
	}

	list.numIntervals[border]++;	

	return newIntval;	
}

bool ValidSpwnIntervals::Add_Primary_Interval(int border, int min, int max)	// SIDENOTE: Pour chaque Bordure, 1 seule intervalle pourra être fournis lors d'un cycle de spawn
{																			// cette intervalle pourra être divisé au fur et à mesure, mais il sera interdit de l'agrandir
	if (primary.start[border] != NULL)	
		return false;		// Il est Interdit d'ajouter un Nouvel Intervalle!!!!!

	primary.start[border] = primary.end[border] = Create_New_Interval(primary, border, min, max);	// Derp
	Exclude_Primary_Interval(border, min, max);				

	allPrimeEmpty = false;		

	return true;
}

bool ValidSpwnIntervals::Exclude_Primary_Interval(int border, int min, int max)		
{
	int scndaryMax = scndary.start[border]->max;	
	int scndaryMin = scndary.start[border]->min;	

	if (min == scndaryMin && scndaryMax == max)	
		Destroy_Empty_Interval(scndary, scndary.start[border], border);
	else
	{
		if (min == scndaryMin)	
			scndary.start[border]->min = max + 1;
		else
			if (max == scndaryMax)
				scndary.start[border]->max = min;
			else
			{
				scndary.start[border]->max = min;	
				prev = scndary.start[border];		
				Create_New_Interval(scndary, border, max, scndaryMax);
				
				if(scndary.end[border] == scndary.start[border])
					scndary.end[border] = scndary.start[border]->nxt;

				prev = scndary.end[border]->nxt = NULL;	// tout brisait à cause d'un pointeur gloabl dénommée prev. Un pointeur static de class est une véritable idée étron-esque
			}
	}

	return true;	
}

void ValidSpwnIntervals::Remove_Spawn_From_List(IntervalList &list, Interval* intval, int border, int bannedCrd)
{
	int max = intval->max;	
	int min = intval->min;	

	if (max - min == 1)	
	{
		if (min == bannedCrd || bannedCrd == max)		 
			Destroy_Empty_Interval(list, intval, border);
	}
	else
	{
		if (min == bannedCrd)	
			Modify_Min(intval, bannedCrd + 1);
		else
			if (bannedCrd == max - 1)	
				Modify_Max(intval, bannedCrd);
			else
				Split_Interval_In_Two(list, border, intval, bannedCrd);	
	}
	
}

void ValidSpwnIntervals::Split_Interval_In_Two(IntervalList &list, int border, Interval* &intval, int bannedCrd)	
{
	static Interval* interval_1; interval_1 = NULL;	// Fais des static cuz i dont know if it really helps

	interval_1 = Create_New_Interval(list, border, intval->min, bannedCrd);	

	if (intval == list.start[border])		
		list.start[border] = interval_1;
	
	interval_1->nxt = intval;	// Re-Pointeursiation

	Modify_Min(intval, bannedCrd + 1);	// Réduit l'intervalle originale
}

void ValidSpwnIntervals::Reset_Secondary_List()
{
	static Interval* it; it = NULL;	

	for (int i = 0; i < 4; i++)	// 4 = nombre de borders
	{
		if (!Is_Secondary_List_Full(i))		
		{
			it = scndary.start[i];

			while (it)	
			{
				prev = it;
				it = it->nxt;
				delete prev;	// Vide la liste		: Si tu Crash ici, c'est que ta essayer de faire spawner un bot sur une coord plus grande que le nombre de spawn possible
			}											// Genre en écrivant linkGrid.Get_Rows() au lieu de Get_Num_Spawns().   Faudrait Vraiment que Je criss un safety là-dedans....

			scndary.start[i] = NULL;	
			prev = it = NULL;
		}

		bannedSpwn[i] = 0;			// !in this order pls!
		borderIsFull[i] = false;	// ahhhhh
		Set_First_Interval(i);		
	}
}

void ValidSpwnIntervals::Empty_Primary_List()	
{
	static Interval* it; it = NULL;

	for (int i = 0; i < 4; i++)	
	{
		while (it = primary.start[i])	
		{
			primary.start[i] = it->nxt;
			delete it;
		}

		primary.numIntervals[i] = 0;	
		primary.end[i] = {};
	}

	allPrimeEmpty = true;	
}

Interval* ValidSpwnIntervals::Pick_Random_Interval(const IntervalList& list, int border)	
{
	static Interval* it; it = NULL;	
	int rdmIntervalle;

	rdmIntervalle = rand() % list.numIntervals[border];

	it = list.start[border];	

	if (list.numIntervals[border] != 1)				// % 1 donne toujours 1.		% > 1  peut donner 0		(par définition, un intervalle de zéro n'existe pas)
		for (int i = 0; i < rdmIntervalle; i++)
		{
			prev = it;		
			it = it->nxt;
		}

	return it;
}
int ValidSpwnIntervals::Pick_Rdm_Spwn_From_Interval(Interval* intval)	
{
	int rdmSpwn, numSpwns;

	if (intval->min == 1)
		rdmSpwn = intval->min;	
	else
	{
		numSpwns = intval->max - intval->min;			
		rdmSpwn = rand() % numSpwns + intval->min;		
	}

	return rdmSpwn; 
}

int ValidSpwnIntervals::Pick_Primary_Border()	
{
	if (allPrimeEmpty == true)		
		return -1;
	else
		for (int border = 0; border < 4; border++)
		{
			if (primary.start[border] != NULL)
				return border;
		}
	
	return -1;	
}

int ValidSpwnIntervals::Pick_Valid_Spawn(int border, bool random, int spwNum)	
{
	static Interval* it; prev = it = NULL;																				// J'ai blocké longtemps parce que prev n'avait pas été ré-initialisé à NULL
	static IntervalList *list;		
	static int spawn;																									 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
																														 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	// Trouve la bonne liste si le spawn qu'on choisit est random														 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	if (primary.start[border] != NULL)	// On va prendre une coord là dedans mah dude									 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	{																													 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
		list = &primary;	
		isPriority = true;
	}
	else
	{
		if (Is_Secondary_List_Full(border))	// Safety
			return -1;						// La bordure sélectionné ne contient aucun spawn de disponible durant ce cycle
		else
			Set_First_Interval(border); // La liste avait-elle  été initialisé?

			list = &scndary;		
	}

	if (!random)	// Trouvons le spawn!
	{
		spawn = spwNum;
		it = Find_Interval(border, spwNum, list);		// Trouve l'intervalle contenant le spawn. 
		if (!it)			// Si le spawn n'est pas dans un intervalle 
			random = true;	// On va spawner quelque chose de random sur la même bordure à la place
	}

	if (random)		// Trouvons un spawn disponible, un peu randomly :)
	{
		it = Pick_Random_Interval(*list, border);		// Prend 1 intervalle random parmis cette liste!!!
		spawn = Pick_Rdm_Spwn_From_Interval(it);		// Prend un spawn Random parmis cette intervalle
	}

	Remove_Spawn_From_List(*list, it, border, spawn);	// Modifie l'intervalle pour exclure le spawn sélectionné par les DieuX

	bannedSpwn[border]++;		

	return spawn;	
}


// bingo bango














