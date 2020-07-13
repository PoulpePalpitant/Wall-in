
#include "ev_resize_from_grids.h"
#include "../events.h"
#include "../../items/item_spawner.h"
#include "../../grid/AllGrids.h"
#include "../../blast/mod_queue_animator.h"


//static Event ev_ResizeFromGrids(Ev_Resize_From_Grids);

 // RESIZE TOUT PLEINS DE SHIT QUI DÉPENDENT DES GRIDS
void Ev_Resize_From_Grids()
{
	ItemSpawner::availableLinks.Resize(linkGrid->Get_Cols() , 0, linkGrid->Get_Rows()  );
	DrawModifierQueue::Set_Mod_Queue_Pos();

	// Other stuff to resize, that depends on the grids now
	// Resize Window to map?

}



