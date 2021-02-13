#pragma once 

#include "../grid/grid.h"

/*
POST-MORTEM

	L'idée d'un gestionneur d'interval dans une liste chaîné était bonne, mais l'utilisation du pointeur "previous" nécessaire à plusieurs méthodes à overcomplexifier tout le processus pour rien, en plus d'apporter
	d'innombrables bug lors de l'implentation...
*/



namespace Intervals 
{
	/* Fonctionne comme suit:			[ min, max [			* interval peut aussi n'avoir qu'une seule valeure possible ex [ 5,6 [ -> 5
		ex: min = 5, max = 10			[ 5 , 15 [
	*/

	struct Interval {
		int min = 0;	// Donne la valeur de départ de l'intervalle *la valeur min est tjrs inclut
		int max = 0;	// Donne la valeure de fin de l'intervalle. Cette valeur est exclut.
		Interval* nxt = nullptr;	
	};

	class IntervalList {				
	private:	
		friend class ManageIntervalLists;

		Interval* start = nullptr;
		Interval* end = nullptr;
		int count = 0;					// Le nombre d'intervalles figurant dans la liste
		int dfltMin = 0, dfltMax = 1;	// Le min et le max de base pour chaque intervalles

		// INFORMATION SUR LISTE
		bool Is_Empty();	
		bool Is_Mono_Interval(Interval* intval);				
		bool Cant_Be_Reduced_By_1(Interval* intval, int value);	
		bool Is_Value_Within(Interval* intval, int value);		
		bool Is_Interval_Null(Interval* intval);				
		bool Equals_Min(Interval* intval, int value);			
		bool Equals_Max_Minus_1(Interval* intval, int value);	

		// INITIALISATION
		void Set_Dflt_Interval(int min, int max) { dfltMin = min; dfltMax = max; }	
		void Empty_List();															
		void Reset_List();															// Détruot les intval et insère l'intervalle par défaut
		bool Set_First_Interval();												
		void Initialize_List(int min, int max);									

		// TROUVE UNE VALEUR DISPONIBLE
		bool Search_Value(int value);							
		Interval* Pick_Random_Interval(Interval* &previous );			
		int Pick_Random_Value(Interval* intval);	
		bool Pick_Value(Interval*& previous, Interval*& intval, int& value);


		// MODIFICATION DES LISTES
		void Modify_Min(Interval* &intval, int newMin);				
		void Modify_Max(Interval* &intval, int newMax);				
		void Destroy_Interval(Interval* &previous, Interval* &intval);				
		void Split_At_Value(Interval* &previous, Interval*& intval, int newMin);		
		void Exclude_Interval_From_Interval(Interval* &previous, Interval*& intval, int newMax, int  newMin);	
		void Exclude_Value_From_Interval(Interval* &previous, Interval* &intval, int value);	

		Interval* Create_Interval(Interval* &previous, int min, int max);				
		void Add_Interval_On_Top(int min, int max);					// Ajoute un intervalle de valeurs qui va combiner toute celle qui contiendrait l'une de ses valeur	// CETTE FONCTION EST BROKEN
		void Exclude_Interval_From_List(int min, int max);			
		

		// RETIRE UNE VALEUR
		void Find_And_Remove_Value(int value);

	protected:
		bool Pick(int& value, bool rdmValue);	

		~IntervalList()
		{
			Interval* it;

			while (it = start)
			{
				start = start->nxt;
				delete it;
			}
		}
	};
}