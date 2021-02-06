#include <thread>

#include "../grid/AllGrids.h"
#include "../animation/UI_move_blast.h"
#include "../player/player.h"
#include "../events/msg_dispatcher.h"
#include "../items/item_list.h"
#include "blast_modifier_queue.h"
#include "../lvls/lvl_script.h" 
#include "blast.h"
#include "mod_queue_animator.h"
#include "../events/global_events/feedback/ev_blast_splash.h"

extern const Distance DFLT_BLAST_LENGTH_HOR = DELTA_X + 1;		// Le +1 c'est pour afficher l'extrémité du blast
extern const Distance DFLT_BLAST_LENGTH_VER = DELTA_Y + 1;		
extern const time_t DFLT_BLAST_SPD_VER = 85000;		
extern const time_t DFLT_BLAST_SPD_HOR = DFLT_BLAST_SPD_VER * 2;

extern const BlastType DFLT_BLAST =	{WallType::REGULAR, Modifier::REGULAR};

// PEW PEW!!

extern Blast blastP1 = {}; 

// PEW PEW!!	


void Blast::Setup_Blast(GrdCoord& newStartPos, Direction& newblastDir, bool consume)
{
	dir = newblastDir;							
	Setup_Length();								
	Setup_Grid_Limit();							
	Setup_Speed(this->wallType == WallType::ENERGIZED);								
	Setup_Dist_Btw_Links();						

	if (consume)
		BlastModifierQueue::Consume_Next_Modifier();	// Faut que le blast franchis une distance pour consommer un modifier

	Setup_Blast_UI();							
	Change_To_Modifier_Color();					
	Setup_Position_Incrementors(newStartPos);	

	nbSteps = movesTillNxtLink = 0;		// Nombre de case que le blast à traversé et nombre de case avant un link	(on start sur un link, donc zéro ici)
	active = true;						
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Blast::Change_To_Modifier_Color()
{
	if (modifier == Modifier::BLOCKER)
		color = LIGHT_RED;
	else
		if (modifier == Modifier::BUFFER)
			color = LIGHT_YELLOW;
}

void Blast::Setup_Blast_UI()	
{
	if (wallType == WallType::REGULAR || wallType == WallType::ENERGIZED)
	{
		switch (dir)
		{
		case UP:
		case DOWN: sym = (int)WallSym::SYM_VER; break;
		case LEFT:
		case RIGHT:sym = (int)WallSym::SYM_HOR; break;
		}

		if (wallType == WallType::REGULAR)
			color = Colors::WHITE;
		else
		{
			color = Colors::LIGHT_PURPLE;
			color = Colors::LIGHT_AQUA;
			
		}
		return;
	}

	if (wallType == WallType::STRONG)
	{
		switch (dir)
		{
		case UP:
		case DOWN: sym = (int)WallSym::SYM_VER2; color = Colors::WHITE; break;
		case LEFT:
		case RIGHT:sym = (int)WallSym::SYM_HOR2; color = Colors::WHITE; break;
		}
		return;
	}

	if (wallType == WallType::WEAK)
	{
		switch (dir)
		{
		case UP:
		case DOWN: 	sym = (int)WallSym::SYM_VER3;break;

		case LEFT:
		case RIGHT:	sym = (int)WallSym::SYM_HOR3;
		}
		
		color = Colors::GRAY;
		return;
	}
}

void Blast::Setup_Length()		
{
	switch (dir)		
	{
	case UP:	case DOWN: this->length = maxlengthVer; break;	
	case LEFT:	case RIGHT:this->length = maxlengthHor; break;	
	}
}

void Blast::Setup_Dist_Btw_Links()
{
	switch (dir)
	{
	case UP:
	case DOWN: btwLinks = DELTA_Y - 1; break;
	case LEFT:
	case RIGHT: btwLinks = DELTA_X - 1; break;
	}
}


void Blast::Setup_Grid_Limit()
{
	// L'axe du grid, c'est celui de "grdPosition.axis". il est intialisé juste au dessus, dans l'autre fonction	o(-^^-)o
	switch (dir)
	{
	case UP:														
	case LEFT:	grdLimit = 0; break;								

	case DOWN:	grdLimit = linkGrid->Get_Rows() - 1; break;			
	case RIGHT:	grdLimit = linkGrid->Get_Cols() - 1;				
	}
}

void Blast::Setup_Speed(bool quick)											
{
	switch (dir)
	{
	case UP:case DOWN:		
		speed = (int)speedVer;	break;
	case LEFT:case RIGHT:	
		speed = (int)speedHor;	break;	
	}

	if (quick)
		speed *= 2.2;	
	else
		if (gCurrentLevel == 3)
			speed *= 1.2;	// Le niveau 3 est plus large, alors le blast est un ti peu plus vite

	updateTimer.Start_Timer(speed, 1, true);	
}

void Blast::Setup_Position_Incrementors(GrdCoord& startPos)	
{
	grdPos.Initialize_All(startPos, dir);

	frontXY.Initialize_Axis(dir);
	Equal_Coordinates(frontXY.coord, linkGrid->link[startPos.c][startPos.r].Get_XY());	

	tailXY.Initialize_Axis(dir);
	tailXY.coord = frontXY.coord;					// Head and tail commence avec le même XY
}


void Blast::Setup_Modifier(Modifier mod)										
{
	modifier = mod;
	P1.Upd_Color();	
}


bool Blast::Is_Player_Shooting_Border(Direction dir)			
{
	GrdCoord crd = P1.Get_Grd_Coord();

	if (crd.r == linkGrid->Get_Rows() - 1 && dir == DOWN)
		return true;

	if (crd.c == linkGrid->Get_Cols() - 1 && dir == RIGHT)
		return true;

	if (crd.r == 0 && dir == UP)
		return true;

	if (crd.c == 0 && dir == LEFT)
		return true;
	
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!

void Blast::UPD_Blast_Shot()
{
	if (active)
	{
		if (UI_MoveBlast::eraserTimer.Is_On())	// efface le blast seulement si aucun mur ne seront créés
		{
  			UI_MoveBlast::Erase_Whole_Blast(this);	// Va continuer d'effacer le blast avant de le réactiver
			return;
		}

		// Va avancer le blast à chaque fois que le countdown tombe à zéro
		while (updateTimer.Tick())
		{
			if (!Has_Reached_Limit())											
			{
				if (Blast_Is_On_LinkGrid())										
				{
					if (nbSteps)					// Si le blast n'est pas sur sa première position de départ
					{
						grdPos.Increment_Coord();	
						ItemsOnGrid::Pickup_Item_Here(grdPos.index);

						if (linkGrid->Is_Link_Alive_Here(grdPos.index))
						{
							if (linkGrid->link[grdPos.index.c][grdPos.index.r].Get_Modifier() == Modifier::FORCEFIELD && wallType != WallType::REGULAR)	// Blast peut passé à travers les forcefield
							{
								this->Setup_Speed(1);						// Gonna be a fastblast!
								
								if (wallType == WallType::WEAK)
								{
									this->Set_WallType(WallType::REGULAR);
									this->Setup_Blast_UI();
								}

 								if (Is_Next_Wall_Active())
								{
									Stop_Blast();	// Blast ne peut passé à travers le link. Car 1 mur se trouve derrière
									continue;
								}
								else
									ffToRedraw.push_back(grdPos.index);
							}
							else
							{
								Stop_Blast();	
								continue;
							}
						}
					}
					Reset_Countdown_Till_Nxt_Link();	
				}
				else
				{
					movesTillNxtLink--;	
				}

				// ANIMATION!!! sort of
				UI_MoveBlast::Animate_Blast(this);

				if (!ffToRedraw.empty())	// Lazy animation fix pour les force field: ceci redraw chaque forcefield rencontré par le blast
					for (int i = 0; i < ffToRedraw.size(); i++)
						linkGrid->link[ffToRedraw.at(i).c][ffToRedraw.at(i).r].Dsp_Link();

				frontXY.Increment_Coord();	
				nbSteps++;	
			}
			else
			{
				length--;	// Ceci est un dumb fix pour l'affichage/ résoud un bug d'affichage quand tu tir sur la bordure avec juste un tit blocker, ça effac¸ait trop loin
				nbSteps--;	// vraiment dumb

				Stop_Blast();
				continue;
			}

		}
	}
}
// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!


void Blast::Stop_Blast()	
{
	if (active)
	{
		UI_MoveBlast::Erase_Blast_Tail(this); 	

		while (!ffToRedraw.empty())	// vide cette liste de merde
			ffToRedraw.pop_back();

		P1.Upd_Sym_From_Direction(dir);
		P1.Dr_Player();				// Faut réafficher le joueur après le tir

		// Le Blast peut resté actif si il ne créé pas de mur. Il faut attendre que ses char soit effacés
		active = gGrids.Activate_Walls_And_Links_From_Blast(this);	// Active les murs qui ont été tirés, ou convertit un link, ou élimine le blast complètement
		updateTimer.Stop();
		

		Setup_Modifier(REGULAR);	// spaghetti
	}
}



bool Blast::Blast_Is_On_LinkGrid()
{
	if (this->movesTillNxtLink == 0)	
		return true;
	else
		return false;
}

bool Blast::Has_Reached_Limit()
{
	if (*grdPos.axis == grdLimit)
		return true;			
	else
		return false;					
}										

bool Blast::Is_Next_Wall_Active()	
{
	Wall* wall = gGrids.Find_Wall_From_Link_Coord_Incrementor(this->grdPos, dir); 

	if (wall == NULL)
		return false;
	else
		return wall->Get_State() != WallState::DEAD;	
}

// POST-BLAST
// **********


int Blast::Nb_Of_Links_To_Activate()
{
	if (nbSteps == 0)	
		return 0;
	else
		if (nbSteps >= length)		
			return 1 + (length) / (btwLinks + 1);	
		else
			return 1 + nbSteps / (btwLinks + 1);	
}

int Blast::Nb_Of_Walls_Per_Blast()
{
	if (nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player à sûrement tiré sur la bordure)
		return 0;
	else
		if (nbSteps >= length)		
			return length / (btwLinks + 1);
		else
			return nbSteps / (btwLinks + 1); //works
}

// SPECIAL
// -- - - -

void Blast::Clear_Blast()	
{
	int toErase;
	if (nbSteps >= length)		
		toErase = length;
	else
		toErase = nbSteps;
	for (int i = 0; i < toErase; i++)
		UI_MoveBlast::Erase_Blast_Tail(this);

	DrawModifierQueue::Hide_Queue_UI();

	ammo.Deactivate();
	this->Cancel();
}