#pragma once

#include "../UI/axis.h"
#include "../UI/coord.h"



// L'�tat du Spawn, si il est disponibe pour spawn� un Bot, ou si il est bloqu�!
enum class SpawnState { BLOCKED, FREE };	// Un Spawn sera Bloqu� pour �viter de cr�er un BOT qui entrarait en contact avec un autre Bot d�j� �xistant.

class BotSpawner
{
public:
	void Set_XY(Coord Coord) { coord = Coord; }	// Initialise le x et y du Spawn (Ne doit pas �tre utilis� directement, se r�f�rer au Grid de Spawn : SpawnGrid)
	Coord Get_XY() { 
		this;
			return coord;}	// retrouve la crd xy pour l'affichage 
	void Set_Spw_Index(int index) { this->SpawnIndex = index; }
	int Get_Spw_Index() { return this->SpawnIndex; }
	SpawnState Is_Blocked() { return this->state; }		// L'�tat du Spawn, si il est disponible pour spawn� un Bot(FREE), ou si il est bloqu�(BLOCKED)!
	// pointeur vers une liste de bots!(Perpendiculaire)	Si le pointeur est NULL
	// pointeur vers une liste de bots!(Frontal)
private:
	int SpawnIndex;	// ? ? ? ? pour pouvoir retrouver sa colonne ?
	Coord coord;
	SpawnState state;
};

