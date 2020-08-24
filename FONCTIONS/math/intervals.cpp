#include "intervals.h"

#include <cstdlib>
#include "../UI/direction.h"

namespace Intervals {

	bool IntervalList::Is_Empty()	// Liste est vide?
	{
		if (count)
			return false;
		else
			return true;
	}

	void IntervalList::Empty_List()															// Enl�ve tout les donn�es de la liste
	{
		Interval* it = start;
	
		while (it = start)
		{
			start = start->nxt;
			delete it;
		}

		start = end = NULL;	// safety
		count = 0;			// pu rien
	}

	void IntervalList::Reset_List()
	{
		Empty_List();	// vide
		Set_First_Interval(); // qekchose
	}

	// INITIALIZATION
	bool IntervalList::Set_First_Interval()		// Set le premier interval, soit de min � max
	{
		if (start)
			return false;			// t'avais pas vid� la liste avant

		start = end = new Interval;

		start->min = dfltMin;
		start->max = dfltMax;

		count = 1;

		return true;
	}

	// Premi�re intialisation
	void IntervalList::Initialize_List(int min, int max)				// intialize une lsite
	{
		Set_Dflt_Interval(min, max);
		Set_First_Interval();
	}

	// TROUVE UNE VALEUR DISPONIBLE
	// ----------------------------

	bool IntervalList::Search_Value(int value)			// trouve une valeur					PREVIOUS POINTERS EST TR�S AGA�ANT
	{
		Interval* it = start;

		if (value < start->min  || value >= end->max)	// On skip la recherche au complet si aucun �l�ment de la liste n'a cette valeur
			return false;

		while (it)
		{
			if (Is_Value_Within(it, value))
				return true;	// it's here
			else
				it = it->nxt;
		}

		return false;	// it Ain't here
	}

	bool IntervalList::Pick(int& value, bool rdmValue)	// On trouve un intervalle qui ensuite trouve un spawn disponible
	{
		Interval* intval = NULL, * prevIter = NULL;
		bool found = false;

		// SI TU VEUX PRENDRE UNE AUTRE VALEUR AU HASARD AU CAS O� CELLE-CI N'EST PAS TROUV�
		//if(!rdmValue)
		//	rdmValue = Pick_Value(prevIter, intval, value);	// vrai si trouv�
				// SI TU VEUX PRENDRE UNE AUTRE VALEUR AU HASARD AU CAS O� CELLE-CI N'EST PAS TROUV�

		if (!rdmValue)
			found = Pick_Value(prevIter, intval, value);	// vrai si trouv�

		if (rdmValue)
		{
			intval = Pick_Random_Interval(prevIter);
			value = Pick_Random_Value(intval);
			found = true;
		}

		if (found)
			Exclude_Value_From_Interval(prevIter, intval, value);	// �limine l'�l�ment de l'intervalle

		return found;	// retourne si on a trouv� ce qu'on cherchait								
	}


	int IntervalList::Pick_Random_Value(Interval* intval)	// On trouve une valeure dans un intervalle 
	{
		int value, length;

		length = intval->max - intval->min;			//	le nombre de spawn pr�sent dans l'intervalle
		value = rand() % length + intval->min;

		return value; // Extraction Complete!
	}

	Interval* IntervalList::Pick_Random_Interval(Interval*& previous)// On trouve un intervalle qui ensuite trouve un spawn disponible
	{
		Interval* intval;	// L'intervalle
		int intvalNum;		// Le combienti�me intervalle de la liste

		intvalNum = rand() % count;		//  Prend 1 # d'intervalle parmis le total pr�sent dans la liste
		intval = start;					// D�but de la liste, Intervalle num�ro 1!

		if (count != 1)				// % 1 donne toujours 1.		% > 1  peut donner 0		(par d�finition, un intervalle de z�ro n'existe pas)
			for (int i = 0; i < intvalNum; i++)
			{
				previous = intval;			// voil�!!
				intval = intval->nxt;
			}

		return intval;	// L'Intervalle !
	}

	// PREND UNE VALEUR NON-AL�ATOIREMENT
	// ----------------------------------

