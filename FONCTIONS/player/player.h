#pragma once

#include "../UI/txtstyle.h"
#include "../grid/grid.h"
#include "../time/countdown_clock.h"
#include "../teleporter/teleporter.h"

enum PlayerState { DEAD, ALIVE, INVINCIBLE };		

const unsigned char AllPlyrSym[5] = { 193,180,194,195,197 };	// Haut, Left, Down, Droite,  Neutre


class Player {
private:
	int hp = 1;								// Hp est arbitraire: dès qu'un bot réussit à sortir, la joueur "meurt" et doit recommencer le puzzle
	PlayerState state = PlayerState::ALIVE;
	bool canDoStuff = true;					
	Colors clr = Colors::LIGHT_GREEN;		
	char sym;								

	GrdCoord grdCrd = {0,0};						
	Teleporter teleporter;		// Permet de se téléporter
	CDTimer timeout;			// Freeze les actions du player

public:
	// GETS
	int Get_HP() { return hp; }					
	char Get_Sym() { return sym; }				
	Colors Get_Clr() { return clr; }			
	GrdCoord Get_Grd_Coord() { return this->grdCrd; }	
	PlayerState Get_State() { return state; }			
	bool Is_Timeout() { return timeout.Is_Running(); }	
	Coord Get_XY();										
	Teleporter& Get_Teleporter() { return teleporter; }
	bool Cant_Do_Stuff();
	

	// SETS 
	void Set_Position(GrdCoord newPos) { this->grdCrd = newPos; }	
	void Set_State(PlayerState newState) { state = newState; }		
	void Set_Sym(char newSym) { sym = newSym; }					
	void Set_Color(Colors newColor) { clr = newColor; }			
	void Set_Hp(int HP) { hp = HP; }							
	void Reset_Hp_And_Heart(int HP = 3);						
	void Set_Timeout(int time);									

	// UPDATES
	void Upd_Player_Timeout();
	void Upd_Sym_From_Direction(Direction dir);							
	void Upd_State();													
	void Upd_Color();													
	void Player_Lose_HP(int hpLost = 1);								
	void Player_Gains_HP(int hpGain = 1);								

	// SPÉCIALE
	void Move_And_Draw_Player(GrdCoord crd);			
	void Dr_Player();									
	void Er_Player();									
};

extern Player P1;

