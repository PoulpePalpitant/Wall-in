#pragma once

#include "intervals.h"


namespace Intervals {

	enum SearchConditions
	{
		 STOP, RDM_ALL, RDM_VALUE, RDM_INTERVAL, RDM_LIST, NXT_INTV, PRV_INTV, MAX_VALUE, MIN_VALUE, RESET_DFLT_LIST, RESET_ALL
	};

	class ManageIntervalLists {

		IntervalList* instance;			// Les listes
		IntervalList availableLists;	// Index des listes disponibles
		int listTot;					

	private:
		// EXTRACTION DE VALEURS,
		int Pick_Random_List();			
		bool Pick(int &listNum, int &value, bool rdmValue = false, bool rdmList = false);		
		
		// ALTERNATIVE SEARCH
		/* Si un pick fail, on l'utilise l'une de ces méthodes pour essayer autre chose */
		bool Alt_Pick_Rdm_All(int &listNum, int &value);	// Pogne une valeur au hasard, provenant d'une liste au hasard
		bool Alt_Pick_Rdm_Value(int &listNum, int &value);	// Pogne une valeur au hasard provenant d'une même liste
		bool Alt_Pick_Rdm_List(int &listNum, int &value);	// Pogne une valeur provenant d'une liste au hasard

		// STATUT DES LISTES
		bool Is_List_Empty(int index);							
		void Remove_Empty_List(int index);
		void Set_All_First_Interval();	
		bool Is_Inbound(int list);

	public:
		// RECHERCHE DE VALEURS DISPONIBLES
		bool Pick_From_Lists(int &listNum, int &value, bool rdmValue = false, bool rdmList = false, SearchConditions search = STOP);		
		bool Find_List_With_Value(int value, int& listNum);		
		bool Find_Value(int listNum, int value);		
		bool Is_All_Empty();
		int Get_Default_Max(int list = 0) { return instance->dfltMax; } 
		int Get_Max_Available_Lists() { return availableLists.dfltMax; }

		// INITIALIZATION
		void Initialize_All_Lists(int min, int max);		

		/* MODIFICATIONS */
		void Remove_Value(int listNum, int value);	 
		void Remove_Value_Everywhere(int value);	 
		void Add_Interval_On_Top(int border, int min, int max);
		void Exclude_Interval_From_List(int listNum, int min, int max);


	   // RESET BUTTON
		void Empty_All_Lists();			
		void Empty_List(int numList);	
		void Reset_All_Lists();			

		void Resize(int lists, int min, int max)
		{
			if (instance)
			{
				availableLists.Empty_List();	
				delete[] instance;	
			}

			listTot = lists;
			instance = new IntervalList[listTot];
			Initialize_All_Lists(min, max);
			availableLists.Initialize_List(0, listTot);	
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
				instance[i].~IntervalList();		

			availableLists.~IntervalList();			
			delete[] instance;						
		}
	};
}
