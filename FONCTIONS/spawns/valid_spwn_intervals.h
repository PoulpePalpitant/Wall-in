#pragma once 

//#include "../grid/managegrids.h"
#include "../grid/spawngrid.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Fonctionne comme suit:			[ min, max [			* interval peut aussi n'avoir qu'une seule valeure possible ex [ 5,6 [ -> 5
	ex: min = 5, max = 10			[ 5 , 15 [
*/

struct Interval {
	int min;	// Donne la valeur de d�part de l'intervalle * la valeur min est tjrs inclut
	int max;	// Donne la valeure de fin de l'intervallle. Cette valeur est exclut.
	Interval* nxt;	// Prochain intervalle
};

struct IntervalList {				// Liste contenant tout les intervalles o� les bots peuvent spawner
	Interval* start[4], * end[4];
	int numIntervals[4];			// Le nombre d'intervalles figurant dans chacune des listes
};

/*
	L'INTERVALLE DE SPAWN EST CALL� D'AVANCE.
	Cette intervalle est aussi ajout� � la liste  ici.
	Tu g�n�re une cood al�atoire dedans dans ta fonction comme d'hab.
	Ensuite tu viens ici pour v�rifier si �a rentre dans son intervalle.
	#1 Le premier spawn devrait marcher.
	Par contre, tu va ajouter cette valeur l� dans la liste des banned
	Ce que �a va faire, c'est modifier l'intervalle pour soit le splitter en deux, ou r�duire les bornes Max/Min. Dans les deux cas, une valeur de l'interval de base est maintenant indisponible
	Ce qui faudrait: c'est que pour chaque spawn succ�quant, on g�n�re un nombre qui se situait ENTRE les bornes originales � partir d'ici

	Il faut donc pouvoir v�rifier:
	- queck chose qui block le program quand l'interval original est trop fat
	-si un interval se situe dans l'intervalle originale
	--trouv� chacun des intervalles qui se situe dans les bornes originels
	--- choisir randomly un de ces intervalles
	- G�n�r� un nombre � partir de �a
	-si il n'y a plus aucun intervalle de disponibles dans ces bornes

	// O�, TU G�N�RE UNE COORD AL�ATOIRE JUSQU'� CE QUE TU TROUVE QUEK CHOSE DE LIBRE
*/
// SI TON INTERVAL DE SPAWN EST F


/* 
	Chaque bordures va contenir une liste de tout les spawns disponible durant un cycle de spawn 
	� chaque fois qu'un spawner est s�lectionner pour faire appara�tre un bot, il sera neutraliser de la liste pour �viter de faire spawner deux bonnes 1 par dessus l'autre
	Avant chaque cycle de spawn, il sera possible de d�terminer 1 intervalle prioritaire dans laquelle les spawns al�atoire
*/
class ValidSpwnIntervals {

private:
	friend class SpawnGrid;// Pour setter le maximum et min

	static IntervalList primary;	// La liste contentant tout les intervalles de spawns prioritaires
	static IntervalList scndary;	// La liste contenant les intervalles valides de spawns
	static Interval* prev;		// 1 Seul It�rateur, pointe vers un �l�ment pr�c�dant			
	static int maxVer;	// Donne le max sur les bordures verticaux
	static int maxHor;	// Donne le max sur les bordures horizontaux	
	static int bannedSpwn[4];	// Permet de v�rifier le nombre de spawn exclut sur une bordure
	static bool borderIsFull[4];// La bordure ne contient aucun spawn de disponible
	static bool allPrimeEmpty;	// Tout les listes primaires sont vides
	static bool isPriority;	// D�termine si on bannis un spawn qui est pr�sent dans la liste prioritaire

	// INFORMATION SUR LISTE
	static bool Is_Secondary_List_Full(int border);	// Liste secondaire est pleine?
	static bool Is_Secondary_List_Empty(int border);				// Liste Secondaire est vide?
	static bool Are_Primary_Lists_Empty();			// V�rification de �a

	// RECHERCHE DE VALEUR
	static Interval* Find_Interval(int border, int spwNum, IntervalList* &theList);			// Trouve un interval � l'aide d'une coord
	static Interval* Set_First_Interval(int border);		// Set le premier interval, soit de "0 � Max Number of Spawn on border"
	static Interval* Pick_Random_Interval(const IntervalList& list, int border);	// Prend un interval random parmis la liste figurant sur une bordure
	static int Pick_Rdm_Spwn_From_Interval(Interval* intval);	// G�n�re la coordonn�e de spawn!

	// MODIFICATION DES LISTES
	static void Modify_Min(Interval* intval, int newMin);	// Augmente le min de 1
	static void Modify_Max(Interval* intval, int newMax);	// R�duit le Max de 1
	static void Split_Interval_In_Two(IntervalList &list, int border, Interval* &intval, int newMin);	// Quand tu ajoute une nouvelle valeur � exclure dans la liste d'interval
	static bool Exclude_Primary_Interval(int border, int min, int max);	// Exclut un intervalle de la liste primaire dans la liste secondaire
	static void Remove_Spawn_From_List(IntervalList &list, Interval* intval, int border, int bannedCrd);	// Retire un spawn dans une liste 

	// AJOUT/DESTRUCTION D'ITEM
	static Interval* Create_New_Interval(IntervalList& list, int border, int min, int max);				// Cr�er un Nouvel intervalle!!
	static void Destroy_Empty_Interval(IntervalList &list, Interval* intval, int border);	// Delete un intervalle quand il est vide

	// INITIALISATION
	static void Set_Maximum_Ver(int max) { maxVer = max; }				// setup le maximum de spawn sur la bordure au d�but du niveau
	static void Set_Maximum_Hor(int max) { maxHor = max; }				// setup le maximum de spawn sur la bordure au d�but du niveau
	static void Set_Maximums(int hor, int ver)			// setup le maximum de spawn sur la bordure au d�but du niveau
	{
		Set_Maximum_Ver(ver);
		Set_Maximum_Hor(hor);
	}

	// RESET BUTTON
	static void Empty_Primary_List();	// Ces listes doivent �tre vid� � la fin des spawns
	static void Reset_Secondary_List();	// Cette liste est Reset � la fin du spawn

public:
	// INITIALIZATION
	static void Initialize_Valid_Spawn_List();

	// AJOUTE UN INTERVALLE PRIORITAIRE. Seul les scipts de Spawn font �a. 1 Max par bordure. Cuz I Said So!
	static bool Add_Primary_Interval(int border, int min, int max);	

	// TROUVE UN SPAWN
	static int Pick_Valid_Spawn(int border, bool random, int spwNum = -1);	// On trouve un intervalle qui ensuite trouve un spawn disponible
	
	// TROUVE UNE BORDER DISPONIBLE
	static bool Is_Border_Full(int border);			// La bordure n'a plus aucun intervalle de disponible
	static int Pick_Primary_Border();	// Prend une bordure contenant une liste primaire

	// PR�PARE LES LISTES POUR LE PROCHAIN CYCLE
	static void Reset_For_Next_Cycle(){
		Empty_Primary_List();
		Reset_Secondary_List();
	}

};

