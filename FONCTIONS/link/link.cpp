
#include "../grid/grid.h"
#include "../UI/console_output/render_list.h"
#include "../structure_manager/structure_manager.h"	// Pour g�rer relation entre Link et walls

#include "link.h"


// La position x et y du Link dans la console, par rapport � son propre LinkGrid
void Link::Set_LinkXY(int col, int row)
{
	this->coord.x = START_X + DELTA_X * col;			
	this->coord.y = START_Y + DELTA_Y * row;
}

void Link::Set_State(Wall* child )	// Assigne le state 
{
	if (!this->pParent)	// Pas de Parent? T'es le premier d'une lign�!
		state = LinkState::ROOT;
	else
		if (child == NULL)
			state = LinkState::FREE;	// Pas de child? T'es FREE!
		else
			state = LinkState::BOUND;		// Ah, tu es li� finalement
}

// Change la couleur et le symbole selon le Type et le State du Link
void Link::Set_UI()						
{
	switch (this->type)
	{
	case LinkType::REGULAR: 
	case LinkType::ETERNAL:
	case LinkType::CORRUPTED:	// BREAK!
	case LinkType::CHASER:
	case LinkType::BLOCKER:
		if (state == LinkState::ROOT)
			sym = (char)LinkSym::ROOT;
		if (state == LinkState::BOUND)
			sym = (char)LinkSym::PARENT;
		if (state == LinkState::FREE)
			sym = (char)LinkSym::CHILD;	// BREAK!
	}
	clr = WHITE;	//default bitch
}

// Active un Link et le relie � un Child
bool Link::Activate_Link(LinkType& type, Wall* child)
{
	//static bool drawLink; drawLink = false;

	this->type = type;	// Son nouveau type	(certaines conversions seront impossible dans le futur)				// Set_Type(type)

	if (this->state == LinkState::DEAD || this->state == LinkState::FREE)		// error brah, le link �tait pas libre ou DEAD
	{
		Set_State(child);				// Set le state selon le fait qu'il a un child ou non, ou si ya pas de parent
		//drawLink = true;				// Affiche toujours le Link quand son state change
	}

	StructureManager::Bond_Link_To_Child(this, child);	// assigne les pointeurs parent/enfant
	Set_UI();						// affichage

	//if (drawLink)
		//Dsp_Link();		//	Draw Le Link n�cessite de v�rifier si le joueur si trouve avant! Alors que pour chaque blast, je veux pas faire �a.

	return true;
}

void Link::Deactivate_Link()					// � D�TERMINER LORS de la destruction
{
	int children = this->numChild;
	this->pParent = NULL;
										// reset pointers
	for (int i = 0; i < numChild; i++)	// reset pointers		// that is some odd for loop
	{
		this->pWalls[i] = NULL;	// reset pointers
		children--;
	}

	numChild = children;	// Safety
	state = LinkState::DEAD;

	//if(type != LinkType::REGULAR)
		/*do stuff*/

}

bool Link::Unbound_Wall_Child(Wall* child)
{
	if (this->state == LinkState::DEAD)		// �a la foir�, ce link n'�tait m�me pas en vie
		return false;

	for (size_t i = 0; i < this->numChild; i++)
	{
		if (this->pWalls[i] == child)				// Le wall qu'on veut retirer
		{		
			for (size_t j = i; j < numChild; j++)	// d�calage de tout les childs de la liste							
			{
				if (j + 1 < numChild)
					this->pWalls[j] = this->pWalls[j + 1];
				else
					this->pWalls[j] = NULL;	// Le dernier sera NULL car on viens de le destroy hha. pOW. Pachinka Haha... SzwIINNg.. PAF! Hehe. SPatatra!!! Ohoho' FLshaq, HaHa.
			}
			
			numChild--;	// -1 wall
			break;
		}
	}

	if (!numChild)
	{ 
		if (state == LinkState::BOUND)
		{
			state = LinkState::FREE;
			this->Set_UI();	// change le sym
			this->Dsp_Link();	// Affiche le sym
		}
		else
			if (state == LinkState::ROOT)		// Si le root n'a plus de Child, il mourre
			{
				this->Deactivate_Link();				
				Clr_Link();		// Efface le Link		// Pourrait �tre mis � pars
			}
		return true;		// success
	}

	return false;	// �a se peut que le wall ne soit m�me pas un de ses childs
}



//UI
void Link::Dsp_Link()						// Affiche le Link
{
	ConsoleRender::Add_Char_To_Render_List(this->coord, this->sym, this->clr);
}

void Link::Clr_Link(float speed)						// Clear le Link
{
	ConsoleRender::Add_Char_To_Render_List(this->coord, TXT_CONST.SPACE, WHITE, speed);
}