
#include "../UI/direction.h"
#include "valid_spwn_intervals.h"

/* Variables static */

 int ValidSpwnIntervals::maxVer;	// Donne le max sur les bordures verticaux
 int ValidSpwnIntervals::maxHor;	// Donne le max sur les bordures horizontaux	
 IntervalList ValidSpwnIntervals::primary;	// La liste contentant tout les intervalles de spawns prioritaires
 IntervalList ValidSpwnIntervals::scndary;	// La liste contenant les intervalles valides de spawns
 Interval* ValidSpwnIntervals::prev;		// 1 Seul It�rateur, pointe vers un �l�ment pr�c�dant			
 int ValidSpwnIntervals::bannedSpwn[4];	// Permet de v�rifier le nombre de spawn exclut sur une bordure
 bool ValidSpwnIntervals::borderIsFull[4];// La bordure ne contient aucun spawn de disponible
 bool ValidSpwnIntervals::allPrimeEmpty = true;	// Tout les listes primaires sont vides
 bool ValidSpwnIntervals::isPriority;	// D�termine si on bannis un spawn qui est pr�sent dans la liste prioritaire

 /* OUECH*/

// Bordure d'intervalles pleine
// ---------------------------
bool ValidSpwnIntervals::Is_Secondary_List_Full(int border)
{
	if (border == LEFT || border == RIGHT)
		return bannedSpwn[border] == maxVer;	// bordure verticale	;|
	else
		return bannedSpwn[border] == maxHor;	// Le compte � atteint le max?
}
 bool ValidSpwnIntervals::Is_Border_Full(int border)			// La bordure n'a plus aucun intervalle de disponible
{
	 if (Is_Secondary_List_Full(border))
		 if (primary.start[border] == NULL)
		 {
			 borderIsFull[border] = true;
			 return true;
		 }

	 return false;
}
// Bordure d'intervalle vide
// -------------------------
bool ValidSpwnIntervals::Is_Secondary_List_Empty(int border)
{
	return (scndary.start[border] == NULL && bannedSpwn[border] == 0);	// La liste d'intervalle est vide
}

void ValidSpwnIntervals::Modify_Min(Interval* intval, int newMin)// Modifie le min
{
	intval->min = newMin;	// Augmente la borne de min 
	
	// Si tu crash, c'est que ta pas fait �a :  Destroy_Null_Interval(intval);
}

void ValidSpwnIntervals::Modify_Max(Interval* intval, int newMax) // MODIFIE LE MAX
{
	intval->max = newMax;	// R�duit la borne de max 
	// Si tu crash, c'est que ta pas fait �a :  Destroy_Null_Interval(intval);
}

bool ValidSpwnIntervals::Are_Primary_Lists_Empty()			// V�rification de �a
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
	list.numIntervals[border]--;	// -1 intervalle

	if (intval == list.start[border] && intval == list.end[border])	// 1 �l�ment dans la liste
	{
		delete intval;									// on le delete
		intval  = list.start[border] = list.end[border] = NULL;	// bonne pratique

		if (isPriority)	// POURRAIT �TRE POTENTIELLEMENT �RRON�
			allPrimeEmpty = Are_Primary_Lists_Empty();	// Les listes prioritaires sont maintenant vides!
	}
	else
	{
		if (intval == list.start[border])	// Delete le d�but
		{
			list.start[border] = list.start[border]->nxt;
			

		}
		else
			if (intval == list.end[border])	// end isnt recorded!!!
			{
				list.end[border] = prev;
				prev->nxt = NULL;
			}
			else
				if (prev)	// Redirection des pointeurs
					prev->nxt = intval->nxt;

		delete intval;	// Delete l'�l�ment de la liste
	}
}

