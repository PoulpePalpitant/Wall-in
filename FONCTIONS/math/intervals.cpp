#include "intervals.h"

#include <cstdlib>
#include "../UI/direction.h"

namespace Intervals {

	bool IntervalList::Is_Empty()
	{
		if (count)
			return false;
		else
			return true;
	}

	void IntervalList::Empty_List()														
	{
		Interval* it = start;
	
		while (it = start)
		{
			start = start->nxt;
			delete it;
		}

		start = end = NULL;	
		count = 0;			
	}

	void IntervalList::Reset_List()
	{
		Empty_List();	
		Set_First_Interval(); 
	}

	bool IntervalList::Set_First_Interval()	
	{
		if (start)
			return false;			

		start = end = new Interval;

		start->min = dfltMin;
		start->max = dfltMax;

		count = 1;

		return true;
	}

	void IntervalList::Initialize_List(int min, int max)				
	{
		Set_Dflt_Interval(min, max);
		Set_First_Interval();
	}

	bool IntervalList::Search_Value(int value)			
	{
		Interval* it = start;

		if (value < start->min  || value >= end->max)	// On skip la recherche au complet si aucun élément de la liste n'a cette valeur
			return false;

		while (it)
		{
			if (Is_Value_Within(it, value))
				return true;	
			else
				it = it->nxt;
		}

		return false;	
	}

	bool IntervalList::Pick(int& value, bool rdmValue)	
	{
		Interval* intval = NULL, * prevIter = NULL;
		bool found = false;

		if (!rdmValue)
			found = Pick_Value(prevIter, intval, value);	

		if (rdmValue)
		{
			intval = Pick_Random_Interval(prevIter);	// Ceci pourrait fail si aucun interval n'est disponible
			value = Pick_Random_Value(intval);
			found = true;
		}

		if (found)
			Exclude_Value_From_Interval(prevIter, intval, value);	

		return found;								
	}


	int IntervalList::Pick_Random_Value(Interval* intval)	
	{
		int value, length;

		length = intval->max - intval->min;			
		value = rand() % length + intval->min;

		return value; 
	}

	Interval* IntervalList::Pick_Random_Interval(Interval*& previous)
	{
		Interval* intval;	
		int intvalNum;		

		intvalNum = rand() % count;		
		intval = start;					// Début de la liste, Intervalle numéro 1!

		if (count != 1)				// % 1 donne toujours 1.		% > 1  peut donner 0		(par définition, un intervalle de zéro n'existe pas)
			for (int i = 0; i < intvalNum; i++)
			{
				previous = intval;			
				intval = intval->nxt;
			}

		return intval;	
	}

	// PREND UNE VALEUR NON-ALÉATOIREMENT
	// ----------------------------------

	bool IntervalList::Pick_Value(Interval*& previous, Interval*& intval, int& value)
	{
		static bool found; found = false;

		intval = previous = NULL;	// À chaque fois qu'on cherche un nouvel item, on va reset le previous* ptr
		intval = start;				

		while (intval)	
		{
			if (intval->min <= value)
				if (intval->max > value)
				{
					found = true;	
					break;
				}

			previous = intval;		
			intval = intval->nxt;	
		}

		if (found)
			return true;
		else
			return false;
	}

	// INFORMATION SUR LES LISTES
	// --------------------------

	bool IntervalList::Is_Mono_Interval(Interval* intval)
	{
		if (intval->max - intval->min == 1)
			return true;
		else
			return false;
	}
	bool IntervalList::Is_Value_Within(Interval* intval, int value)		
	{
		if (intval->min <= value && intval->max > value)		
			return true;
		else
			return false;
	}
	bool IntervalList::Is_Interval_Null(Interval* intval)		// Si l'interval est nul(devra être delete) ?????????????????????????
	{
		if (intval->min == intval->max)
			return true;
		else
			return false;
	}
	
	// Cette méthode est vraisemblablement la même affaire que Is_Mono_Interval
	bool IntervalList::Cant_Be_Reduced_By_1(Interval* intval, int value)				
	{
		if (Is_Mono_Interval(intval) && Equals_Min(intval, value))		
			return false;
		else
			return true;
	}
	bool IntervalList::Equals_Min(Interval* intval, int value)			
	{
		if (intval->min == value)
			return true;
		else
			return false;
	}
	bool IntervalList::Equals_Max_Minus_1(Interval* intval, int value)
	{
		if (intval->max - 1 == value)
			return true;
		else
			return false;
	}

	// RETIRE UNE VALEUR D'UN INTERVALLE
	// ---------------------------------

	void IntervalList::Find_And_Remove_Value(int value)	
	{
		Interval* intval = start, * prev = NULL;

		if (!count)
			return;

		if (end->max <= value || start->min > value)	
			return;

		while (intval)
		{
			if (Is_Value_Within(intval, value))
				break;
			else
			{
				prev = intval;
				intval = intval->nxt;
			}
		}

		if (intval)	
			Exclude_Value_From_Interval(prev, intval, value);
	}


