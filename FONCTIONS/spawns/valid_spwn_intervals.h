#pragma once 

#include "../grid/spawngrid.h"



/*
 POST-MORTEM
	"Here comes the stuff of nightmares..."-
*/

/*
	Chaque bordures va contenir une liste de tout les spawns disponible durant un cycle de spawn
	À chaque fois qu'un spawner est sélectionner pour faire apparaître un bot, il sera neutraliser de la liste pour éviter de faire spawner deux bots 1 par dessus l'autre
	Avant chaque cycle de spawn, il sera possible de déterminer 1 intervalle prioritaire dans laquelle les spawns aléatoire
*/

/* Fonctionne comme suit:			[ min, max [			* interval peut aussi n'avoir qu'une seule valeure possible ex [ 5,6 [ -> 5
	ex: min = 5, max = 10			[ 5 , 15 [
*/

struct Interval {
	int min;	
	int max;	
	Interval* nxt;	
};

struct IntervalList {				
	Interval* start[4], * end[4];
	int numIntervals[4];		
};

class ValidSpwnIntervals {

private:
	friend class SpawnGrid;// Pour setter le maximum et min

	static IntervalList primary;	// La liste contentant tout les intervalles de spawns prioritaires
	static IntervalList scndary;	// La liste contenant les intervalles valides de spawns( excluant primary)
	

	static Interval* prev;		//  THIS IS THE ULTIMATE HOT GARBAGE I WAS WAITING FOR ALL MY LIFE!		

	static int maxVer;	
	static int maxHor;	
	static int bannedSpwn[4];	
	static bool borderIsFull[4];
	static bool allPrimeEmpty;	
	static bool isPriority;	// Détermine si on bannis un spawn qui est présent dans la liste prioritaire

	// INFORMATION SUR LISTE
	static bool Is_Secondary_List_Full(int border);	
	static bool Is_Secondary_List_Empty(int border);				
	static bool Are_Primary_Lists_Empty();			

	// RECHERCHE DE VALEUR
	static Interval* Find_Interval(int border, int spwNum, IntervalList* &theList);			
	static Interval* Set_First_Interval(int border);		
	static Interval* Pick_Random_Interval(const IntervalList& list, int border);
	static int Pick_Rdm_Spwn_From_Interval(Interval* intval);	

	// MODIFICATION DES LISTES
	static void Modify_Min(Interval* intval, int newMin);	
	static void Modify_Max(Interval* intval, int newMax);	
	static void Split_Interval_In_Two(IntervalList &list, int border, Interval* &intval, int newMin);
	static bool Exclude_Primary_Interval(int border, int min, int max);	// Exclut un intervalle de la liste primaire dans la liste secondaire
	static void Remove_Spawn_From_List(IntervalList &list, Interval* intval, int border, int bannedCrd);	

	// AJOUT/DESTRUCTION D'ITEM
	static Interval* Create_New_Interval(IntervalList& list, int border, int min, int max);				
	static void Destroy_Empty_Interval(IntervalList &list, Interval* intval, int border);	

	// INITIALISATION
	static void Set_Maximum_Ver(int max) { maxVer = max; }				
	static void Set_Maximum_Hor(int max) { maxHor = max; }				
	static void Set_Maximums(int hor, int ver)			
	{
		Set_Maximum_Ver(ver);
		Set_Maximum_Hor(hor);
	}

	// RESET BUTTON
	static void Empty_Primary_List();	// Ces listes doivent être vidé à la fin des spawns
	static void Reset_Secondary_List();	// Cette liste est Reset à la fin du spawn

public:
	static void Initialize_Valid_Spawn_List();

	// AJOUTE UN INTERVALLE PRIORITAIRE. Seul les scipts de Spawn font ça. 1 Max par bordure. Cuz I Said So!
	static bool Add_Primary_Interval(int border, int min, int max);	

	static int Pick_Valid_Spawn(int border, bool random, int spwNum = -1);	
	static bool Is_Border_Full(int border);			
	static int Pick_Primary_Border();
	static void Reset_For_Next_Cycle(){
		Empty_Primary_List();
		Reset_Secondary_List();
	}

};

