
#include "../grid/AllGrids.h"
#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "player.h"
#include "../blast/blast_modifier_queue.h"
#include "../UI/console_output/render_list.h"
#include "../events/global_events/ev_update_heart.h"
#include "../events/msg_dispatcher.h"
#include "../blast/blast_ammo.h"
#include "../inputs/action_input.h"

extern Player P1 = {};		

bool Player::Cant_Do_Stuff() {
	return gBlockInputs;
}

void Player::Player_Lose_HP(int hpLost)	
{
	if (hp > 0)
	{
		hp -= hpLost;
		Upd_State();
	}
}


void Player::Player_Gains_HP(int hpGain)
{
	hp += hpGain; 
	Upd_State();	
	Start_Ev_Dr_Heart(hp);		 
}

void Player::Reset_Hp_And_Heart(int HP)	
{
	hp = HP;
	Upd_State();	
	Start_Ev_Dr_Heart(hp);		 
}

void Player::Upd_State()
{
	if (hp > 0)
		state = PlayerState::ALIVE;
	else
	{
		state = PlayerState::DEAD;	
		MsgQueue::Register(DEFEAT);	
	}
}

// Change la couleur du joueur quand son prochain tir est d'un certains type
void Player::Upd_Color()													
{
	static int tempMod;

	if (!BlastModifierQueue::queue.Get_Nth_Element(1, tempMod))
		tempMod = 0;	

	switch ((Modifier)tempMod)
	{
	case REGULAR: clr = LIGHT_GREEN;		  break;
	case BUFFER: clr = LIGHT_YELLOW;		  break;
	case BLOCKER: clr = LIGHT_RED;			  break;
	case CORRUPTER: clr = LIGHT_PURPLE;		  break;
	case ENERGIZER: clr = LIGHT_PURPLE;		  break;
	case COLOR_B: clr = LIGHT_AQUA;			  break;
	case BLIND_COLOR: clr = LIGHT_AQUA;		  break;

	}

	Dr_Player(); 
}


// Affiche le joueur		
void Player::Dr_Player()
{
	static Coord crd;
	crd = Get_XY();
	
	ConsoleRender::Add_Char(crd, sym, clr); 	
}

void Player::Er_Player()						
{
	ConsoleRender::Add_Char(Get_XY(), TXT_CONST.SPACE); 	
}

void Player::Move_And_Draw_Player(GrdCoord crd)			// Teleporte virtuellement le joueur
{
	if (gGrids.linkGrd.link[crd.c][crd.r].Get_State() != LinkState::DEAD)
		gGrids.linkGrd.link[crd.c][crd.r].Dsp_Link();
	else
		P1.Er_Player();

	P1.Set_Position(crd);
	P1.Dr_Player();
}

void Player::Upd_Sym_From_Direction(Direction dir)								
{
	sym = AllPlyrSym[dir];
}

void Player::Set_Timeout(int time)			// Freeze le joueur pour une durée de temps 
{	
	timeout.Set_Cd_Duration((float)time);	// Sert principalement pour lui montrer un queue visuel quand il ne peut pas se déplacer
	timeout.Start_CountDown();
}

void Player::Upd_Player_Timeout()
{
	if (timeout.Is_Running())
	{
		timeout.Tick_Timer();
		
		if (!timeout.Is_Running())	
			ConsoleRender::Add_Char(Get_XY(), sym, clr);		// Ré-affiche toujours le joueur après un timeout
	}
}

Coord Player::Get_XY()									
{
	if (linkGrid->Is_Inbound(grdCrd))
		return linkGrid->link[grdCrd.c][grdCrd.r].Get_XY();
	else
		return { -1,-1 };	
}

