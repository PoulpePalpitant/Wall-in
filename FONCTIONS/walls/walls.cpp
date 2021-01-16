

#include "../UI/console_output/render_list.h"
#include "../grid/grid.h"
#include "../structure_manager/structure_manager.h"	// Pour gérer relation entre Link et walls
#include "../events/msg_dispatcher.h"
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

// ON CHANGE L'APPARANCE DU MUR SELON SA FORCE ET LE MODIFIER DE SON PARENT!
void Wall::Set_Wall_UI()									
{
	switch (type)
	{
	case WallType::REGULAR:
		Set_Default_Wall_UI(); break;		// Mur blanc. Une ligne continue

	case WallType::NONE:	
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
		break;		
	}

	//Set_Drawer(false, true);	// Réaffiche le mur

}

void Wall::Set_Strength_From_Parent(WallType newStrgt)
{
	if (StructureManager::Is_Link_Corrupted(pParent))// Le parent corrompu change le Wall en weak pour l'instant
	{
		type = WallType::NONE;
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

// RESET L'APPARENCE DU WALL À SES VALEURS PAR DÉFAUTS
void Wall::Set_Default_Wall_UI()
{
	// Changement du Symbole!
	if (axis == HOR)
		sym = WallSym::SYM_HOR;		// Un mur de type différent devrait avoir une couleur et un sym diff
	else
		sym = WallSym::SYM_VER;

	// Changement de la couleur par défaut
	clr = Colors::BRIGHT_WHITE;
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
void Wall::Activate_Wall(WallType newStrgt, Link* child, Polarization plr) {

	state = WallState::EXISTS;		// It's alive!
	childPos = plr;					// La position de son child dans la console

	StructureManager::Bond_Wall_To_Child(this, child); // Relie le wall à deux Links
	Set_Strength_From_Parent(newStrgt);		// La nouvelle force du mur

	
	//if (this->type == WallType::ENERGIZED)
	//	if(this->pParent->Get_Modifier() != Modifier::FORCEFIELD)
	//		this->pParent->Change_Color(LIGHT_PURPLE);


	if (drawer.timer.Is_On())
		DrawWalls::Find_And_Draw_Wall(drawer);	// Finit l'affichage du mur				Cett fonction peut fail

	Set_Drawer(false, true);

	MsgQueue::Register(WALL_ACTIVATED);
}
void Wall::Deactivate_Wall()
{
	state = WallState::DEAD;		// REMARQUE: On reset pas toutes les valeurs, c'est pour sauver de l'énergie un peu. On a juste besoin de savoir qu'il est dead au final quand on fais des checkup
	pParent = pChild = NULL;
	sym = WallSym::DEAD;	//UI
	clr = WHITE;			//UI
	MsgQueue::Register(WALL_DEACTIVATED);	//we did
}

void Wall::Remove_Bot_On_Me()
{
	this->botOnMe = -1; 	// Le bot est pati :)

	//if (type == WallType::NONE)
	//	Set_Drawer();				// DISABLEED SANS SAVOIR CE QUE ÇA FAISAIT

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

// Dépend de la force du bot
void Wall::Take_Damage(int dmg)
{
	this->hp -= dmg;

	if (hp <= 0)
		ListsOfChainToModify::Add_Chain_To_Modify({}, this->pChild);	// Détruit la chaîne de mur bueno
	else
	{
		type = ((WallType)hp);	// change la force. et aussi l'apparence automatiquement.
		Set_Wall_UI();
		Set_Drawer(); //this->UI_Draw_Or_Erase_Wall();	// Il faut Redraw manuellement
	}
}


// Si un wall était déjà en train d'être dessiné? faudrait au moins finir de le draw?????????
void Wall::Set_Drawer(bool erase, bool instant)	// Si inAChain est activé, on gère pas la création des queues
{
	CoordIncrementor startPos;	// Position de départ
	int wallSize;	// Dimension du mur

	// Initialisation de l'incrémenteur
	startPos.Initialize_Axis(axis);
	startPos.polar = childPos;	// pourrait mettre un safety ici, genre if(childpos exist)
	startPos.coord = XY;

	wallSize = Get_Wall_Size(axis);

	if (childPos == NEG)								//  x  ->   <-  x		x = startpos
		*startPos.axis += wallSize - 1;					// O----O	O----O		-> = plr

	// Si Le Wall était déjà en train d'être afficher, on finis de faire ça
	DrawWalls::Finish_Wall(drawer);

	// Timer is set boyos
	if (erase)
		drawer.sym = TXT_CONST.SPACE;	// we erase
	else
		drawer.sym = (char)sym;	// we draw

	drawer.clr = clr;
	drawer.xy = startPos;

	if(instant)
		drawer.timer.Start_Timer(0, wallSize);
	else
		drawer.timer.Start_Timer(WALL_DRAW_SPEED, wallSize);

	DrawWalls::Add(&drawer); // adding that shit
}


void Wall::UI_Draw_Or_Erase_Wall(bool inAChain)	// Si inAChain est activé, on gère pas la création des queues
{
	//CoordIncrementor startPos;	// Position de départ
	//int wallSize;	// Dimension du mur

	//// Initialisation de l'incrémenteur
	//startPos.Initialize_Axis(axis);
	//startPos.polar = childPos;
	//startPos.coord = XY;

	//wallSize = Get_Wall_Size(axis);

	//if (childPos == NEG)								//  x  ->   <-  x		x = startpos
	//	*startPos.axis += wallSize - 1;					// O----O	O----O		-> = plr

	//if(!inAChain)
	//	ConsoleRender::Create_Animation_Queue(75);

	//for (int i = 0; i < wallSize; i++)
	//{
	//	ConsoleRender::Add_Char(startPos.coord, (char)sym, clr);	// SPEEDSPEEDSPEEDSPEEDSPEEDSPEEDSPEEDSPEED
	//	startPos.Increment_Coord();	// Prochaine case
	//}

	//if(!inAChain)
	//	ConsoleRender::Stop_Queue();			// TU DOIS ABSOLUMENT STOP LA QUEUE QUAND TU UTILISE ^CA
}
