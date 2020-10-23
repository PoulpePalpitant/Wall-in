#include "console_output/render_list.h"
#include "map.h"


extern const Distance GAP_BTW_GRID = 2;	// Les Spawns se retrouvent 1 case plus loin que le grid de Links

extern bool gBorderShown = false;		// Les bordures de la map sont visibles

extern Map map = {};	// Définition de la class map iciitttttttttteeeeee


void Map::Resize(LinkGrid& linkGrid)	// Resize les dimensions selon la nouvelle dimension du Grid principal(LinkGrid)
{
	//UI_Erase_Map_Corners();

	limit[LEFT] = START_X;	// Limite de l'air de déplacement du joueur à gauche
	limit[RIGHT] = START_X + DELTA_X * (linkGrid.Get_Cols() - 1);	// Limite de l'air de déplacement du joueur à droite -1 car c'Est le nombre de colonne max, à partir de 0
	length = limit[RIGHT] - limit[LEFT];	// Largeur

	limit[UP] = START_Y;	// Limite de l'air de déplacement du joueur en haut
	limit[DOWN] = START_Y + DELTA_Y * (linkGrid.Get_Rows() - 1);	// Limite de l'air de déplacement du joueur en bas
	height = limit[DOWN] - limit[UP];	// Hauteur
	
	//UI_Draw_Map_Corners();	// Test pour visibilité
}

void Map::UI_Draw_Map_Corners()
{
	ConsoleRender::Add_Char({ limit[LEFT] -1, limit[UP] - 1}, (unsigned char)218,BRIGHT_WHITE	);	// Start une queue ici.
	ConsoleRender::Add_Char({ limit[RIGHT] + 1, limit[UP] - 1 }, (unsigned char)191, BRIGHT_WHITE);								// -1 c'est pour créer une tit distance voyé!
	ConsoleRender::Add_Char({ limit[LEFT] -1,limit[DOWN] + 1}, (unsigned char)192, BRIGHT_WHITE);
	ConsoleRender::Add_Char({ limit[RIGHT] + 1, limit[DOWN] + 1 }, (unsigned char)217, BRIGHT_WHITE);
}

void Map::UI_Erase_Map_Corners()
{
	//ConsoleRender::Create_Animation_Queue(1500, false);	// false pour animation non-linéaire
	//ConsoleRender::Add_Char({ limit[LEFT] - 1, limit[UP] - 1 }, TXT_CONST.SPACE);
	//ConsoleRender::Add_Char({ limit[RIGHT] + 1, limit[UP] - 1 }, TXT_CONST.SPACE);
	//ConsoleRender::Add_Char({ limit[LEFT] - 1,limit[DOWN] + 1 }, TXT_CONST.SPACE);
	//ConsoleRender::Add_Char({ limit[RIGHT]+ 1, limit[DOWN] + 1 }, TXT_CONST.SPACE);
	//ConsoleRender::Stop_Queue();	// Stop la queue ici
}