	void IntervalList::Exclude_Value_From_Interval(Interval*& previous, Interval*& intval, int value)
	{
		if (!Cant_Be_Reduced_By_1(intval, value))	
			Destroy_Interval(previous, intval); 
		else
		{
			if (Equals_Min(intval, value))	// On peut juste exclure le min 
				Modify_Min(intval, value + 1);
			else
				if (Equals_Max_Minus_1(intval, value))	// On peut juste modifier le max
					Modify_Max(intval, value);
				else
					Split_At_Value(previous, intval, value);	// Sinon on split l'intervalle en deux. Ceci en créer un nouvel qui sera placé juste avant			
		}
	}

	void IntervalList::Modify_Min(Interval*& intval, int newMin)	
	{
		intval->min = newMin;	
	}
	void IntervalList::Modify_Max(Interval*& intval, int newMax)	
	{
		intval->max = newMax;	
	}

	// Delete un intervalle quand il est vide
	// --------------------------------------

	void IntervalList::Destroy_Interval(Interval*& previous, Interval*& intval)
	{
		if (intval == start && intval == end)	
		{
			delete intval;		
			intval = start = end = NULL;	
		}
		else
		{
			if (intval == start)	
			{
				start = start->nxt;
				delete intval;
				intval = start;	// Égal au prochain
			}
			else
				if (intval == end)	
				{
					end = previous;
					delete intval;	

					intval = previous->nxt = NULL;
				}
				else
					if (previous)	// Redirection des pointeurs
					{
						previous->nxt = intval->nxt;
						delete intval;

						intval = previous->nxt;
					}
		}

		count--;	

	}

	// SPLIT UN INTERVALLE EN DEUX
	// ---------------------------

	void IntervalList::Split_At_Value(Interval*& previous, Interval*& intval, int newMax)	
	{
		int oldMax = intval->max;

		// INTERVALLE #1			
		Modify_Max(intval, newMax);	// Réduit l'intervalle originale

		// INTERVALLE #2
		Create_Interval(intval, newMax + 1, oldMax);	// Créer un nouvel intervalle suivant 
	}

	void IntervalList::Exclude_Interval_From_Interval(Interval*& previous, Interval*& intval, int newMax, int newMin)	
	{
		if (newMax < intval->min || newMin > intval->max)	//	[old min, newmax,	[newMin, oldMax[   // j'ai des doutes icic
			throw "you fucked up";

		if (Equals_Min(intval, newMax) && newMin >= intval->max - 1)		// Exclut l'intervalle au complet
		{
			Destroy_Interval(previous, intval);
			return;
		}

		if (intval->min < newMax && newMin >= intval->max - 1)	// ne détruit pas, change le max
		{
			Modify_Max(intval, newMax);
			return;
		}

		if (Equals_Min(intval, newMax) && newMin < intval->max - 1)	// ne détrutit pas, change le min
		{
			Modify_Min(intval, newMin + 1);	// En excluant la valeur min
			return;
		}

		// Si ce trouve pas à aucune extremités
		int oldMax = intval->max;
		Modify_Max(intval, newMax);
		Create_Interval(intval, newMin + 1, oldMax);	
	}

	// CRÉER UN NOUVEL INTERVALLE!!
	// ----------------------------

	Interval* IntervalList::Create_Interval(Interval*& previous, int min, int max)
	{
		static Interval* newIntval; newIntval = NULL;	// Fais des static cuz i dont know if it really helps

		newIntval = new Interval;	
		newIntval->min = min;
		newIntval->max = max;
		newIntval->nxt = NULL;

		if (!count)	
			start = end = newIntval;
		else
			if (previous->nxt == NULL)
				end = end->nxt = newIntval;
			else
				if (previous == NULL)
					start = newIntval;
				else
				{
					newIntval->nxt = previous->nxt;
					previous->nxt = newIntval;
				}

		count++;	
		return newIntval;
	}


	// This is where the shit hits the fan

