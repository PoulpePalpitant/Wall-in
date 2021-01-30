#include "ev_progress_bar.h"

#include "../../lvls/lvl_script.h"
#include "../events.h"
#include "../../time/spawn_cycle.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/map.h"
#include "ev_final_hour_1.h"
#include "../../lvls/lvl_script.h"


static void Ev_Progress_Animation();
static void Dr_Er_Cursor(bool draw, Coord crd);

static Event ev_ProgressAnimation(Ev_Progress_Animation, 6);	// pour faire afficher un ti progrès dans la bar

static Event ev_ProgressBar(Ev_Progress_Bar);
static Event ev_DrawWholeBar(Ev_Draw_Whole_Bar, 1);

static float ratio;					// Nombre de wave à faire
static float nextWave;				// La wave de l'event actuel
static int waitForNxtSpawn;			// Pendant un break, Si le total de spawn dépasse ce montant, on progresse dans la bar et on stop le break

// UI
static const std::string tip[2] = { "  > "," <  " };
static const int BAR_LENGTH = 100;	// Dimension de la bar OLD
static int nextPuzzle;				// Prochain puzzle

static Coord crd = {};
static const int SPACE_BTW_DOTS = 2;	// Espace entre chaque dots sur la bar
static Colors barProgClr;				// // Est jaune. Devient rouge durant le fianl hour

static void Draw_tip(Coord crd, bool side)	// True = left false = right
{
	if (side)
		ConsoleRender::Add_String(tip[true], crd, BRIGHT_WHITE);
	else
		ConsoleRender::Add_String(tip[false], crd, BRIGHT_WHITE); crd.x +=(int)tip[false].length();
}


void Dr_Er_Cursor(bool draw, Coord crd)
{
	if (draw)
	{
		ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, 194, GRAY); // 1 case en haut
		ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, 193, GRAY); // 1 case en bas
	}
	else
	{
		ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, TXT_CONST.SPACE); // 1 case en haut
		ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, TXT_CONST.SPACE); // 1 case en bass
	}
}


static void Progress()
{
	if (ev_ProgressAnimation.Is_Active())
	{
		ev_ProgressAnimation.Cancel();								
		ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.DOT, barProgClr);	
	}
}


void Ev_Progress_Animation()
{
	if (!ev_ProgressAnimation.Is_Active())
	{
		Dr_Er_Cursor(false, crd);	// delete le curseur précédant
		ev_ProgressAnimation.Activate();
		ev_ProgressAnimation.Start(300);
	}
	else
		while (ev_ProgressAnimation.delay.Tick())
		{
			switch (ev_ProgressAnimation.Get_Current_Step())
			{

			case 1:
				// Début Animation de bar qui flash
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, WHITE);
				ev_ProgressAnimation.Advance(8000);
				break;

			case 2:
				ConsoleRender::Add_Char(crd, TXT_CONST.PLUS, BRIGHT_WHITE);
				ev_ProgressAnimation.Advance(5000);
				break;

			case 3:// Flash la bar 
				ConsoleRender::Add_Char(crd, 254, BRIGHT_WHITE);
				ev_ProgressAnimation.Advance(5000);
				break;

			case 4:
				ConsoleRender::Add_Char(crd, 219, LIGHT_RED);
				ev_ProgressAnimation.Advance(6000);
				break;

			case 5:
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, RED);
				ev_ProgressAnimation.Advance(4000);
				break;

			case 6:
				// Fin animation qui flash
				ConsoleRender::Add_Char(crd, TXT_CONST.DOT, barProgClr);
				ev_ProgressAnimation.Advance(0);


				crd.x += SPACE_BTW_DOTS;				// avance d'une case :`D
				Dr_Er_Cursor(true,crd);						// avance le curseur
				break;
			}
		}
}


void Ev_Draw_Whole_Bar()	// Happens first
{
	static int puzzleMarker;
	static int barLength;
	static float ratio;
	static Colors clr;
	static Coord coord;

	if (!ev_DrawWholeBar.Is_Active())
	{
		puzzleMarker = 0;
		barLength = NUM_PUZZLES[gCurrentLevel - 1];
		clr = GRAY;
		coord = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength) - (int)tip[true].length()  + 2, 3 };	// pos de départ ouch
		Draw_tip(coord, true); coord.x += (int)tip[true].length();	//  left tip

		ev_DrawWholeBar.Activate();
		ev_DrawWholeBar.Start(0);
		if(gCurrentPuzzle[gCurrentLevel - 1] == 0)

			ev_DrawWholeBar.delay.Start_Timer(100000 / 12, barLength);
		else
			ev_DrawWholeBar.delay.Start_Timer(100000, barLength);
	}
	else
		while (ev_DrawWholeBar.delay.Tick())
		{
			if (puzzleMarker == gCurrentPuzzle[gCurrentLevel - 1] )
				Dr_Er_Cursor(true, coord);	// Affiche le curseur au bon endroit

			if (puzzleMarker == barLength - 1)	// Le final houre :O
			{
				ConsoleRender::Add_Char(coord,158, RED); coord.x++;
				Draw_tip(coord, false);		// right tip, à la fin
				ev_DrawWholeBar.Cancel();	// safety
			}
			else
			{
				if (puzzleMarker < gCurrentPuzzle[gCurrentLevel - 1]) // Puzzle déjà fait
					clr = LIGHT_GREEN;
				else
					clr = GRAY;	// Puzzle pas encore fait

				ConsoleRender::Add_Char(coord, TXT_CONST.DOT, clr); coord.x += SPACE_BTW_DOTS;
				puzzleMarker++;
			}
		}
}


void Ev_Progress_Bar()
{
	static int barLength;
	//static Coord crd;

	if (!ev_ProgressBar.Is_Active())
	{
		nextPuzzle = gCurrentPuzzle[gCurrentLevel - 1] + 1; // On se fie à cette valeur pour progresser dans la bar		
		barLength = NUM_PUZZLES[gCurrentLevel - 1];
		crd = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength)+ 2, 3 };	// pos de départ ouch
		crd.x += (gCurrentPuzzle[gCurrentLevel - 1]) * SPACE_BTW_DOTS;

		barProgClr = LIGHT_GREEN;

		if (gSpawnCycleTot == 0)	// Version normal	
			Ev_Draw_Whole_Bar();

		ev_ProgressBar.Activate();
		ev_ProgressBar.Start(1000);
	}
	else
	{
		if (gCurrentPuzzle[gCurrentLevel - 1] == barLength)	// reached the end
		{
			barProgClr = LIGHT_RED;	// it's serious time
			Progress();
			ev_ProgressBar.Cancel();
			return;
		}

		if (gCurrentPuzzle[gCurrentLevel - 1] == nextPuzzle)	// On passe au prochain
		{
			Progress();
			Ev_Progress_Animation();
			nextPuzzle++;
		}
	}

}