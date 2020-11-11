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
static void Ev_Break_Animation();
static void Dr_Er_Cursor(bool draw);

static Event ev_ProgressAnimation(Ev_Progress_Animation, 6);	// pour faire afficher un ti progrès dans la bar
static Event ev_BreakAnimation(Ev_Break_Animation, 1);	// Animation surt les points break
static Event ev_ProgressBar(Ev_Progress_Bar);
static Event ev_DrawWholeBar(Ev_Draw_Whole_Bar, 1);
static Event ev_DrawWholeBarFast(Ev_Draw_Whole_Bar_Fast, 1);



// got lazy here
// Permet d'inscrire certains "break" dans la progress bar au endroit dans le spawn script ou une certaine longues pause à lieu. J'ai décidé de faire ça manuellement.
// Cette décision m'oblige à updater continuellement les ce script autant que le spawn script si je souhaite une cohérence entre les deux. Heureusement ya pas grand chose à changer




static float ratio;					// Nombre de wave à faire
static float nextWave;				// La wave de l'event actuel
static int waitForNxtSpawn;			// Pendant un break, Si le total de spawn dépasse ce montant, on progresse dans la bar et on stop le break

// UI
static const std::string tip[2] = { "  > "," <  " };
static const int barLength = 100;	// Dimension de la bar
static Coord crd;
static Colors barProgClr;	// // Est jaune. Devient rouge durant le fianl hour

static bool Is_Checkpoint_Here(int lvl, int waveTot)	// Check si un checkpoint  à lieu ici
{
	int const* pCHECKPOINT_LVL;	// le pointeurs vers les checkpoints de niveau

	switch (lvl + 1)	// vraiment cave
	{
	case 1:pCHECKPOINT_LVL = LVL1_CHECKPOINT; break;
	case 2:pCHECKPOINT_LVL = LVL2_CHECKPOINT; break;
	case 3:pCHECKPOINT_LVL = LVL3_CHECKPOINT; break;
	case 4:pCHECKPOINT_LVL = LVL4_CHECKPOINT; break;
	default: return false;
	}

	for (int i = 0; i < NUM_CHECKPOINT[lvl]; i++)
	{
		if (waveTot == pCHECKPOINT_LVL[i])
			return true;
	}
	return false;
}

static void Draw_tip(Coord crd, bool side)	// True = left false = right
{
	if (side)
	{
		//ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); crd.x++;
		ConsoleRender::Add_String(tip[true], crd, BRIGHT_WHITE);
	}
	else
	{
		ConsoleRender::Add_String(tip[false], crd, BRIGHT_WHITE); crd.x +=(int)tip[false].length();
		//ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); 
	}
}

void Ev_Draw_Whole_Bar()	// Happens first
{
	static int waveTot;
	static float nextWave;
	static float ratio;
	static Colors baseClr;
	static Coord coord;

	if (!ev_DrawWholeBar.Is_Active())
	{
		waveTot = nextWave = 0;
		ratio = (NUMWAVES[gCurrentLevel - 1]) / ((float)barLength);
		baseClr = GRAY;
		coord = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - (int)tip[true].length() , map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
		Draw_tip(coord, true); coord.x += (int)tip[true].length();	//  left tip

		ev_DrawWholeBar.Activate();
		ev_DrawWholeBar.Start(0);
		ev_DrawWholeBar.delay.Start_Timer(100000, NUMWAVES[gCurrentLevel - 1]);
	}
	else
		while (ev_DrawWholeBar.delay.Tick())
		{
			if (FINALHOUR[gCurrentLevel - 1] == waveTot) // Check si on draw le finalhour ici
			{
				finalHour = coord;
				ConsoleRender::Add_Char(coord, TXT_CONST.LINE_VER, LIGHT_RED); coord.x++;
				baseClr = RED;
				nextWave += ratio;
				
			}
			else
				if (Is_Checkpoint_Here(gCurrentLevel - 1, waveTot)) // draw checkpoint
				{
					// Affiche le symbole du break
					ConsoleRender::Add_Char(coord, '|', LIGHT_GREEN); coord.x++;
					nextWave += ratio;
				}
				else
					if ((int)nextWave == waveTot)	// On passe au prochain
					{
						ConsoleRender::Add_Char(coord, TXT_CONST.DOT, baseClr); coord.x++;
						nextWave += ratio;
						// Start l'animation du prochain
					}

			waveTot++;
		}

	if (!ev_DrawWholeBar.delay.Is_On())
	{
		Draw_tip(coord, false);	// right tip, à la fin
		ev_DrawWholeBar.Cancel();	// safety
	}

}

