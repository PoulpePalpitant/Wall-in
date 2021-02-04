

#include "../UI/console_output/render_list.h"
#include "../grid/grid.h"
#include "../structure_manager/structure_manager.h"	// Pour gérer relation entre Link et walls
#include "../events/msg_dispatcher.h"
#include "walls.h"

extern const int WALL_SIZE_X =  DELTA_X - 1;	
extern const int WALL_SIZE_Y = DELTA_Y - 1;		


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

// L'apparance du mur selon son type
void Wall::Set_Wall_UI()									
{
	switch (type)
	{
	case WallType::REGULAR:
		Set_Default_Wall_UI(); break;		// Mur blanc. Une ligne continue

	case WallType::WEAK:	
		clr = Colors::GRAY;				
		if (axis == HOR)
			sym = WallSym::SYM_HOR3;	// Le symbole est aussi différent. C'Est plus un truc rayé qu'une ligne continue
		else
			sym = WallSym::SYM_VER3;
		break;

	case WallType::STRONG: 
		if (axis == HOR)
			sym = WallSym::SYM_HOR2;	// DEUX GROSSES LIGNES
		else
			sym = WallSym::SYM_VER2;
		clr = Colors::BRIGHT_WHITE;				
		break;

	case WallType::INVINCIBRU:
		clr = Colors::LIGHT_AQUA;
		break;

	case WallType::ENERGIZED:
		Set_Default_Wall_UI();
		clr = Colors::LIGHT_PURPLE;
		clr = Colors::LIGHT_AQUA;
		break;		
	}
}

void Wall::Set_Strength_From_Parent(WallType newStrgt)
{
	if (StructureManager::Is_Link_Corrupted(pParent)) 
	{
		type = WallType::WEAK;
		hp = (int)type;
	}
	else
		if (pParent->Get_Modifier() == BUFFER)
		{
			type = WallType::STRONG;
			hp = int(type);
		}
		else
		{
			type = newStrgt;

			if (newStrgt == WallType::ENERGIZED)
				hp = 1;
			else
				hp = int(type);
		}

	Set_Wall_UI();
}

void Wall::Set_Default_Wall_UI()
{
	if (axis == HOR)
		sym = WallSym::SYM_HOR;		
	else
		sym = WallSym::SYM_VER;

	clr = Colors::BRIGHT_WHITE;
}

int Wall::Get_Wall_Size(Axis axis)						
{
	if (axis == HOR)
		return WALL_SIZE_X;
	else
		return WALL_SIZE_Y;
}

void Wall::Activate_Wall(WallType newStrgt, Link* child, Polarization plr) {

	state = WallState::EXISTS;		// It's alive!
	childPos = plr;					// Pour retrouver son child dans la console

	StructureManager::Bond_Wall_To_Child(this, child); // Relie le wall à deux Links
	Set_Strength_From_Parent(newStrgt);		

	if (drawer.timer.Is_On())
		DrawWalls::Find_And_Draw_Wall(drawer);	// Finit l'affichage du mur *cette fonction peut fail

	Set_Drawer(false, true);

	MsgQueue::Register(WALL_ACTIVATED);
}
void Wall::Deactivate_Wall()
{
	state = WallState::DEAD;		// REMARQUE: On reset pas toutes les valeurs, c'est pour sauver de l'énergie un peu . On a juste besoin de savoir qu'il est dead au final quand on fais des checkup
	pParent = pChild = NULL;
	sym = WallSym::DEAD;	
	clr = WHITE;			
	MsgQueue::Register(WALL_DEACTIVATED);	
}

void Wall::Remove_Bot_On_Me()
{
	this->botOnMe = -1; 			// Le bot est pati :)

	if (state != WallState::DEAD)
		Set_Drawer();				// Réaffiche d'un coup que ya des glitchs visuels. encore
}

bool Wall::Is_Activated()
{
	if (this->state == WallState::DEAD)
		return false;
	else
		return true;
}

void Wall::Take_Damage(int dmg)
{
	if(this->type != WallType::INVINCIBRU)
		this->hp -= dmg;	

	if (hp <= 0)
		ListsOfChainToModify::Add_Chain_To_Modify({}, this->pChild);	// Détruit la chaîne de mur bueno
	else
	{
		type = ((WallType)hp);	// change la force. et aussi l'apparence automatiquement.
		Set_Wall_UI();
		Set_Drawer(); 
	}
}


void Wall::Set_Drawer(bool erase, bool instant)	
{
	CoordIncrementor startPos;	
	int wallSize;	

	// Initialisation de l'incrémenteur
	startPos.Initialize_Axis(axis);
	startPos.polar = childPos;	
	startPos.coord = XY;

	wallSize = Get_Wall_Size(axis);

	if (childPos == NEG)								//  x  ->   <-  x		x = startpos
		*startPos.axis += wallSize - 1;					// O----O	O----O		-> = plr

	// Si Le Wall était déjà en train d'être affiché, on finis de faire ça
	DrawWalls::Finish_Wall(drawer);

	if (erase)
		drawer.sym = TXT_CONST.SPACE;	
	else
		drawer.sym = (char)sym;	

	drawer.clr = clr;
	drawer.xy = startPos;

	if(instant)
		drawer.timer.Start_Timer(0, wallSize);
	else
		drawer.timer.Start_Timer(WALL_DRAW_SPEED, wallSize);

	DrawWalls::Add(&drawer); // adding that shit
}

