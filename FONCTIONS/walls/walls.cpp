

#include "../UI/console_output/dsp_char.h"
#include "../grid/grid.h"
#include "../structure_manager/structure_manager.h"	// Pour gérer relation entre Link et walls

#include "walls.h"

extern const int WALL_SIZE_X =  DELTA_X - 1;	// Le nombre de case qui composent chaque wall horizontale
extern const int WALL_SIZE_Y = DELTA_Y - 1;		// Le nombre de case qui composent chaque wall verticale


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
void Wall::Set_Wall_UI(WallStrength newStrgt)									
{

	// On change rien si le nouveau type est le même que le précédent
	//if (strgt == newType)		// Doit être updaté
		//return;

	switch (newStrgt)
	{
	case WallStrength::REGULAR:
		Set_Default_Wall_UI(); break;		// Mur blanc. Une ligne continue

	case WallStrength::WEAK:	
		color = Colors::GRAY;				// La couleur est grise
		//if (axis == HOR)
		//	sym = WallSym::SYM_HOR;		// Le symbole est aussi différent. C'Est plus un truc rayé qu'une ligne continue
		//else
		//	sym = WallSym::SYM_VER;
		break;
	case WallStrength::STRONG: 
		color = Colors::LIGHT_YELLOW;				
		break;

	case WallStrength::BIGSTRONGWOW:
		color = Colors::LIGHT_AQUA;
		break;
	}
}

void Wall::Set_Strength(WallStrength newStrgt)
{
	if(StructureManager::Is_Link_Corrupted(this, pParent))// Le parent corrompu change le Wall en weak pour l'instant
		strgt = WallStrength::WEAK;
	else
		strgt = newStrgt;
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

// Dimension de chacun des walls
int Wall::Get_Wall_Size(Axis axis)						// La longueur du wall
{
	if (axis == HOR)
		return WALL_SIZE_X;
	else
		return WALL_SIZE_Y;
}

// Créer un mur (techniquement, le mur était déjà là, mais ici on change son state et son type pour signifier qu'un bot peut à nouveau rentré dedans)
void Wall::Activate_Wall(WallStrength newStrgt, Link* child) {

	state = WallState::EXISTS;		// It's alive!
	StructureManager::Bond_Wall_To_Child(this, child); // Relie le wall à deux Links
	Set_Strength(newStrgt);			// La nouvelle force du mur
	Set_Wall_UI(newStrgt);			// Update l'UI si le nouv type est différent que le précédent.
}

// Affiche un Mur selon une direction
void Wall::UI_Draw_Wall(Polarization plr)
{
	CoordIncrementor startPos;	// Position de départ
	int wallSize;	// Dimension du mur

	// Initialisation de l'incrémenteur
	startPos.Initialize_Axis(axis);
	startPos.polar = plr;
	startPos.coord = XY;

	wallSize = Get_Wall_Size(axis);

	if (plr == NEG)								//  x  ->   <-  x		x = startpos
		*startPos.axis += wallSize - 1;			// O----O	O----O		-> = plr

	for (int i = 0; i < wallSize; i++)
	{
		UI_Dsp_Char(startPos.coord, (char)sym, color);
		Sleep(15);	// SPEEDSPEEDSPEEDSPEEDSPEEDSPEEDSPEEDSPEED

		startPos.Increment_Coord();	// Prochaine case
	}


}
