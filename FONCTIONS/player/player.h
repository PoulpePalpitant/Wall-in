#pragma once

#include "../UI/txtstyle.h"
#include "../grid/grid.h"

enum PlayerState { DEAD, ALIVE, INVINCIBLE };		// Statut Héro 

const unsigned char AllPlyrSym[5] = { 193,180,194,195,197 };	// Haut, Left, Down, Droite,  Neutre


class Player {
private:
	// ATTRIBUTES
	int hp = 3;								// La vie du joueur. : Le nombre de bots qui peuvent sortir de la bot avant qu'il soit dead
	PlayerState state = PlayerState::ALIVE; //

	// UI
	Colors clr = Colors::LIGHT_GREEN;		// Sa couleur
	char sym;								// Le symbole représentant le player

	// POSITION
	GrdCoord grdCrd = {0,0};						// On utilise le système de coordonnées des grids pour changer la position du joueur

public:
	// GETS
	int Get_HP() { return hp; }					// La vie
	char Get_Sym() { return sym; }				// Le symbole pour l'affichage
	Colors Get_Clr() { return clr; }			// Couleur
	GrdCoord Get_Grd_Coord() { return this->grdCrd; }	// Sa position dans le grid
	PlayerState Get_State() { return state; }	// Le state du joueur

	// SETS 
	void Set_Position(GrdCoord newPos) { this->grdCrd = newPos; }			// Change la position du joueur sur le Grid
	void Set_State(PlayerState newState) { state = newState; }		// Permet de détruire le joueur:  Le réssuciter : Ou le Rendre invincible
	void Set_Sym(char newSym) { sym = newSym; }						// Change le symbole du joueur
	void Set_Color(Colors newColor) { clr = newColor; }				// Change la couleur du joueur
	void Set_Hp(int HP) { hp = HP; }								// Chane l'hp pour une valeur fixe

	// UPDATES
	void Upd_Sym_From_Direction(Direction dir);							// Change le symbole du joueur lors d'un mouvement ou d'un tir dans une direction
	void Upd_State();													// Ceci change le state du joueur quand il pred ou gagne du HP
	void Upd_Color();													// Change la couleur du joueur quand il pred ou gagne de la vie
	void Player_Lose_HP(int hpLost = 1);								// En général, le joueur perdra 1hp seulement
	void Player_Gains_HP(int hpGain = 1);								// En général, le joueur gagnera 1hp seulement

	void Dis_Player_Sym();												// fait juste afficher le joueur. Utilisé plutôt UI_Move_Player, qui efface le symbole derrière lui aussi
// changer le symbole selon la direction du dernier move du player

};

extern Player P1;
extern Player P2;		// It's a YOU!

