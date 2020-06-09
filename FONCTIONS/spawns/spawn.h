#pragma once

#include "../UI/axis.h"
#include "../UI/coord.h"



// L'état du Spawn, si il est disponibe pour spawné un Bot, ou si il est bloqué!
enum class SpawnState { BLOCKED, FREE };	// Un Spawn sera Bloqué pour éviter de créer un BOT qui entrarait en contact avec un autre Bot déjà éxistant.

class BotSpawner
{
public:
	void Set_XY(Coord Coord) { coord = Coord; }	// Initialise le x et y du Spawn (Ne doit pas être utilisé directement, se référer au Grid de Spawn : SpawnGrid)
	Coord Get_XY() { 
		this;
			return coord;}	// retrouve la crd xy pour l'affichage 
	void Set_Spw_Index(int index) { this->SpawnIndex = index; }
	int Get_Spw_Index() { return this->SpawnIndex; }
	SpawnState Is_Blocked() { return this->state; }		// L'état du Spawn, si il est disponible pour spawné un Bot(FREE), ou si il est bloqué(BLOCKED)!
	// pointeur vers une liste de bots!(Perpendiculaire)	Si le pointeur est NULL
	// pointeur vers une liste de bots!(Frontal)
private:
	int SpawnIndex;	// ? ? ? ? pour pouvoir retrouver sa colonne ?
	Coord coord;
	SpawnState state;
};

