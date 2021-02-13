#include <cstdlib>

#include "manage_interval.h"


namespace Intervals
{
	bool ManageIntervalLists::Is_List_Empty(int listNum)		
	{
		return instance[listNum].Is_Empty();
	}
	bool ManageIntervalLists::Is_All_Empty()
	{
		if (availableLists.count)
			return false; 
		else 
			return true;
	}


	void ManageIntervalLists::Remove_Empty_List(int listNum)
	{
		Interval* it = availableLists.start;
		Interval* prev = NULL;

		if (Is_List_Empty(listNum))
		{
			for (size_t i = 0; i < availableLists.count; i++)
			{
				if (availableLists.Is_Value_Within(it, listNum))	
				{
					availableLists.Exclude_Value_From_Interval(prev, it, listNum);	
					break;
				}
				else
				{
					prev = it;
					it = it->nxt;
				}
			}		
		}
	}



	/* MODIFICATIONS */
	// *************
	bool ManageIntervalLists::Is_Inbound(int list)
	{
		if (list > listTot - 1 )	
			return false;

		if (list < 0)		
			return false;

		return true;
	}

	void ManageIntervalLists::Remove_Value(int listNum, int value)			
	{
		if (Is_Inbound(listNum))
		{
			instance[listNum].Find_And_Remove_Value(value);
			Remove_Empty_List(listNum);
		}
	}

	void ManageIntervalLists::Remove_Value_Everywhere(int value)	 
	{
		for (int i = 0; i < listTot; i++)		// implémentation lazy, essaie d'enlever une valeur dans des listes qui pourraient être vide
			Remove_Value(i, value);	
	}

	void ManageIntervalLists::Exclude_Interval_From_List(int listNum, int min, int max)
	{
		instance[listNum].Exclude_Interval_From_List(min, max);
		Remove_Empty_List(listNum);
	}

	void ManageIntervalLists::Add_Interval_On_Top(int listNum, int min, int max)
	{
		instance[listNum].Add_Interval_On_Top(min, max);
	}

	void ManageIntervalLists::Empty_All_Lists()			
	{
		for (int i = 0; i < listTot; i++)	
			instance[i].Empty_List();	
	}
	void ManageIntervalLists::Empty_List(int numList)				
	{
		instance[numList].Empty_List();
	}
	void ManageIntervalLists::Reset_All_Lists()		
	{
		for (int i = 0; i < listTot; i++)
			instance[i].Reset_List();
		
		availableLists.Reset_List();
	}
	void ManageIntervalLists::Set_All_First_Interval()	
	{
		for (int i = 0; i < listTot; i++)
			instance[i].Set_First_Interval();
	}



	// INITIALIZE TOUT LES LISTES UNIFORMÉMENT
	// ---------------------------------------

	void ManageIntervalLists::Initialize_All_Lists(int min, int max)		
	{
		for (int list = 0; list < listTot; list++)
			instance[list].Initialize_List(min, max);						
	}

	// SEARCHING!
	// ----------

	bool ManageIntervalLists::Find_Value(int listNum, int value)		
	{
		if (instance[listNum].count)
			return instance[listNum].Search_Value(value);
		else
			return false;
	}

	bool ManageIntervalLists::Find_List_With_Value(int value, int& listNum)	
	{
		int list = 0;
		Interval* it = availableLists.start;
	
		for (int i = 0; i < availableLists.count; i++)
		{
				list = availableLists.start->min;	

				if (instance[list].Search_Value(value))
				{
					listNum = list;
					return true;		// found it!
				}
				else

				it = it->nxt;
		}

		return false; // didn't find it :(
	}

	// Prend une liste parmis celles disponibles
	// -----------------------------------------

	int ManageIntervalLists::Pick_Random_List()			
	{
		Interval* it = NULL;
		int list;

		if (Is_All_Empty())	
			return -1;
		else
			list = rand() % availableLists.count;

		it = availableLists.start;
		
		for (int i = 0; i < list; i++)
		{
			it = it->nxt;		
		}
		
		list = rand() % (it->max - it->min) + it->min;

		return list;
	}


	bool ManageIntervalLists::Pick(int &listNum, int& value, bool rdmValue , bool rdmList )	
	{
		bool foundValue = false;

		if (rdmList)
		{
			listNum = Pick_Random_List();	
			
			if (listNum == -1)
				return foundValue; 
		}
		else
			if (instance[listNum].Is_Empty())	
				return foundValue;

		foundValue = instance[listNum].Pick(value, rdmValue);

		return foundValue;	
	}

	bool ManageIntervalLists::Pick_From_Lists(int& listNum, int& value, bool rdmValue , bool rdmList , SearchConditions search)		
	{
		bool foundValue = false;

		if (!Is_All_Empty())	
		{
			foundValue = Pick(listNum, value, rdmValue, rdmList);	

			if(!foundValue)			// Si échoue, on utilise l'une de ces méthodes pour faire d'autres recherches and shit
				switch (search)
				{
				case SearchConditions::STOP:
					break;
				case SearchConditions::RDM_ALL: foundValue = Alt_Pick_Rdm_All(listNum, value);		// Liste et valeurs aléatoires
					break;
				case SearchConditions::RDM_VALUE:
					break;
				case SearchConditions::RDM_INTERVAL:
					break;
				case SearchConditions::RDM_LIST:
					break;
				case SearchConditions::NXT_INTV:
					break;
				case SearchConditions::PRV_INTV:
					break;
				case SearchConditions::MAX_VALUE:
					break;
				case SearchConditions::MIN_VALUE:
					break;
				case SearchConditions::RESET_DFLT_LIST:
					break;
				case SearchConditions::RESET_ALL:
					break;
				}

			Remove_Empty_List(listNum);
		}

		return foundValue;	// Si tout les lists sont vides, bah, sorry, ya rien ici

	}

	// ALTERNATIVE SEARCH
	// ------------------

	bool ManageIntervalLists::Alt_Pick_Rdm_All(int& listNum, int& value)
	{
		bool foundValue = false;

		while (!foundValue)
		{
			foundValue = Pick(listNum, value, true, true);	// Pogne une valeur au hasard, provenant d'une liste au hasard
		}

		return foundValue;
	}		
	
	bool ManageIntervalLists::Alt_Pick_Rdm_Value(int& listNum, int& value)	// Pogne une valeur au hasard provenant d'une même liste
	{
		bool foundValue = false;

		if (instance[listNum].Is_Empty())	
			return foundValue;

		while (foundValue)
			foundValue = Pick(listNum, value, true, false);

		return foundValue;	
	}

	bool ManageIntervalLists::Alt_Pick_Rdm_List(int& listNum, int& value)	// Pogne une valeur provenant d'une liste au hasard
	{
		bool foundValue = false;

		while (foundValue)
			if (Find_List_With_Value(value, listNum))
			{
				foundValue = true;
				Pick(listNum, value, false, false);			
			}

		return foundValue;	
	}
}