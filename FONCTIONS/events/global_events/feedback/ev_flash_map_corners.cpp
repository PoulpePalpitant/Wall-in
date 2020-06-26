#include "ev_flash_map_corners.h"

#include "../../../UI/map.h"

void Ev_Flash_Map_Corners()
{
	map.UI_Draw_Map_Corners();
	map.UI_Erase_Map_Corners();
	//map.UI_Draw_Map_Corners();
}