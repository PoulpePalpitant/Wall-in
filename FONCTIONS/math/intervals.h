#pragma once 

#include "../grid/grid.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Intervals 
{

	/* Fonctionne comme suit:			[ min, max [			* interval peut aussi n'avoir qu'une seule valeure possible ex [ 5,6 [ -> 5
		ex: min = 5, max = 10			[ 5 , 15 [
	*/

	struct Interval {
		int min = 0;	// Donne la valeur de départ de l'intervalle * la valeur min est tjrs inclut
		int max = 0;	// Donne la valeure de fin de l'intervalle. Cette valeur est exclut.
		Interval* nxt = nullptr;	// Prochain intervalle
	};

	class IntervalList {				// Liste contenant tout les intervalles où les bots peuvent spawner
	private:	
		friend class ManageIntervalLists;

		Interval* start = nullptr;
		Interval* end = nullptr;
		int count = 0;						// Le nombre d'intervalles figurant dans la liste
		int dfltMin = 0, dfltMax = 0;	// Le min et le max de base pour chaque intervalles

		// INFORMATION SUR LISTE
		bool Is_Empty();	// Liste est vide?
		bool Is_Mono_Interval(Interval* intval);				// Si l'intervalle, ne  contient qu'une seule valeur
		bool Can_Be_Reduced_By_1(Interval* intval, int value);		// Si l'interval devient null, si réduit par une certaine valeur
		bool Is_Value_Within(Interval* intval, int value);		// Si l'interval est nul(devra être delete)
		bool Is_Interval_Null(Interval* intval);				// Si l'interval est nul(devra être delete) ?????????????????????????
		bool Equals_Min(Interval* intval, int value);			// Valeur est égal au minimum
		bool Equals_Max_Minus_1(Interval* intval, int value);	// Valeur est égal au max - 1

		// INITIALISATION
		void Set_Dflt_Interval(int min, int max) { dfltMin = min; dfltMax = max; }		// setup le min et max par dflaut
		void Empty_List();															// Enlève tout les données de la liste
		void Reset_List();															// Détruot les intval et insère l'intervalle par défaut
		bool Set_First_Interval();													// Set le premier interval, soit de min à max
		void Initialize_List(int min, int max);										// Set le dflt min/max et créer un interval

		// TROUVE UNE VALEUR DISPONIBLE
		bool Search_Value(int value);							// trouve une valeur
		Interval* Pick_Random_Interval(Interval* &previous );			// On trouve un intervalle qui ensuite trouve un spawn disponible
		int Pick_Random_Value(Interval* intval);	// On trouve un intervalle qui ensuite trouve un spawn disponible
		bool Pick_Value(Interval*& previous, Interval*& intval, int& value);


		// MODIFICATION DES LISTES
		void Modify_Min(Interval* &intval, int newMin);				// Augmente le min de 1
		void Modify_Max(Interval* &intval, int newMax);				// Réduit le Max de 1
		void Destroy_Interval(Interval* &previous, Interval* &intval);				// Si un intervalle est vide, on le détruit
		void Split_At_Value(Interval* &previous, Interval*& intval, int newMin);		// Quand tu ajoute une nouvelle valeur à exclure dans la liste d'interval
		void Exclude_Interval_From_Interval(Interval* &previous, Interval*& intval, int newMax, int  newMin);	// Créer un gap dans un intervalle avec un intervalle
		void Exclude_Value_From_Interval(Interval* &previous, Interval* &intval, int value);	// Retire une valeur d'un intervalle

		Interval* Create_Interval(Interval* &previous, int min, int max);				// Créer un Nouvel intervalle unique
		void Add_Interval_On_Top(int min, int max);					// Ajoute un intervalle de valeurs qui va combiner toute celle qui contiendrait l'une de ses valeur	// CETTE FONCTION EST BROKEN
		void Exclude_Interval_From_List(int min, int max);						// Retire un intervalle de valeurs de la liste
		

		// RETIRE UNE VALEUR
		void Find_And_Remove_Value(int value);	// Retire une valeur d'un intervalle

	protected:
		bool Pick(int& value, bool rdmValue);	// On trouve un intervalle qui ensuite trouve un spawn disponible

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