void Ev_Draw_Whole_Bar_Fast()	// Happens first
{
	static int waveTot;
	static float nextWave;
	static float ratio;
	static Colors baseClr;
	static Coord coord;

	if (!ev_DrawWholeBarFast.Is_Active())
	{
		waveTot = nextWave = 0;
		ratio = (NUMWAVES[gCurrentLevel - 1]) / ((float)barLength);
		baseClr = GRAY;
		coord = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - (int)tip[true].length() , map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
		Draw_tip(coord, true); coord.x += (int)tip[true].length();	//  left tip

		ev_DrawWholeBarFast.Activate();
		ev_DrawWholeBarFast.Start(0);

		//if (gSpawnCycleTot >= FINALHOUR[gCurrentLevel - 1] - 5)
		//	ev_DrawWholeBarFast.delay.Start_Timer(200000 * 5, NUMWAVES[gCurrentLevel - 1]);
		//else
			ev_DrawWholeBarFast.delay.Start_Timer(200000, NUMWAVES[gCurrentLevel - 1]);
	}
	else
		while (ev_DrawWholeBarFast.delay.Tick())
		{
			if (FINALHOUR[gCurrentLevel - 1] == waveTot) // Check si on draw le finalhour ici
			{
				finalHour = coord;
				ConsoleRender::Add_Char(coord, TXT_CONST.LINE_VER, LIGHT_RED); coord.x++;
				baseClr = RED;
				nextWave += ratio;
			}
			else
				if (Is_Checkpoint_Here(gCurrentLevel - 1, waveTot)) // draw checkpoint
				{
					// Affiche le symbole du break
					ConsoleRender::Add_Char(coord, '|', LIGHT_GREEN); coord.x++;
					nextWave += ratio;
				}
				else
					if ((int)nextWave == waveTot)	// On passe au prochain
					{
						if (nextWave >= gSpawnCycleTot)
						{
							ConsoleRender::Add_Char(coord, TXT_CONST.DOT, baseClr); coord.x++;
						}
						else
						{
							ConsoleRender::Add_Char(coord, TXT_CONST.DOT, barProgClr); coord.x++;
						}

						
						nextWave += ratio;
						// Start l'animation du prochain
					}
			waveTot++;
		}

	if (!ev_DrawWholeBarFast.delay.Is_On())
	{
		Draw_tip(coord, false);	// right tip, à la fin
		ev_DrawWholeBarFast.Cancel();	// safety
	}

}



static void Progress()
{
	nextWave += ratio;
	Dr_Er_Cursor(false);	// delete le curseur précédant
	crd.x++;	// avance d'une case :`D
	if (ev_ProgressAnimation.Is_Active())
	{
		ev_ProgressAnimation.Cancel();								// lazy shit
		ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.DOT, barProgClr);	// lazy shit
	}
}

// pas de spawn sur les break? Pas de spawn sur les break!|
// Signale au joueur combien de waves y reste avant la fin 
void Ev_Progress_Bar()
{
	if (!ev_ProgressBar.Is_Active())
	{
		nextWave = 0;
		ratio = NUMWAVES[gCurrentLevel - 1] / ((float)barLength);	// On se fie à cette valeur pour progresser dans la bar		
		crd = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - 1, map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
		barProgClr = LIGHT_YELLOW;

		if (gSpawnCycleTot == 0)	// Version normal	
			Ev_Draw_Whole_Bar();
		else
		{
			Ev_Draw_Whole_Bar_Fast();	// Version checkpoint: Commence la progression plus loin sur la bar (à l'endroit ou le checkpoint est)

			while (nextWave < gSpawnCycleTot)
				Progress();
		}


		ev_ProgressBar.Activate();
		ev_ProgressBar.Start(1000);
		ev_ProgressBar.delay.Start_Timer(20000, 1, true);
	}
	else
		while (ev_ProgressBar.delay.Tick())
		{
			if (gSpawnCycleTot == NUMWAVES[gCurrentLevel - 1])	// reached the end
			{
				ev_ProgressBar.Cancel();
				return;
			}

			// if final hour?
			if (gSpawnCycleTot == FINALHOUR[gCurrentLevel - 1])
			{
				if (barProgClr != LIGHT_RED) // dumb condition, but understandable
				{
					Progress(); 
					barProgClr = LIGHT_RED;	// it's serious time
					Ev_Break_Animation();	// start l'animation du drette sur le FINALHOUR
				}

				continue;
			}

			if (ev_BreakAnimation.Is_Active())	// Si l'animation de break est active
			{
				if (waitForNxtSpawn != gSpawnCycleTot)	// Faut attendre le prochain spawn
				{
					ev_BreakAnimation.Cancel();// Stop le break
					Progress();	// Quand un break arrive, il faut avancer de 2 le ratio, sinon ça décale
					Ev_Progress_Animation(); // progress
				}
			}
			else
				if (Is_Checkpoint_Here(gCurrentLevel - 1, gSpawnCycleTot))
				{
					waitForNxtSpawn = gSpawnCycleTot;
					Progress();	// we progress
					Ev_Break_Animation();	// start l'animation du break
				}
				else
					if ((int)nextWave == gSpawnCycleTot)	// On passe au prochain
					{
						Progress(); // efface le curseur précédant et on avance
						Ev_Progress_Animation();
					}
		}
}


void Ev_Progress_Animation()
{
	if (!ev_ProgressAnimation.Is_Active())
	{
		Dr_Er_Cursor(true);	// avance le curseur
		ev_ProgressAnimation.Activate();
		ev_ProgressAnimation.Start(7000);
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
				break;
			}
		}
}



void Ev_Break_Animation()
{
	static bool draw;
	if (!ev_BreakAnimation.Is_Active())
	{
		draw = true;
		ev_BreakAnimation.Activate();
		ev_BreakAnimation.Start(0);
		ev_BreakAnimation.delay.Start_Timer(gSpwBotTimer.Get_Speed() * 2, 1, true);
	}
	else
		while (ev_BreakAnimation.delay.Tick())
		{
			if (draw)
			{	// Animation qui flash
				//ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// sur la bar 
				Dr_Er_Cursor(true);
				draw = false;
			}
			else { // une fois sur deux, on efface pour clignoter
				//ConsoleRender::Add_Char(crd, TXT_CONST.DOT, LIGHT_GREEN);	// sur la bar 
				Dr_Er_Cursor(false);
				draw = true;
			}

		}
}


void Dr_Er_Cursor(bool draw)
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
