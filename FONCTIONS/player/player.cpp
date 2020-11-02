#include <iostream>

#include "../grid/AllGrids.h"
#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "player.h"
#include "../blast/blast_modifier_queue.h"
#include "../UI/console_output/render_list.h"
#include "../events/global_events/ev_update_heart.h"
#include "../events/msg_dispatcher.h"
#include "../blast/blast_ammo.h"

extern Player P1 = {};		// Un joueur! 
extern Player P2 = {};		// Des joueurs!



// En général, le joueur perdra 1hp seulement
void Player::Player_Lose_HP(int hpLost)
{
	if (hp > 0)
	{
		hp -= hpLost;

		if (hp > 0)
			Start_Ev_Dr_Heart(hp);		 //  coeur est réaffiché
		else
			Start_Ev_Dr_Heart(0);	// important de mettre 0 ici, car ça peut être plus bas

		Upd_State();
	}
}


// Gagne 1 point de vie!
void Player::Player_Gains_HP(int hpGain)
{
	hp += hpGain; 
	Upd_State();	// Change le state du joueur
	Start_Ev_Dr_Heart(hp);		 //  coeur est réaffiché
}

void Player::Reset_Hp_And_Heart(int HP)	// 3 d'hp par défaut
{
	hp = HP;
	Upd_State();	// Change le state du joueur
	Start_Ev_Dr_Heart(hp);		 //  coeur est réaffiché
}

// Change le STate du joueur quand son hp tombe à 0 ou devient plus grand que zéro
void Player::Upd_State()
{
	if (hp > 0)
		state = PlayerState::ALIVE;
	else
	{
		state = PlayerState::DEAD;	
		MsgQueue::Register(DEFEAT);	// dead
	}
}

void Player::Reset_State()	// health, crd, and state
{
	Set_Hp(3);
	state = ALIVE;
	Set_Position({ 6,6 });
}

// Change la couleur du joueur quand il pred ou gagne de la vie
void Player::Upd_Color()													
{
	static int tempMod;

	if (!BlastModifierQueue::queue.Get_Nth_Element(1, tempMod))	// Prend le premier élément.
		tempMod = 0;	// si vide, tempmod est égal à regular

	switch ((Modifier)tempMod)
	{
	case REGULAR: clr = LIGHT_GREEN;		  break;
	case BUFFER: clr = LIGHT_YELLOW;		  break;
	case BLOCKER: clr = LIGHT_RED;			  break;
	case CORRUPTER: clr = LIGHT_PURPLE;		  break;
	case COLOR_A: clr = LIGHT_YELLOW;		  break;
	case COLOR_B: clr = LIGHT_AQUA;			  break;
	case BLIND_COLOR: clr = LIGHT_AQUA;		  break;

	}

	Dr_Player(); // Display le joueur si on update sa couleur booda
}


// Affiche le joueur		
void Player::Dr_Player()
{
	static Coord crd;
	crd = Get_XY();	// Position XY
	
	ConsoleRender::Add_Char(crd, sym, clr); 	// display
}

void Player::Er_Player()									// fait juste effacer
{
	ConsoleRender::Add_Char(Get_XY(), TXT_CONST.SPACE); 	// display
}

void Player::Move_And_Draw_Player(GrdCoord crd)			// Teleporte virtuellement le joueur
{
	// On teleport le joueur à un endroit probablement ailleurs
	if (gGrids.linkGrd.link[crd.c][crd.r].Get_State() != LinkState::DEAD)
		gGrids.linkGrd.link[crd.c][crd.r].Dsp_Link();
	else
		P1.Er_Player();

	P1.Set_Position(crd);
	P1.Dr_Player();
}

// Change le symbole du joueur lors d'un mouvement
void Player::Upd_Sym_From_Direction(Direction dir)								
{
	sym = AllPlyrSym[dir];
}

void Player::Set_Timeout(int time)			// Freeze le joueur pour une durée de temps 
{	
	timeout.Set_Cd_Duration((float)time);				// Sert principalement pour lui montrer un queue visuel quand il ne peut pas se déplacer
	timeout.Start_CountDown();
}

void Player::Upd_Player_Timeout()
{
	if (timeout.Is_Running())
	{
		timeout.Tick_Timer();
		
		if (!timeout.Is_Running())	// Timer finit
			ConsoleRender::Add_Char(Get_XY(), sym, clr);		// Ré-affiche toujours le joueur après un timeout
	}
}

Coord Player::Get_XY()										// Retrouva la crd du player dans la console
{
	if (linkGrid->Is_Inbound(grdCrd))
		return linkGrid->link[grdCrd.c][grdCrd.r].Get_XY();
	else
		return { -1,-1 };	// Player n'est pas dans le grid
}

bool Player::Set_On_Grid()												// 
{
	return (isOnGrid = linkGrid->Is_Inbound(grdCrd));
}
