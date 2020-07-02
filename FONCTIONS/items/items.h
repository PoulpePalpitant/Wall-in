#pragma once

#include "../grid/grid.h"
#include "../UI/txtstyle.h"
#include "../time/countdown_clock.h"

/*
	IDEAS:
	Chaque Objet items aurait un impact unique sur le jeu. Je devrais créer donc un classe différente pour chacuns si jamais j'en fais
	Un Item pourrait apparaître randomly sur le grid en utilisant un random position generator et un random item generator
	Une fois apparu, un item pourrait avoir une durée de vie limité. Le joueur devra donc se dépêcher pour le ramasser				requesite: item timer
	Pour ramasser l'item, le joueur pourrait se déplacer par dessus, ou simplement tirer dessus
	Une fois ramassé l'item pourrait avoir un Effet Limité, ou permanent? (permanent serait intéressant) L'effet pourrait même resté si le joueur quitte le jeu		Why?: Les actions ont des conséquences? Pas tellement un them du jeu, sauf si j'instaure une narrative avec des choix

	IDÉES D'ITEMS:
	- Health
	- Shooting speed
	- Pause

	Idées Out There:
	Si je fais un jeu punitifs, les items pourrait être des debuffs?  : Difficile à faire comprendre au joueur MM kinda bad
*/

class ItemMeta
{
private:
	static ItemMeta AllMeta;

public:
	int total;		// Le nombre d'items spawné
	int current;	// Le nombre d'item dans la box en ce moment
	int pickup;		// Le nombre d'item pickup
	int missed;		// Le nombre d'item pas pickup

	void Item_Spawned() {
		this->current++; this->total++; 
		AllMeta.current++; AllMeta.total++;
	}
	void Item_Picked_Up() {
		this->current--;AllMeta.current--;
		this->pickup++;
		AllMeta.pickup++;
	}
	void Item_Disappeared() { 
	this->current--;
	AllMeta.current--; 
	this->missed++; 
	AllMeta.missed++;
	}
};


class Items {

private:
	Countdown nextSpawn;	// À quand le prochain dans ce groupe

	// UI
	Colors clr = Colors::LIGHT_GREEN;		// Sa couleur
	char sym;								// Le symbole le représentant 

	// POSITION
	GrdCoord grdCrd;						// On utilise le système de coordonnées des grids pour changer faire apparâitre les items

	// DURÉE
	Countdown despawn;						// si le countdown finis, l'item despawn
	int max;								// quantité max d'item de ce type en vie

	ItemMeta meta;	// info sur le groupe d'items

	// SETS
	void Set_Sym(char newSym) { sym = newSym; }						// Change le symbole 
	void Set_Color(Colors newColor) { clr = newColor; }				// Change la couleur 
	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			// Change sa position sur le Grid
	
	// UI
	void Despawn_Warning();	// Flash and disappear
	void Spawn_Animation();
	

	bool Find_Spawn_Location();
public:
	// GETS
	char Get_Sym() { return sym; }				// Le symbole pour l'affichage
	GrdCoord Get_Grd_Coord() { return grdCrd; }	// Sa position dans le grid

	// UPDATES
	void Spawn(GrdCoord);				// À spawné
	void Pickup(GrdCoord);				// Joueur l'a pickup
	void Got_Shot(GrdCoord);			// C'est fait tiré par un blast
	static void Update_Items();			// Update les items du jeu
	static bool Is_Item_Here(GrdCoord crd);		// Hitbox de l'item


};