Interval* ValidSpwnIntervals::Find_Interval(int border, int spwNum, IntervalList* &theList)			// Trouve un interval � l'aide d'une coord
{
	static Interval* it; it = NULL;	// Fais des static cuz i dont know if it really helps
	static IntervalList *list;		
	static bool found; found = false;

	prev = NULL;	// � chaque fois qu'on cherche un nouvel item, on va reset le previous* ptr

	for (size_t i = 0; i < 2; i++)	// Faut v�rifier les deux listes malheureusement. Puisque primary �limine des �l�ments de secondary
	{
		if (i % 2 == 0)
			list = &scndary;	// V�rifie la liste secondaire en premier
		else
			list = &primary;	// ensuite la primaire

		it = list->start[border];	// Premier �l�ment de la liste
		while (it)	// liste non-vide
		{
			if (it->min <= spwNum)
				if (it->max > spwNum)
				{
					found = true;
					break;					// La crd est dans cet interval	     intrv >= min      intrv < max 
				}

			prev = it;			// previous
			it = it->nxt;	// Passe au prochain
		}

		if (found)
			break;
	}

	if (it)
		theList = list;		// Faut rapporter la bonne liste apr�s :( mais pas la modifier si on a rien trouv�. i know its dumbo
		
	return it;		// Pourrait �tre NULL si liste vide, --=-=ou si valeure trop grande ou erron�e!!!!-=-=-
}
void ValidSpwnIntervals::Initialize_Valid_Spawn_List()							// DOIT �TRE FAIT � CHAQUE D�BUT DE NIVEAU!	
{
	for (int border = 0; border < 4; border++)
	{
		Reset_Secondary_List();	// Si un grid fut cr�� dans le pass�, on fait juste resize les intervals
	}
}
// // Set le premier interval, soit de "0 � Max Number of Spawn on border"
// ----------------------------------------------------------------------------
Interval* ValidSpwnIntervals::Set_First_Interval(int border)
{
	if (Is_Secondary_List_Empty(border))
	{
		scndary.start[border] = scndary.end[border] = new Interval;	// Nouvel intervalle

		scndary.start[border]->min = 0;	// Minimum

		// Assigne le max selon la longueur de la bordure
		if (border == LEFT || border == RIGHT)
			scndary.start[border]->max = maxVer;
		else
			scndary.start[border]->max = maxHor;

		scndary.numIntervals[border] = 1;	// 1 intervalle !

		scndary.end[border]->nxt = NULL;	// bonne pratique
		return scndary.start[border];
	}
	else
		return NULL;	// Y'an avait d�j� 1 ici. Il faut vider D'abord!!
}

Interval* ValidSpwnIntervals::Create_New_Interval(IntervalList& list, int border, int min, int max)
{
	static Interval* newIntval; newIntval = NULL;	// Fais des static cuz i dont know if it really helps

	newIntval = new Interval;	// Nouvel Intervalle
	newIntval->min = min;
	newIntval->max = max;
	newIntval->nxt = NULL;

	if (prev)	// Non d�but de list (NULL)
	{
		prev = prev->nxt = newIntval;	// Reset le prev pointeur ici?
	}

	list.numIntervals[border]++;	// 1 de plus les amis!

	return newIntval;	// doit �tre pass� � la bonne liste!!!!!!
}

// Ajoute un intervalle prioritaire dans la liste 
bool ValidSpwnIntervals::Add_Primary_Interval(int border, int min, int max)	// SIDENOTE: Pour chaque Bordure, 1 seule intervalle pourra �tre fournis lors d'un cycle de spawn
{																				// cette intervalle pourra �tre divis� au fur et � mesure, mais il sera interdit de l'agrandir
	if (primary.start[border] != NULL)	// Si la liste est vide
		return false;		// Il est Interdit d'ajouter un Nouvel Intervalle!!!!!

	primary.start[border] = primary.end[border] = Create_New_Interval(primary, border, min, max);	// Derp
	Exclude_Primary_Interval(border, min, max);				// Exlut tout les spawns dans l'intervalle primaires, de la liste des intervalles secondaires

	allPrimeEmpty = false;		// Les listes primaires ne sont pas tous vides

	return true;
}

// Ajoute un intervalle de spawn invalide � la liste secondaire
bool ValidSpwnIntervals::Exclude_Primary_Interval(int border, int min, int max)		// SIDENOTE: L'exclusion se fait toujours sur une liste � 1 intervalle 0 � max. Cuz I said So!
{
	//if (!Is_Secondary_List_Empty(border))	// dafuck, y'avais d�j� quek chose icitte!
	//	return false;

	int scndaryMax = scndary.start[border]->max;	// backup du max original
	int scndaryMin = scndary.start[border]->min;	// backup du min original

	if (min == scndaryMin && scndaryMax == max)	// Exclusion de l'intervalle au complet				// Devrait pas �tre min <= scndaryMin && scndaryMax <= max ??
		Destroy_Empty_Interval(scndary, scndary.start[border], border);// On doit d�truire l'intervalle
	else
	{
		if (min == scndaryMin)	// Exclut tout les valeurs primaire � gauche
			scndary.start[border]->min = max + 1;
		else
			if (max == scndaryMax)	// Exclut tout les valeurs primaires � droite
				scndary.start[border]->max = min;
			else
			{
				// Sinon on doit spliter l'intervalle en deux en excluant les valeurs primaires
				scndary.start[border]->max = min;	//	INTERVALLE #1
				prev = scndary.start[border];		// setup le pr�c�dant
				Create_New_Interval(scndary, border, max + 1, scndaryMax);			// INTERVALLE #2
				
				if(scndary.end[border] == scndary.start[border])
					scndary.end[border] = scndary.start[border]->nxt;

				prev = scndary.end[border]->nxt = NULL;	// tout brisait � cause d'un pointeur gloabl d�nomm�e prev. Un pointeur static de class est une v�ritable id�e �tron-esque
			}
	}

	//bannedSpwn[border] = max - min;		// Update le nombre de spawn bannis  NO!

	return true;	// worked
}

