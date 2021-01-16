#pragma once

#include "intervals.h"


namespace Intervals {

	// Exemples de recherches secondaires qui pourraient être faîtes si une recherche dans les listes échoue

	enum SearchConditions
	{
		 STOP, RDM_ALL, RDM_VALUE, RDM_INTERVAL, RDM_LIST, NXT_INTV, PRV_INTV, MAX_VALUE, MIN_VALUE, RESET_DFLT_LIST, RESET_ALL
	};

	class ManageIntervalLists {

		IntervalList* instance;			// La liste contentant tout les listes d'intervalles 
		IntervalList availableLists;	// La liste contenant tout les index des listes disponibles
		int listTot;					// Nombre de liste max.

	private:
		// EXTRACTION DE VALEURS,
		int Pick_Random_List();					// Prend une lsite parmis celles disponibles
		bool Pick(int &listNum, int &value, bool rdmValue = false, bool rdmList = false);		// Pogne une valeur provenant d'une list
		
		// ALTERNATIVE SEARCH
		/* Si un pick fail, on l'utilise l'une de ces méthodes pour essayer autre chose */
		bool Alt_Pick_Rdm_All(int &listNum, int &value);	// Pogne une valeur au hasard, provenant d'une liste au hasard
		bool Alt_Pick_Rdm_Value(int &listNum, int &value);	// Pogne une valeur au hasard provenant d'une même liste
		bool Alt_Pick_Rdm_List(int &listNum, int &value);	// Pogne une valeur provenant d'une liste au hasard


			// Tu pourrais faire des modifs ici en intégrant les conditions que tu veux quand tu cherche une donnée, du genre:
			// prend n'importe quel value au hasard si tu trouve pas
			// prend n'import quel list au hasard si tu trouve pas
			// prend la première valeur la plus grande
			// Si ta liste est empty, remplis là

		// STATUT DES LISTES
		bool Is_List_Empty(int index);							// Check si une liste est vide
		void Remove_Empty_List(int index);
		void Set_All_First_Interval();	// Set l'intervalle par défaut de tout les listes
		bool Is_Inbound(int list);

	public:
		// RECHERCHE DE VALEURS DISPONIBLES
		bool Pick_From_Lists(int &listNum, int &value, bool rdmValue = false, bool rdmList = false, SearchConditions search = STOP);		// Pogne une valeur provenant d'une list quelconque
		bool Find_List_With_Value(int value, int& listNum);		// Trouve une liste contenant cette valeur
		bool Find_Value(int listNum, int value);		// Trouve une liste contenant cette valeur
		bool Is_All_Empty();
		int Get_Default_Max(int list = 0) { return instance->dfltMax; } // prend le premier max par défaut
		int Get_Max_Available_Lists() { return availableLists.dfltMax; } // Nombre de list max possible

		// INITIALIZATION
		void Initialize_All_Lists(int min, int max);		// Avec les même valeurs!

		/* MODIFICATIONS */
		void Remove_Value(int listNum, int value);	 // enlève une valeur dans une liste
		void Remove_Value_Everywhere(int value);	 // enlève une valeur dans tout les listes
		void Add_Interval_On_Top(int border, int min, int max);	 // ajoute un intervalle dans une liste
		void Exclude_Interval_From_List(int listNum, int min, int max);		// retire un intervalle 


	   // RESET BUTTON
		void Empty_All_Lists();			// Vides les listes
		void Empty_List(int numList);	// Vides une liste
		void Reset_All_Lists();			// PRÉPARE LES LISTES POUR LE PROCHAIN CYCLE

		// Si tu veux ré-utiliser le même objet tout le temps
		void Resize(int lists, int min, int max)
		{
			if (instance)
			{

				////  Pas obligé, le destructeur devrait le faire automatiquement
				//// Destroy first
				//for (int i = 0; i < listTot; i++)
				//	instance[i].~IntervalList();		// Détruit les listes, et tous leurs intervalles
				//availableLists.~IntervalList();			// Delete la liste contenant les index des listes disponibles


				availableLists.Empty_List();	// vide à la place? c'est pas un pointeur dude
				delete[] instance;	// Delete deux fois????

			}

			listTot = lists;
			instance = new IntervalList[listTot];
			Initialize_All_Lists(min, max);
			availableLists.Initialize_List(0, listTot);				// Delete la liste contenant tout les listes
		}

		ManageIntervalLists(int lists, int min , int max)	// CONSTRUCTO
		{
			listTot = lists;
			instance = new IntervalList[listTot];
			Initialize_All_Lists(min, max);
			availableLists.Initialize_List(0, listTot);
		}

		~ManageIntervalLists() // DESTRUCTO
		{
			for (int i = 0; i < listTot; i++)
				instance[i].~IntervalList();		// Détruit les listes, et tous leurs intervalles

			availableLists.~IntervalList();			// Delete la liste contenant les index des listes disponibles
			delete[] instance;						// Delete la liste contenant tout les listes
		}
	};
}