	void IntervalList::Add_Interval_On_Top(int min, int max)					// Ajoute un intervalle de valeurs qui va combiner toute celle qui contiendrait l'une de ses valeur
	{
		Interval* first = NULL;
		Interval* last = NULL;
		Interval* next = NULL;
		Interval* prev = NULL;
		int intvLeft;		
		bool foundMin = false;		
		int newMax = max;

		first = start;

		for (intvLeft = count; intvLeft > 0; intvLeft--)		// Le nombre d'éléments restants							//	Prend tout les intervalles qui contiennent l'intervalle à ajouter, et les combinent
		{																													//	ex: [1, 3[	[10 ,14[	min = -1
			if (first->min <= min)		// Trouvé!																			//		[5, 6[	[-4 , 0[	max = 10
			{																												//		Prend l'Intervalle contenant la valeur Min ex: -4																															//
				if (max <= first->max)	// l'intervalle était déjà contenu au complet dans l'intervalle first				//		Delete les intervalles qui contiennet pas le premier
					return;																									//		Modify_Max(first, 14);

				foundMin = true;			
				intvLeft--;     
				break;			
			}
			else
			{
				prev = first;
				first = first->nxt;
			}
		}
		//----------------------------------------------------------------------------------------

		if (foundMin)
			last = first->nxt; // cherchons si un intervalle contient la valeur max		
		else
		{
			prev = NULL;	// Si tu trouve pas le min, tu dois quand même trouver le max		
			last = start;
			intvLeft = count;	// reset le counter
		}

		for (int i = intvLeft; i > 0; i--)		// Le nombre d'éléments restants
		{
			if (max <= last->max)
			{
				newMax = last->max;		// Le max fut trouvé
				Destroy_Interval(prev, last);
				break;
			}

			next = last->nxt;
			Destroy_Interval(prev, last);	// // Delete Tout les intervalles ne contenant pas le min et étant plus petit que le max
		}

		if (foundMin)	// Si tu trouve pas le min, tu dois quand même trouver le max
			Modify_Max(first, newMax);	// Agrandi le premier intervalle trouvé, pour qu'il contienne le nouvel intervalle
		else
			Create_Interval(prev, min, max);	// From scratch. On va créer l'intervalle 
	}

	void IntervalList::Exclude_Interval_From_List(int min, int max)						
	{
		Interval* first = NULL;
		Interval* last = NULL;																									// Pour REMOVE un intervalle:  prendre tout les intervalles qui contiennent l'intervalle à enlever, et les deletes
		Interval* next = NULL;																									// ex: [1, 3[	[10 ,14[	min = -1
		Interval* prev = NULL;																									// 	[5, 6[	[-4 , 0[	max = 10
		int intvLeft;				// Nombre d'intervalle restant à checker													//
		bool foundMin = false;		// Trouvé un intervalle contenant la valeur minimale										// 	Si aucun Intervalle: SKIP. else
																																//		Prend l'intervalle contenant la min(-1): [-4 , 0[	(si y'en a un) Ajuste l'intervalle min en lui assisgnant min(-1) comme nouveau max: Modify_Max(min)
		if (!count)  // Si aucun Intervalle: SKIP																				// 		Prend l'intervalle contenant le max(10): [10 ,14[	(si y'en a un) Ajuste l'intervalle max en lui assisgnant max(14) comme nouveau min: Modify_Min(max)
			return;																												//
																																//	Delete TOUT les autres intervalles se trouvant entre ces deux intervalles
		first = start; 																					  

		for (intvLeft = count; intvLeft > 0; intvLeft--)				
		{
			if (first->min <= min)
			{
				if (max <= first->max)			
				{
					Exclude_Interval_From_Interval(prev, first, min, max);	// si t'arrive ici, c'est que les TOUT valeurs que tu veux exlure se trouvent TOUS dans 1 seul interval. ex opposé  : ToExclude [-5 , 10} interval {0, 10} = marchera pas
					return;
				}

				foundMin = true;				
				intvLeft--;					
				break;
			}
			else
			{
				prev = first;
				first = first->nxt;
			}
		}

		//----------------------------------------------------------------------------------------	

		// La valeur minimal fut trouvé dans un intervalle. Maintenant on vérifie si des valeurs de la liste se trouve entre le min et le max

		if (foundMin)
		{
			// Si l'intervalle contenant la valeur min est trop petit pour être réduit, on le détruit
			if (Equals_Min(first, min))
			{
				Destroy_Interval(prev, first);	// prev

				if (intvLeft)		// Si il restait des éléments à checker
					last = first;	//(first devient le next, i know, its confusing :/)		// MIGHT NOT NEED TO PASS BY REF IN THE END
			}
			else
			{
				Modify_Max(first, min);	// Réduit son maximum
				prev = first;	// J'AI AJOUTÉ ÇA UN PEU DANS LE VIDE CAR ÇA CRASHAIT
				last = first->nxt; // cherchons si un intervalle contient la valeur max
			}
		}
		else
		{
			prev = NULL;	// Si tu trouve pas le min, tu dois quand même trouver le max		
			last = start;
			intvLeft = count;	// reset le counter
		}

		for (int i = intvLeft; i > 0; i--)		// Le nombre d'éléments restants
		{
			if (max <= last->max)
			{
				// Le max fut trouvé!
				if (max >= last->max - 1)
					Destroy_Interval(prev, last);
				else
					Modify_Min(last, max + 1);	// Réduit son minimum, en excluant la valeur minimal elle même
				break;	// we done here
			}
			else
			{
				next = last->nxt;
				Destroy_Interval(prev, last);	// // Delete Tout les intervalles trouvés
			}
		}

	}
}