	bool IntervalList::Pick_Value(Interval*& previous, Interval*& intval, int& value)
	{
		static bool found; found = false;

		intval = previous = NULL;	// � chaque fois qu'on cherche un nouvel item, on va reset le previous* ptr
		intval = start;				// Premier �l�ment de la liste

		while (intval)	// liste non-vide
		{
			if (intval->min <= value)
				if (intval->max > value)
				{
					found = true;	// La donn�e est dans cet interval	     intrv >= min      intrv < max 
					break;
				}

			previous = intval;		// previous
			intval = intval->nxt;	// Passe au prochain
		}

		if (found)
			return true;
		else
			return false;
	}

	// INFORMATION SUR LES LISTES
	// --------------------------

	bool IntervalList::Is_Mono_Interval(Interval* intval)	// Si l'intervalle , ne  contient qu'une seule valeur
	{
		if (intval->max - intval->min == 1)	// Si on a intervalle de 1
			return true;
		else
			return false;
	}
	bool IntervalList::Is_Value_Within(Interval* intval, int value)		// Si l'interval est nul(devra �tre delete)
	{
		if (intval->min <= value && intval->max > value)		// La valeur Max est exclut implicitement
			return true;
		else
			return false;
	}
	bool IntervalList::Is_Interval_Null(Interval* intval)		// Si l'interval est nul(devra �tre delete) ?????????????????????????
	{
		if (intval->min == intval->max)
			return true;
		else
			return false;
	}
	bool IntervalList::Can_Be_Reduced_By_1(Interval* intval, int value)				// Si l'interval devient null , si r�duit
	{
		if (Is_Mono_Interval(intval) && Equals_Min(intval, value))		// R�duire l'intervalle le d�truirait
			return false;
		else
			return true;
	}
	bool IntervalList::Equals_Min(Interval* intval, int value)			// Valeur est �gal au minimum
	{
		if (intval->min == value)
			return true;
		else
			return false;
	}
	bool IntervalList::Equals_Max_Minus_1(Interval* intval, int value)	// Valeur est �gal au max - 1
	{
		if (intval->max - 1 == value)
			return true;
		else
			return false;
	}

	// RETIRE UNE VALEUR D'UN INTERVALLE
	// ---------------------------------

	void IntervalList::Find_And_Remove_Value(int value)	// Retire une valeur d'un intervalle. Mais doit d'abord le trouver
	{
		Interval* intval = start, * prev = NULL;

		if (!count)	// yo stais vide
			return;

		if (end->max <= value || start->min > value)	// On skip la recherche au complet si aucun �l�ment de la liste � une valeur suffisament �lev�e
			return;

		while (intval)
		{
			if (Is_Value_Within(intval, value))
				break;	// it's here
			else
			{
				prev = intval;
				intval = intval->nxt;
			}
		}

		if (intval)	// n'a pas atteint end->nxt = null
			Exclude_Value_From_Interval(prev, intval, value);
	}


	void IntervalList::Exclude_Value_From_Interval(Interval*& previous, Interval*& intval, int value)
	{
		if (!Can_Be_Reduced_By_1(intval, value))	// Si on a intervalle de 1  // Et qu'on doit r�duire une des deux extr�mit�s		
			Destroy_Interval(previous, intval);// On doit d�truire l'intervalle	
		else
		{
			if (Equals_Min(intval, value))	// On peut juste exclure le min 
				Modify_Min(intval, value + 1);
			else
				if (Equals_Max_Minus_1(intval, value))	// On peut juste modifier le max
					Modify_Max(intval, value);
				else
					Split_At_Value(previous, intval, value);	// Sinon on split l'intervalle en deux. Ceci en cr�er un nouvel qui sera plac� juste avant			
		}
	}

	void IntervalList::Modify_Min(Interval*& intval, int newMin)	// Augmente le min de 1
	{
		intval->min = newMin;	// Augmente la borne de min 	
	}
	void IntervalList::Modify_Max(Interval*& intval, int newMax)	// R�duit le Max de 1
	{
		intval->max = newMax;	// R�duit la borne de max 
	}

	// Delete un intervalle quand il est vide
	// --------------------------------------

	void IntervalList::Destroy_Interval(Interval*& previous, Interval*& intval)
	{
		if (intval == start && intval == end)	// 1 �l�ment dans la liste
		{
			delete intval;		// on le delete
			intval = start = end = NULL;	// bonne pratique
		}
		else
		{
			if (intval == start)	// Delete le d�but
			{
				start = start->nxt;
				delete intval;
				intval = start;	// �gal au prochain
			}
			else
				if (intval == end)	// end isnt recorded!!!
				{
					end = previous;
					delete intval;	// Delete l'�l�ment de la liste

					intval = previous->nxt = NULL;
				}
				else
					if (previous)	// Redirection des pointeurs
					{
						previous->nxt = intval->nxt;
						delete intval;	// Delete l'�l�ment de la liste

						intval = previous->nxt;	// Passe au prochain
					}
		}

		count--;	// -1 intervalle

	}

