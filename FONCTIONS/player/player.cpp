#include <iostream>

#include "../grid/AllGrids.h"
#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "../UI/console_output/dsp_char.h"
#include "player.h"

extern Player P1 = {};		// Un joueur! 
extern Player P2 = {};		// Des joueurs!

// En général, le joueur perdra 1hp seulement
void Player::Player_Lose_HP(int hpLost ) 
{
	HP -= hpLost;
	Upd_State();
	Upd_Color();
	//update heart
}	

// Gagne 1 point de vie!
void Player::Player_Gains_HP(int hpGain)
{
	HP += hpGain; 
	Upd_State();	// Change le state du joueur
	Upd_Color();	// Change sa couleur
	//update heart

}

// Change le STate du joueur quand son hp tombe à 0 ou devient plus grand que zéro
void Player::Upd_State()
{
	if (HP > 0)
		state = PlayerState::ALIVE;
	else
		state = PlayerState::DEAD;
}

// Change la couleur du joueur quand il pred ou gagne de la vie
void Player::Upd_Color()													
{
	switch (HP)
	{
	case 4:clr = Colors::LIGHT_AQUA; break;		// LE MAX, TU COMMENCE PAS UNE GAME AVEC ÇA
	case 3:clr = Colors::LIGHT_GREEN; break;	// Standard: Commence chaque lvl avec ça
	case 2:clr = Colors::LIGHT_YELLOW; break;	// Tension Rises!
	case 1:clr = Colors::LIGHT_RED; break;		// Dernière chance
	}
}

// Affiche le joueur		
void Player::Dis_Player_Sym()
{
	static Coord crd;
	crd = linkGrid->link[grdCrd.c][grdCrd.r].Get_XY();	// Position XY
	
	UI_Dsp_Char(crd,sym,clr);	// display
}

// Change le symbole du joueur lors d'un mouvement
void Player::Upd_Sym_From_Direction(Direction dir)								
{
	sym = AllPlyrSym[dir];

}