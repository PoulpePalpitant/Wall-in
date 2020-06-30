#include <iostream>

#include "../grid/AllGrids.h"
#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "player.h"
#include "../UI/console_output/render_list.h"

extern Player P1 = {};		// Un joueur! 
extern Player P2 = {};		// Des joueurs!

// En général, le joueur perdra 1hp seulement
void Player::Player_Lose_HP(int hpLost ) 
{
	hp -= hpLost;
	Upd_State();
	Upd_Color();
	//update heart
}	

// Gagne 1 point de vie!
void Player::Player_Gains_HP(int hpGain)
{
	hp += hpGain; 
	Upd_State();	// Change le state du joueur
	Upd_Color();	// Change sa couleur
	//update heart

}

// Change le STate du joueur quand son hp tombe à 0 ou devient plus grand que zéro
void Player::Upd_State()
{
	if (hp > 0)
		state = PlayerState::ALIVE;
	else
		state = PlayerState::DEAD;
}

// Change la couleur du joueur quand il pred ou gagne de la vie
void Player::Upd_Color()													
{
	switch (hp)
	{
	case 4:clr = Colors::LIGHT_AQUA; break;		// LE MAX, TU COMMENCE PAS UNE GAME AVEC ÇA
	case 3:clr = Colors::LIGHT_GREEN; break;	// Standard: Commence chaque lvl avec ça
	case 2:clr = Colors::LIGHT_YELLOW; break;	// Tension Rises!
	case 1:clr = Colors::LIGHT_RED; break;		// Dernière chance
	}

	Dis_Player_Sym(); // Display le joueur si on update sa couleur booda
}

// Affiche le joueur		
void Player::Dis_Player_Sym()
{
	static Coord crd;
	crd = Get_XY();	// Position XY
	
	ConsoleRender::Add_Char(crd, sym, clr); 	// display
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


//
//
//void UPD_Hero_Heart()
//{
//	std::string Layer[4] = {};			// Chacune des lignes possibles représentant le coeur
//	Coord crd;					// Coordonnée de départ pour afficher le coeur
//	crd.y = map.Get_Box_Limit(DOWN) + 2;
//
//
//	// Si le hp change, je doit changer 
//
//	switch (P1.Get_HP())
//	{
//	case 4:
//		Layer[0] = "	 \     /";
//		Layer[1] = "    - (*Y*)	-";
//		Layer[2] = ". + / _`v'_ \ + .";
//		break;
//	case 3:
//		Layer[0] = "        ";
//		Layer[1] = "     ( Y*)  ";
//		Layer[2] = "      `v'   ";
//		crd.x = 39;
//		break;
//	case 2:
//		Layer[1] = "     ( Y    ";" ( Y/  ";" (X X)  ";
//		Layer[2] = "      `v    ";"  /v  ";	"  'X  ";
//		crd.x = 39;
//		break;
//	case 1:
//		Layer[0] = "   ";
//		Layer[1] = " ( X )";
//		Layer[2] = " _`v'  ";
//		Layer[3] = "'       ";
//		crd.x = 38;
//		break;
//	case 0:
//		break;
//	}
//
//	UI_AF_Hero_Heart(crd, Layer, hero.clr);		// Affiche le coeur!
//}
//// Affiche la vie du joueur sous la forme d'un coeur
//// -------------------------------------------------
//
//
//void UI_AF_Hero_Heart(Coord crd, string Layer[], Colors clr)
//{
//	CDTimer animation;
//	Coord crd;
//	int keyFrame, finalStage;	// Va définir chaque stage de l'animation qu'on est en train de faire
//	bool isActive;
//
//	if (isActive)
//	{
//		if (keyFrame == 0)
//		{
//			animation.Set_Cd_Duration(20);
//			animation.Start_CountDown();
//		}
//
//
//		if (animation.Get_Time_Left <= 0)
//		{
//
//			switch (keyFrame)
//			{
//			case 0:
//				animation.Set_Cd_Duration(20);
//				crd = { 39,map.Get_Box_Limit(DOWN) + 2 };
//
//				crd.y++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.y++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.x++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.x++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.x++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.x++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.y++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				crd.y++;	ConsoleRender::Add_Char_To_Render_List(crd, '(');
//			case 1:
//				animation.Set_Cd_Duration(20);
//				crd = { 39,map.Get_Box_Limit(DOWN) + 2 };
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//				ConsoleRender::Add_Char_To_Render_List(crd, '(');
//
//
//
//
//
//			case 5: isActive = false;
//			}
//		}
//
//		animation.Start_CountDown();
//
//		else
//			animation.Tick_Timer();
//
//}
//	// Animation et subanimation
//
//	// con.X / 2 Mettre des choses centré!!! >:(
//	for (size_t i = 0; i < 3; i++)
//	{
//		UI_Aff_String(crd.X, crd.Y + i, Layer[i], 0, clr);
//	}
//}