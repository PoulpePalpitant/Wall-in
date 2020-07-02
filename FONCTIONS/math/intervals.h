#pragma once 

#include "../grid/grid.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace interval 
{

	/* Fonctionne comme suit:			[ min, max [			* interval peut aussi n'avoir qu'une seule valeure possible ex [ 5,6 [ -> 5
		ex: min = 5, max = 10			[ 5 , 15 [
	*/

	struct Interval {
		int min;	// Donne la valeur de départ de l'intervalle * la valeur min est tjrs inclut
		int max;	// Donne la valeure de fin de l'intervalle. Cette valeur est exclut.
		Interval* nxt;	// Prochain intervalle
	};

	struct IntervalList {				// Liste contenant tout les intervalles où les bots peuvent spawner

		Interval* start, * end;
		int id;						// Si tu fais un intervalle en Coord XY, l'id pourrait être le X, et l'interval le Y
		IntervalList* nxt;
	};


	class ManageIntervals {

		static IntervalList* instance;	// La liste contentant tout les intervalles de spawns prioritaires
		static int MAX_LISTS;
	private:
		static IntervalList list;	// La liste contentant tout les intervalles de spawns prioritaires
		static Interval* prev;		// 1 Seul Itérateur, pointe vers un élément précédant			
		static int min, max;		// Le min et le max de base pour chaque intervalles
		static bool allPrimeEmpty;	// Tout les listes primaires sont vides

		ManageIntervals(int numLists)
		{
			MAX_LISTS = numLists;
			instance = new IntervalList[MAX_LISTS];
		}


		// INFORMATION SUR LISTE
		static bool Is_Secondary_List_Full(int border);	// Liste secondaire est pleine?
		static bool Is_Secondary_List_Empty(int border);				// Liste Secondaire est vide?
		static bool Are_Primary_Lists_Empty();			// Vérification de ça

		// RECHERCHE DE VALEUR
		static Interval* Find_Interval(int border, int spwNum, IntervalList*& theList);			// Trouve un interval à l'aide d'une coord
		static Interval* Set_First_Interval(int border);		// Set le premier interval, soit de "0 à Max Number of Spawn on border"
		static Interval* Pick_Random_Interval(const IntervalList& list, int border);	// Prend un interval random parmis la liste figurant sur une bordure
		static int Pick_Rdm_Spwn_From_Interval(Interval* intval);	// Génère la coordonnée de spawn!

		// MODIFICATION DES LISTES
		static void Modify_Min(Interval* intval, int newMin);	// Augmente le min de 1
		static void Modify_Max(Interval* intval, int newMax);	// Réduit le Max de 1
		static void Split_Interval_In_Two(IntervalList& list, int border, Interval*& intval, int newMin);	// Quand tu ajoute une nouvelle valeur à exclure dans la liste d'interval
		static bool Exclude_Primary_Interval(int border, int min, int max);	// Exclut un intervalle de la liste primaire dans la liste secondaire
		static void Remove_Spawn_From_List(IntervalList& list, Interval* intval, int border, int bannedCrd);	// Retire un spawn dans une liste 

		// AJOUT/DESTRUCTION D'ITEM
		static Interval* Create_New_Interval(IntervalList& list, int border, int min, int max);				// Créer un Nouvel intervalle!!
		static void Destroy_Empty_Interval(IntervalList& list, Interval* intval, int border);	// Delete un intervalle quand il est vide

		// INITIALISATION
		static void Set_Maximum_Ver(int max) { maxVer = max; }				// setup le maximum de spawn sur la bordure au début du niveau
		static void Set_Maximum_Hor(int max) { maxHor = max; }				// setup le maximum de spawn sur la bordure au début du niveau
		static void Set_Maximums(int hor, int ver)			// setup le maximum de spawn sur la bordure au début du niveau
		{
			Set_Maximum_Ver(ver);
			Set_Maximum_Hor(hor);
		}

		// RESET BUTTON
		static void Empty_Primary_List();	// Ces listes doivent être vidé à la fin des spawns
		static void Reset_Secondary_List();	// Cette liste est Reset à la fin du spawn

	public:
		// INITIALIZATION
		static void Initialize_Valid_Spawn_List();

		// AJOUTE UN INTERVALLE PRIORITAIRE. Seul les scipts de Spawn font ça. 1 Max par bordure. Cuz I Said So!
		static bool Add_Primary_Interval(int border, int min, int max);

		// TROUVE UN SPAWN
		static int Pick_Valid_Spawn(int border, bool random, int spwNum = -1);	// On trouve un intervalle qui ensuite trouve un spawn disponible

		// TROUVE UNE BORDER DISPONIBLE
		static bool Is_Border_Full(int border);			// La bordure n'a plus aucun intervalle de disponible
		static int Pick_Primary_Border();	// Prend une bordure contenant une liste primaire

		// PRÉPARE LES LISTES POUR LE PROCHAIN CYCLE
		static void Reset_For_Next_Cycle() {
			Empty_Primary_List();
			Reset_Secondary_List();
		}

	};

}