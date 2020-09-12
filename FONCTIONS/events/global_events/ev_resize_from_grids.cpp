
#include "ev_resize_from_grids.h"
#include "../events.h"
#include "../../items/item_spawner.h"
#include "../../grid/AllGrids.h"
#include "../../blast/mod_queue_animator.h"
#include "../../spawns/valid_spwn_intervals.h"
#include "../../spawns/bots_to_spawn.h"

//static Event ev_ResizeFromGrids(Ev_Resize_From_Grids);

 // RESIZE TOUT PLEINS DE SHIT QUI DÉPENDENT DES GRIDS
void Ev_Resize_From_Grids()
{
	ValidSpwnIntervals::Initialize_Valid_Spawn_List(); // Doit être fait à chaqu resize du grid
	ItemSpawner::availableLinks.Resize(linkGrid->Get_Cols() , 0, linkGrid->Get_Rows()  );
	DrawModifierQueue::Set_Mod_Queue_Pos();

	ValidSpwnIntervals::Reset_For_Next_Cycle();	// anti-crash action
	bots_to_spawn::Reset_To_Default();			// anti-crash action

	// Other stuff to resize, that depends on the grids now
	// Resize Window to map?

}



