
#include "player_move.h"

#include "../animation/UI_move_player.h"
#include "../grid/AllGrids.h"
#include "../animation/UI_invalid_move.h"
#include "../events/msg_dispatcher.h"
#include "../items/item_list.h"
#include "../choice/choice_time.h"
#include "../time/movement_timer.h"



void Move_Player(Player& player, Direction dir)
{
	static GrdCoord start, end;

		start = player.Get_Grd_Coord();			
		end = Find_End_Position(start, dir);	

		player.Upd_Sym_From_Direction(dir);			// Change le symbole du joueur selon la direction, même si le mouv échoue

		if (Validate_Move(end))						
		{
			player.Set_Position(end);				
			player.Get_Grd_Coord();
			UI_Move_Player(player, start, end);		
			ItemsOnGrid::Pickup_Item_Here(end);		

			if (ChoiceTime::Is_Choice_Time())	
			{
				ChoiceTime::Unselect_If_Player_Off();
				ChoiceTime::Select_If_Player_On();
			}
		}
		else
			UI_Invalide_Action();		
}

GrdCoord Find_End_Position(GrdCoord& start, Direction dir)	// Position dans le grid, après le move
{
	GrdCoord end = start;	

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

	if (!gGrids.linkGrd.Is_Inbound(pos))
	{
		MsgQueue::Register(BUMPED_BORDER);	// Mouhahaha
		return false;
	}


	LinkState state = gGrids.linkGrd.link[pos.c][pos.r].Get_State();	
	
	// Peut uniquement se DÉPLACER sur un link free ou DEAD et régulier
	if (state == LinkState::BOUND || state == LinkState::ROOT)
		return false;

	if(linkGrid->link[pos.c][pos.r].Get_Modifier() != REGULAR)
		return false;

	return true;
}