// Modifie un intervalle
void ValidSpwnIntervals::Remove_Spawn_From_List(IntervalList &list, Interval* intval, int border, int bannedCrd)
{
	int max = intval->max;	// backup du max original
	int min = intval->min;	// backup du min original

	if (max - min == 1)	// Si on a intervalle de 1
	{
		if (min == bannedCrd || bannedCrd == max)		 // Et qu'on doit r�duire une des deux extr�mit�s
			Destroy_Empty_Interval(list, intval, border);// On doit d�truire l'intervalle
	}
	else
	{
		if (min == bannedCrd)	// On peut juste exclure le min 
			Modify_Min(intval, bannedCrd + 1);
		else
			if (bannedCrd == max - 1)	// On peut juste modifier le max
				Modify_Max(intval, bannedCrd);
			else
				Split_Interval_In_Two(list, border, intval, bannedCrd);	// Sinon on split l'intervalle en deux. Ceci en cr�er un nouvel qui sera plac� juste avant			
	}
	
}

// Split un intervalle en ajoutant une nouvelle valeur � exclure
// ----------------------------------------------------------------------------
void ValidSpwnIntervals::Split_Interval_In_Two(IntervalList &list, int border, Interval* &intval, int bannedCrd)	// Quand tu ajoute une nouvelle valeur � exclure dans la liste d'interval
{
	static Interval* interval_1; interval_1 = NULL;	// Fais des static cuz i dont know if it really helps

	// INTERVALLE #1			
	interval_1 = Create_New_Interval(list, border, intval->min, bannedCrd);	// Cr�er un nouvel intervalle pr�c�dant 

	if (intval == list.start[border])		// Devient le nouveau start
		list.start[border] = interval_1;
	
	interval_1->nxt = intval;	// Re-Pointeursiation

	// INTERVALLE #2
	Modify_Min(intval, bannedCrd + 1);	// R�duit l'intervalle originale
}

// Chaque bordure est reset � son intervalle de base par d�faut: 0 � max
void ValidSpwnIntervals::Reset_Secondary_List()
{
	static Interval* it; it = NULL;	// Fais des static cuz i dont know if it really helps

	for (int i = 0; i < 4; i++)	// 4 = nombre de borders
	{
		///// BUG CATCHED!
		//if (bannedSpwn[i] == 0)	// Aucun spawn n'est bannis, l'intervalle de base est d�j� sett�	// ALERTE: SI TU RESIZE LE GRID, CECI EMP�CHE DE SETT� UN NOUVEL INTERVALLE!
		//	continue;
		////
		if (!Is_Secondary_List_Full(i))		// Tout les coord sont bannies. Il'n'y a donc aucun intervalle de disponible dans la liste
		{
			it = scndary.start[i];

			while (it)	// Liste non vide
			{
				prev = it;
				it = it->nxt;
				delete prev;	// Vide la liste		: Si tu Crash ici, c'est que ta essayer de faire spawner un bot sur une coord plus grande que le nombre de spawn possible
			}											// Genre en �crivant linkGrid.Get_Rows() au lieu de Get_Num_Spawns().   Faudrait Vraiment que Je criss un safety l�-dedans....

			scndary.start[i] = NULL;	// ?
			prev = it = NULL;	// Bonne pratique
		}

		bannedSpwn[i] = 0;			// !in this order pls!
		borderIsFull[i] = false;	// ahhhhh
		Set_First_Interval(i);		// Set un intervalle de d�part: 0 � max
	}
}

void ValidSpwnIntervals::Empty_Primary_List()	// Ces listes doivent �tre vid� � la fin des spawns
{
	static Interval* it; it = NULL;	// Fais des static cuz i dont know if it really helps

	for (int i = 0; i < 4; i++)	// 4 bordures
	{
		while (it = primary.start[i])	// Liste pas vide
		{
			primary.start[i] = it->nxt;
			delete it;
		}

		primary.numIntervals[i] = 0;	// Plus d'intervalle ici!
		primary.end[i] = {};	// Bonne pratique
	}

	allPrimeEmpty = true;		// Les listes primaires sont vides
}

