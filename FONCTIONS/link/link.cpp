
#include "../grid/grid.h"
#include "../UI/console_output/render_list.h"
#include "../structure_manager/structure_manager.h"	// Pour gérer relation entre Link et walls
#include "../events/msg_dispatcher.h"
#include "../player/player.h"
#include "link.h"


LinkMeta Link::meta = {};	// metton

// La position x et y du Link dans la console, par rapport à son propre LinkGrid
void Link::Set_LinkXY(int col, int row)
{
	this->coord.x = START_X + DELTA_X * col;			
	this->coord.y = START_Y + DELTA_Y * row;
}

void Link::Set_State(Wall* child )	// Assigne le state 
{
	if (!this->pParent)	// Pas de Parent? T'es le premier d'une ligné!
		state = LinkState::ROOT;
	else
		if (child == NULL)
			state = LinkState::FREE;	// Pas de child? T'es FREE!
		else
			state = LinkState::BOUND;		// Ah, tu es lié finalement
}

// Change la couleur et le symbole selon le Type et le State du Link
void Link::Set_UI()						
{
	switch (this->modifier)
	{
	case Modifier::REGULAR:
		clr = WHITE;	//default bitch

		if (state == LinkState::BOUND)
			sym = (char)LinkSym::PARENT;
		if (state == LinkState::FREE)
		{
			sym = (char)LinkSym::CHILD;	// BREAK!
			clr = GRAY;
		}
		break;

	case BUFFER:
		sym = 254;		
		clr = LIGHT_YELLOW;
		break;

	case Modifier::BLOCKER:
		sym = 158;
		/*if (state == LinkState::ROOT)
			clr = BG_WH_LIGHT_RED;
		else*/
			clr = LIGHT_RED;
		break;

	case Modifier::CORRUPTER:
		sym = 207;
	/*	if (state == LinkState::ROOT)
			clr = BG_WH_LIGHT_PURPLE;
		else*/
			clr = LIGHT_PURPLE;
		break;

	case Modifier::FORCEFIELD:
		sym = 176;
		clr = Colors::TEST;
		break;
	}

	if (state == LinkState::ROOT && modifier != Modifier::FORCEFIELD)
		sym = (char)LinkSym::ROOT;
}

bool Link::Set_First_Modifier(Modifier mod)		// Ne convertit pas le modifier si celui déjà existant est REGULAR
{
	if (Get_State() != LinkState::FREE && modifier == REGULAR)	// shame.		dont' edit, it makes sense
	{
		modifier = mod;
		return true;
	}
	else
		return false;
	
	
}
void Link::Convert_Modifier(Modifier mod)		// Convertit le modifier d'un link. Si le link était free, on affiche son symbole de modifier, ce faisant, il devient impassable pour le joueur
{
	if (mod != Modifier::REGULAR)	// I guess qu'on convertit pas en regular: Je fais ça uniquement pour ne pas convertir un forcefield en regular............
	{
		modifier = mod;
		Set_UI();	// affichage

		if (!Are_Equal(P1.Get_XY(), coord))
			Dsp_Link();	// Réaffiche le sym 
	}
}

void Link::Corruption_Inheritance(Modifier& mod)		//  le modifier
{
	if(pParent != NULL)
		if (pParent->Get_Parent_Modifier() == CORRUPTER)
			mod = CORRUPTER;
}

// Active un Link et le relie à un Child
bool Link::Activate_Link(Modifier& mod, Wall* child)
{
	// INTÉRACTIONS
	if(modifier != Modifier::FORCEFIELD)
		if (modifier == REGULAR)
			Corruption_Inheritance(mod);

	if (this->state == LinkState::DEAD || this->state == LinkState::FREE || modifier == Modifier::FORCEFIELD)		// error brah, le link était pas libre ou DEAD
	{
		Set_State(child);				// Set le state selon le fait qu'il a un child ou non, ou si ya pas de parent
	}

	StructureManager::Bond_Link_To_Child(this, child);	// assigne les pointeurs parent/enfant
	Set_First_Modifier(mod);		// Si le link est free, il ne peut avoir autre modifier que le REGULAR. Il pourra être convertit par un blast plus tard . Why?, parce que je veut qu'un buffer puisse
								// transformer le child d'un corrupter? Et que les child des corrupter soit toujours Regular pour que ce soit claire que le joueur peut uniquement bouger sur des tits points
	Set_UI();											// affichage

	meta.Add();
	MsgQueue::Register(LINK_ACTIVATED);
	return true;
}

// Active un Link et le relie à un Child
bool Link::Activate_Lonely_Link(Modifier mod)
{
	bool dead = false;
	if (state == LinkState::DEAD)
		dead = true;
	
	modifier = mod;
	
	if (mod == Modifier::FORCEFIELD)
		state = LinkState::ROOT;	// this doesnt matter i think
	else
		Set_State(NULL);				// Set le state de root

	Set_UI();						// affichage

	if (dead)
	{
		meta.Add();
		MsgQueue::Register(LINK_ACTIVATED);
	}

	Dsp_Link();
	return true;
}

void Link::Deactivate_Link()					// À DÉTERMINER LORS de la destruction
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
	modifier = REGULAR;	// faut bien reset ça
	//if(type != LinkType::REGULAR)
		/*do stuff*/

	meta.Remove();
	
	if(!ListsOfChainToModify::annihilating)
		MsgQueue::Register(LINK_DEACTIVATED); // we did
}

void Link::Unbound_All_Child()	// Retire tout les child du link. et n'update pas le state
{
	numChild = 0;
	
	for (size_t i = 0; i < 4; i++)
		pWalls[i] = NULL;
}


bool Link::Unbound_Wall_Child(Wall* child)
{
	if (this->state == LinkState::DEAD)		// ça la foiré, ce link n'était même pas en vie
		return false;

	for (size_t i = 0; i < this->numChild; i++)
	{
		if (this->pWalls[i] == child)				// Le wall qu'on veut retirer
		{		
			for (size_t j = i; j < numChild; j++)	// décalage de tout les childs de la liste							
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
			if (state == LinkState::ROOT && modifier == REGULAR)		// Si le root n'a plus de Child, il mourre, SAUF SI C'EST UN MOTHERFUCKER MODIFIER
			{
				this->Deactivate_Link();				
				Er_Link();		// Efface le Link		// Pourrait être mis à pars
			}
		return true;		// success
	}

	return false;	// Ça se peut que le wall ne soit même pas un de ses childs
}



//UI
void Link::Dsp_Link()						// Affiche le Link
{
	ConsoleRender::Add_Char(this->coord, this->sym, this->clr);
}

void Link::Er_Link( )						// Clear le Link
{
	if (!Are_Equal(P1.Get_XY(), Get_XY()))
		ConsoleRender::Add_Char(this->coord, TXT_CONST.SPACE, WHITE);	// Efface pas le player!!
	else
		return;
}