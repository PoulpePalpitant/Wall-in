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
public:
	int total;		// Le nombre d'items spawné
	int current;	// Le nombre d'item dans la box en ce moment
	int pickup;		// Le nombre d'item pickup
	int missed;		// Le nombre d'item pas pickup

	void Item_Spawned() { this->current++; this->total++; }
	void Item_Picked_Up() { this->current--; this->pickup++; }
	void Item_Disappeared() { this->current--; this->missed++; }
};


class Items {

private:
	static Countdown nextSpawn;	// À quand le prochain
	static ItemMeta AllMeta;

	// UI
	Colors clr = Colors::LIGHT_GREEN;		// Sa couleur
	char sym;								// Le symbole le représentant 

	// POSITION
	GrdCoord grdCrd;						// On utilise le système de coordonnées des grids pour changer la position du joueur

	// DURÉE
	Countdown despawn;						// si le countdown finis, l'item despawn

	ItemMeta meta;	// info sur les items

public:
	// GETS
	char Get_Sym() { return sym; }				// Le symbole pour l'affichage
	GrdCoord Get_Grd_Coord() { return grdCrd; }	// Sa position dans le grid

	// SETS
	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			// Change sa position sur le Grid
	void Set_Sym(char newSym) { sym = newSym; }						// Change le symbole 
	void Set_Color(Colors newColor) { clr = newColor; }				// Change la couleur 

	// UPDATES
	static void Spawn(GrdCoord);				// À spawné
	static void Pickup(GrdCoord);				// Joueur l'a pickup
	static void Got_Shot(GrdCoord);			// C'est fait tiré par un blast

	// UI
	void Despawn_Warning();	// Flash and disappear
};