	// SPLIT UN INTERVALLE EN DEUX
	// ---------------------------

	void IntervalList::Split_At_Value(Interval*& previous, Interval*& intval, int newMax)	// Quand tu ajoute une nouvelle valeur � exclure dans la liste d'interval
	{
		int oldMax = intval->max;

		// INTERVALLE #1			
		Modify_Max(intval, newMax);	// R�duit l'intervalle originale

		// INTERVALLE #2
		Create_Interval(intval, newMax + 1, oldMax);	// Cr�er un nouvel intervalle suivant 
	}

	void IntervalList::Exclude_Interval_From_Interval(Interval*& previous, Interval*& intval, int newMax, int newMin)	// Cr�er un gap dans un intervalle avec un intervalle
	{
		if (newMax < intval->min || newMin > intval->max)	//	[old min, newmax,	[newMin, oldMax[   // j'ai des doutes icic
			throw "you fucked up";

		if (Equals_Min(intval, newMax) && newMin >= intval->max - 1)		// Exclut l'intervalle au complet
		{
			Destroy_Interval(previous, intval);
			return;
		}

		if (intval->min < newMax && newMin >= intval->max - 1)	// ne d�truit pas, change le max
		{
			Modify_Max(intval, newMax);
			return;
		}

		if (Equals_Min(intval, newMax) && newMin < intval->max - 1)	// ne d�trutit pas, change le min
		{
			Modify_Min(intval, newMin + 1);	// En excluant la valeur min
			return;
		}

		// Si ce trouve pas � aucune extremit�s
		int oldMax = intval->max;
		Modify_Max(intval, newMax);
		Create_Interval(intval, newMin + 1, oldMax);	// Cr�er un nouvel intervalle suivant 
	}

	// CR�ER UN NOUVEL INTERVALLE!!
	// ----------------------------

	Interval* IntervalList::Create_Interval(Interval*& previous, int min, int max)
	{
		static Interval* newIntval; newIntval = NULL;	// Fais des static cuz i dont know if it really helps

		newIntval = new Interval;	// Nouvel Intervalle
		newIntval->min = min;
		newIntval->max = max;
		newIntval->nxt = NULL;

		if (!count)	// D�but et fin
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

		count++;	// 1 de plus les amis!
		return newIntval;
	}

