

#include "walls.h"
#include "../grid/grid.h"



void Wall::Set_XY(int col, int row, Axis axis)
{
	if (axis == HOR)
	{
		this->XY.x = START_X + 1 + DELTA_X * col;	// Le COORD XY du wall sur le grid horizontal se trouvera tjrs une case plus loin en X(+1) que celle du Main Grid	
		this->XY.y = START_Y + DELTA_Y * row;		// Voir grid.h -> WallGrd pour la logique
	}  													  
	else
	{
		this->XY.x = START_X + DELTA_X * col;		// Le COORD XY du Grid de wall Vertical se trouvera tjrs une case plus loin en Y(+1) que celle du Main Grid
		this->XY.y = START_Y + 1 + DELTA_Y * row;
	}
}

// ON CHANGE L'APPARANCE DU MUR SELON SON TYPE!
void Wall::Set_Wall_UI(WallType newType)									
{
	// On change rien si le nouveau type est le même que le précédent
	if (type == newType)
		return;

	switch (newType)
	{
	case WallType::REGULAR:
		Set_Default_Wall_UI(); break;		// Mur blanc. Une ligne continue

	case WallType::GHOST:	
		color = Colors::GRAY;				// La couleur est grise
		//if (axis == HOR)
		//	sym = WallSym::SYM_HOR;		// Le symbole est aussi différent. C'Est plus un truc rayé qu'une ligne continue
		//else
		//	sym = WallSym::SYM_VER;
		break;
	case WallType::STRONG: 
		color = Colors::LIGHT_YELLOW;				
		break;

	case WallType::BIGSTRONGWOW:
		color = Colors::LIGHT_AQUA;
		break;
	}
}



// RESET L'APPARENCE DU WALL À SES VALEURS PAR DÉFAUTS
void Wall::Set_Default_Wall_UI()
{
	// Changement du Symbole!
	if (axis == HOR)
		sym = WallSym::SYM_HOR;		// Un mur de type différent devrait avoir une couleur et un sym diff
	else
		sym = WallSym::SYM_VER;

	// Changement de la couleur par défaut
	color = Colors::WHITE;
}


