#pragma once

#include "../UI/txtstyle.h"
#include "../grid/grid.h"

enum PlayerState { DEAD, ALIVE, INVINCIBLE };		// Statut H�ro 

const unsigned char AllPlyrSym[5] = { 193,180,194,195,197 };	// Haut, Left, Down, Droite,  Neutre


class Player {
private:

	// ATTRIBUTES
	int HP = 3;								// La vie du joueur. : Le nombre de bots qui peuvent sortir de la bot avant qu'il soit dead
	PlayerState state = PlayerState::ALIVE; //

	// UI
	Colors clr = Colors::LIGHT_GREEN;		// Sa couleur
	char sym;								// Le symbole repr�sentant le player

	// POSITION
	GrdCoord grdCrd;						// On utilise le syst�me de coordonn�es des grids pour changer la position du joueur

public:
	// GETS
	int Get_HP() { return HP; }					// La vie
	char Get_Sym() { return sym; }				// Le symbole pour l'affichage
	GrdCoord Get_Grd_Coord() { return grdCrd; }	// Sa position dans le grid
	PlayerState Get_State() { return state; }	// Le state du joueur

	// SETS 
	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			// Change la position du joueur sur le Grid
	void Set_State(PlayerState newState) { state = newState; }		// Permet de d�truire le joueur:  Le r�ssuciter : Ou le Rendre invincible
	void Set_Sym(char newSym) { sym = newSym; }						// Change le symbole du joueur
	void Set_Color(Colors newColor) { clr = newColor; }				// Change la couleur du joueur

	// UPDATES
	void Upd_State();													// Ceci change le state du joueur quand il pred ou gagne du HP
	void Upd_Color();													// Change la couleur du joueur quand il pred ou gagne de la vie
	void Player_Lose_HP(int hpLost = 1);								// En g�n�ral, le joueur perdra 1hp seulement
	void Player_Gains_HP(int hpGain = 1);								// En g�n�ral, le joueur gagnera 1hp seulement

	void Dis_Player_Sym();
// changer le symbole selon la direction du dernier move du player

};

extern Player P1;
extern Player P2;		// It's a YOU!