Interval* ValidSpwnIntervals::Pick_Random_Interval(const IntervalList& list, int border)	// Prend un interval random parmis la liste figurant sur une bordure
{
	static Interval* it; it = NULL;	// Fais des static cuz i dont know if it really helps
	int rdmIntervalle;

	rdmIntervalle = rand() % list.numIntervals[border];		//  Prend 1 intervalle parmis le total pr�sent dans la liste

	it = list.start[border];	// D�but de la liste, Intervalle num�ro 1!

	if (list.numIntervals[border] != 1)				// % 1 donne toujours 1.		% > 1  peut donner 0		(par d�finition, un intervalle de z�ro n'existe pas)
		for (int i = 0; i < rdmIntervalle; i++)
		{
			prev = it;		// voil�!!
			it = it->nxt;
		}

	return it;	// L'Intervalle !
}
int ValidSpwnIntervals::Pick_Rdm_Spwn_From_Interval(Interval* intval)	// G�n�re la coordonn�e de spawn!
{
	int rdmSpwn, numSpwns;

	if (intval->min == 1)
		rdmSpwn = intval->min;	// Assur�ment
	else
	{
		numSpwns = intval->max - intval->min;			// le nombre de spawn pr�sent dans l'intervalle
		rdmSpwn = rand() % numSpwns + intval->min;		//  Un spawn random parmis cet intervalle!!!
	}

	return rdmSpwn; // Le spawn !
}

int ValidSpwnIntervals::Pick_Primary_Border()	// Prend une bordure contenant une liste primaire
{
	if (allPrimeEmpty == true)		// Les listes primaires sont vides brah�
		return -1;
	else
		for (int border = 0; border < 4; border++)
		{
			if (primary.start[border] != NULL)
				return border;
		}
	
	return -1;	// failed somewhere
}
// Trouve un spawn disponible sur une bordure pr�d�termin�
int ValidSpwnIntervals::Pick_Valid_Spawn(int border, bool random, int spwNum)	// On trouve un intervalle qui ensuite trouve un spawn
{
	static Interval* it; prev = it = NULL;	// Fais des static cuz i dont know if it really helps						// J'ai block� longtemps parce que prev n'avait pas �t� r�-initialis� � NULL
	static IntervalList *list;		// La liste dans laquelle on va piger un spawn
	static int spawn;																									 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
																														 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	// Trouve la bonne liste si le spawn qu'on choisit est random														 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	if (primary.start[border] != NULL)	// On va prendre une coord l� dedans mah dude									 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
	{																													 // BONNE PRATIQUE	 BONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUEBONNE PRATIQUE
		list = &primary;	// Liste prioritaire
		isPriority = true;
	}
	else
	{
		if (Is_Secondary_List_Full(border))	// Safety
			return -1;						// La bordure s�lectionn� ne contient aucun spawn de disponible durant ce cycle
		else
			Set_First_Interval(border); // La liste avait-elle  �t� initialis�?

			list = &scndary;		// autre liste
	}

	if (!random)	// Trouvons le spawn!
	{
		spawn = spwNum;
		it = Find_Interval(border, spwNum, list);		// Trouve l'intervalle contenant le spawn. Change la liste pour que �a correspond � celle contenant l'intervalle
		if (!it)			// Si le spawn n'est pas dans un intervalle 
			random = true;	// On va spawner quelque chose de random sur la m�me bordure � la place
	}

	if (random)		// Trouvons un spawn disponible, un peu randomly :)
	{
		it = Pick_Random_Interval(*list, border);		// Prend 1 intervalle random parmis cette liste!!!
		spawn = Pick_Rdm_Spwn_From_Interval(it);		// Prend un spawn Random parmis cette intervalle
	}

	Remove_Spawn_From_List(*list, it, border, spawn);	// Modifie l'intervalle pour exclure le spawn s�lectionn� par les DieuX

	//if (list == &scndary)			// Le nombre de spawn bannis par un prioritaire n'a pas besoin d'�tre enregistr�, puisque c'est d�j� fait au d�but
	bannedSpwn[border]++;		// + 1 au nombre de spawn exclut dans l'intervalle de cette bordure de spawn bot  

	Is_Border_Full(border);	// Bordure pleine?

	return spawn;	// we got it
}


// bingo bango














