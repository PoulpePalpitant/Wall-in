#pragma once

#include "items.h"
#include "item_list.h"
#include "../time/movement_timer.h"

struct TypeSpawner
{
	ItemType type;		
	SpeedTimer timer; 
	int rdmDelay;		// La variation de temps entre chaque spawn. mon syst�me marche avec la speed et non en seconde. Je peux pas r�duire la vitesse facilement pour cr�er 1 d�lay d'une seconde:	
	int spwSpeed;																																				// 1000 = 1 sec 2000 = .5 seconde
};																																								 // 100 = 10 sec
																																								 // 1000 + 10 != 11 secondes :/
struct ItemSpawnPool																																			 //
{
	TypeSpawner spawner[MAX_ITEM_TYPE] = {};
	int size; 
};

class ItemSpawner
{
private:
	friend void Ev_Resize_From_Grids();	
	friend void Initialize_Game();		
	static void Init_Pool_Types();	// Initialize la pool avec tout les types actuel
	static bool pause;	

public:
	static Intervals::ManageIntervalLists availableLinks;	
	static ItemSpawnPool pool;

	// TIMERS
	static void UPD_Item_Spawn_Timers();
	static int Add_Delay(TypeSpawner* spawner);
	static void Pause_Updates() { pause = true; }
	static void Resume_Updates() { pause = false; }
	static TypeSpawner* Get_Spawner(ItemType type);

	// POOL
	static bool Add_To_Pool(ItemType type, int timerduration, int rngDelay);				
	static bool Remove_From_Pool(ItemType type);
	static void Set_Spawner_Timer(TypeSpawner& spawner, int timerduration, int rngDelay);	
	static bool Set_Spawner_Timer(ItemType type, int timerduration, int rngDelay);			

	// SPAWNER
	static bool Spawn_This_Item(ItemType type, GrdCoord crd, bool cancel = false, bool noanimation = false , bool rdmCoord = false);	
	static void Refresh_Available_Spawn_List();
	static bool Find_Spawn_Location(GrdCoord &itemCrd);
	static bool Generate_Rdm_Coord(GrdCoord& itmCrd);	
	static bool Pick_Specific_Coord(GrdCoord& itmCrd);	

	// EXCLUT LES POSITIONS DU GRIDS SUIVANTES
	static void Player_Exclusion(GrdCoord P1Pos);	// Exclut les spawns trop proches du joueur
	static void Blast_Exclusion(GrdCoord P1Pos);	// Exclut les spawns perpendiculaire au joueur
	static void Items_Exclusion();					// Exclut les spawns occup�s par d'autres items

};


// THE RANDOM WAY

// G�n�re 1 donn�e au hasard
// V�rifie si chacune des conditions sont pr�sentes
// Sinon recommence

// Peut reprendre la m�me donn�e.
// Si les conditions augmentent, �a prend de plus en plus de temps
// Si les conditions diminuent, �a prend de moins en moins de temps
// Si aucune conditions sont valides, �a crash
// Extr�mement basic

// TAKE NO CHANCES

// �limine tout de suite les donn�es qui sont pas valides
// Choisis une au hasard dans celle qui restes
// M�me vitesse, peut importe le nombre de conditions. 
// Prend du temps valider chacunes des conditions
// Si utilis� en rafale, peut gagner bcp de temps

// Par Comparaison aux autres m�thodes: 
// tr�s rapide quand les conditions sont grandes
// tr�s lentes quand aucune conditions sont pr�sentes

// PAR �LIMINATION

// G�n�re 1 donn�e au hasard
// V�rifie si chacune des conditions sont pr�sentes
// Sinon, la donn�e invalide est ajout� � une liste
// Et recommence

// Ne Peut pas reprendre la m�me donn�e.
// Plus les conditions augmentent, plus �a va prendre du temps, mais sera plus rapide que LA RANDOM WAY
// Si les conditions diminuent, �a prend de moins en moins de temps
// Ne crash pas si aucunes conditions sont valides

// �LIMINATION ET REGROUPEMENT 

// �limine une certaine partie des donn�es qui ne sont pas valides
// G�n�re 1 donn�e au hasard en excluant ces donn�es
// V�rifie si le reste des conditions sont pr�sentes
// Sinon, ajoute l'�l�ment dans une listes
// Recommence

// Mix entre PAR �LIMINATION et TAKE NO CHANCES, cette fa�ont est un peux plus flexible
// Selon la quantit� d'�l�ment qui sont exclus, peut avoir une vitesse stable
// Peut �tre rapide quand ya rien
// Peut �tre un peu plus rapide que TAKE NO CHANCES quand on atteint 50% de conditions invalides?
// Tout d�pend de la capacit� � regrouper des exclusions


// I'm a go with that one