	void IntervalList::Add_Interval_On_Top(int min, int max)					// Ajoute un intervalle de valeurs qui va combiner toute celle qui contiendrait l'une de ses valeur
	{
		Interval* first = NULL;
		Interval* last = NULL;
		Interval* next = NULL;
		Interval* prev = NULL;
		int intvLeft;		// Nombre d'intervalle restant � chequer
		bool foundMin = false;		// Trouv� un intervalle contenant la valeur minimale
		int newMax = max;

		first = start;

		for (intvLeft = count; intvLeft > 0; intvLeft--)		// Le nombre d'�l�ments restants							//	Prend tout les intervalles qui contiennent l'intervalle � ajouter, et les combinent
		{																													//	ex: [1, 3[	[10 ,14[	min = -1
			if (first->min <= min)		// Trouv�!																			//		[5, 6[	[-4 , 0[	max = 10
			{																												//		Prend l'Intervalle contenant la valeur Min ex: -4																															//
				if (max <= first->max)	// l'intervalle �tait d�j� contenu au complet dans l'intervalle first				//		Delete les intervalles qui contiennet pas le premier
					return;																									//		Modify_Max(first, 14);

				foundMin = true;			
				intvLeft--;      //		Prend le plus grand Max: 14
				break;			// Trouv�, we out
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
			prev = NULL;	// Si tu trouve pas le min, tu dois quand m�me trouver le max		
			last = start;
			intvLeft = count;	// reset le counter
		}

		for (int i = intvLeft; i > 0; i--)		// Le nombre d'�l�ments restants
		{
			if (max <= last->max)
			{
				newMax = last->max;		// Le max fut trouv�
				Destroy_Interval(prev, last);
				break;
			}

			next = last->nxt;
			Destroy_Interval(prev, last);	// // Delete Tout les intervalles ne contenant pas le min et �tant plus petit que le max
		}

		if (foundMin)	// Si tu trouve pas le min, tu dois quand m�me trouver le max
			Modify_Max(first, newMax);	// Agrandi le premier intervalle trouv�, pour qu'il contienne le nouvel intervalle
		else
			Create_Interval(prev, min, max);	// From scratch. On va cr�er l'intervalle 
	}

	void IntervalList::Exclude_Interval_From_List(int min, int max)						// Retire un intervalle de valeurs de la liste
	{
		Interval* first = NULL;
		Interval* last = NULL;																									// Pour REMOVE un intervalle:  prendre tout les intervalles qui contiennent l'intervalle � enlever, et les deletes
		Interval* next = NULL;																									// ex: [1, 3[	[10 ,14[	min = -1
		Interval* prev = NULL;																									// 	[5, 6[	[-4 , 0[	max = 10
		int intvLeft;				// Nombre d'intervalle restant � checker													//
		bool foundMin = false;		// Trouv� un intervalle contenant la valeur minimale										// 	Si aucun Intervalle: SKIP. else
																																//		Prend l'intervalle contenant la min(-1): [-4 , 0[	(si y'en a un) Ajuste l'intervalle min en lui assisgnant min(-1) comme nouveau max: Modify_Max(min)
		if (!count)  // Si aucun Intervalle: SKIP																				// 		Prend l'intervalle contenant le max(10): [10 ,14[	(si y'en a un) Ajuste l'intervalle max en lui assisgnant max(14) comme nouveau min: Modify_Min(max)
			return;																												//
																																//	Delete TOUT les autres intervalles se trouvant entre ces deux intervalles
		first = start; // d�but de listeS																						  

		for (intvLeft = count; intvLeft > 0; intvLeft--)		// Le nombre d'�l�ments restants		
		{
			if (first->min <= min)
			{
				if (max <= first->max)			// Interval trouv�
				{
					Exclude_Interval_From_Interval(prev, first, min, max);	// si t'arrive ici, c'est que les TOUT valeurs que tu veux exlure se trouvent TOUS dans 1 seul interval. ex oppos�  : ToExclude [-5 , 10} interval {0, 10} = marchera pas
					return;
				}

				foundMin = true;				//	Prend le plus grand Max: 14
				intvLeft--;						// R�duit de 1 le nombre � checker la fin
				break;
			}
			else
			{
				prev = first;
				first = first->nxt;	// passse au prochain
			}
		}

		//----------------------------------------------------------------------------------------	

		// La valeur minimal fut trouv� dans un intervalle. Maintenant on v�rifie si des valeurs de la liste se trouve entre le min et le max

		if (foundMin)
		{
			// Si l'intervalle contenant la valeur min est trop petit pour �tre r�duit, on le d�truit
			if (Equals_Min(first, min))
			{
				Destroy_Interval(prev, first);	// prev

				if (intvLeft)		// Si il restait des �l�ments � checker
					last = first;	//(first devient le next, i know, its confusing :/)		// MIGHT NOT NEED TO PASS BY REF IN THE END
			}
			else
			{
				Modify_Max(first, min);	// R�duit son maximum
				prev = first;	// J'AI AJOUT� �A UN PEU DANS LE VIDE CAR �A CRASHAIT
				last = first->nxt; // cherchons si un intervalle contient la valeur max
			}
		}
		else
		{
			prev = NULL;	// Si tu trouve pas le min, tu dois quand m�me trouver le max		
			last = start;
			intvLeft = count;	// reset le counter
		}

		for (int i = intvLeft; i > 0; i--)		// Le nombre d'�l�ments restants
		{
			if (max <= last->max)
			{
				// Le max fut trouv�!
				// Si l'intervalle serait r�duit � un intervalle null par le nouveau min
				if (max >= last->max - 1)
					Destroy_Interval(prev, last);
				else
					Modify_Min(last, max + 1);	// R�duit son minimum, en excluant la valeur minimal elle m�me
				break;	// we done here
			}
			else
			{
				next = last->nxt;
				Destroy_Interval(prev, last);	// // Delete Tout les intervalles trouv�s
			}
		}

	}
}