

#include "../grid/AllGrids.h"
#include "../animation/UI_invalid_move.h"
#include "../animation/UI_move_player.h"
#include "../events/msg_dispatcher.h"
#include "../items/item_list.h"
#include "../choice/choice_time.h"
#include "player_move.h"
#include "../time/movement_timer.h"



void Move_Player(Player& player, Direction dir)
{
	static GrdCoord start, end;

		start = player.Get_Grd_Coord();	// position de départ
		end = Find_End_Position(start, dir);		// Position d'arrivée

		player.Upd_Sym_From_Direction(dir);				// Change le symbole du joueur selon la direction, même si le mouv échoue

		if (Validate_Move(end))						// Vérifie si position valide
		{
			player.Set_Position(end);				// Nouvelle position
			player.Get_Grd_Coord();
			UI_Move_Player(player, start, end);		// Efface l'ancienne position. Affiche la nouvelle
			ItemsOnGrid::Pickup_Item_Here(end);		// Si ya un item, grab it!

			if (ChoiceTime::Is_Choice_Time())	// pour faire des choix
			{
				ChoiceTime::Unselect_If_Player_Off();
				ChoiceTime::Select_If_Player_On();
			}
		}
		else
			UI_Invalide_Action(/*player*/);		// Fait flasher le joueur
}

GrdCoord Find_End_Position(GrdCoord& start, Direction dir)	// Position dans le grid, après le move
{
	GrdCoord end = start;	// Position final

	switch (dir)
	{
	case UP:	end.r--;
		break;
	case LEFT:	end.c--;
		break;
	case DOWN:	end.r++;
		break;
	case RIGHT:	end.c++;
		break;
	}

	return end;

}
bool Validate_Move(const GrdCoord &pos) {

	//	Vérification que la position est dans le grid 
	if (!gGrids.linkGrd.Is_Inbound(pos))
	{
		MsgQueue::Register(BUMPED_BORDER);	// Mouhahaha
		return false;
	}

	// Vérification que le Link est passable	(le joueur peut circuleruniquement sur des Links qui sont FREE ou DEAD)
	LinkState state = gGrids.linkGrd.link[pos.c][pos.r].Get_State();	// non static 

	if (state == LinkState::BOUND || state == LinkState::ROOT)
		return false;

	if(linkGrid->link[pos.c][pos.r].Get_Modifier() != REGULAR)	// Peut uniquement marcher sur un link free ou DEAD et régulier
		return false;

	return true;
}