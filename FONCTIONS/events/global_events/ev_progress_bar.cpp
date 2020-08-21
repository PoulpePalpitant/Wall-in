#include "ev_progress_bar.h"

#include "../../lvls/lvl_script.h"
#include "../events.h"
#include "../../time/spawn_cycle.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/map.h"
// les cript de break des progress bar
#include "../../lvls/lvl_1/lvl_1_prg_bar_scrpt.h"

static void Ev_Progress_Animation();
static void Ev_Break_Animation();
static void Dr_Er_Cursor(bool draw);


static Event ev_ProgressAnimation(Ev_Progress_Animation, 6);	// pour faire afficher un ti progrès dans la bar
static Event ev_BreakAnimation(Ev_Break_Animation, 1);	// Animation surt les points break
static Event ev_ProgressBar(Ev_Progress_Bar);

// got lazy here
// Permet d'inscrire certains "break" dans la progress bar au endroit dans le spawn script ou une certaine longues pause à lieu. J'ai décidé de faire ça manuellement.
// Cette décision m'oblige à updater continuellement les ce script autant que le spawn script si je souhaite une cohérence entre les deux. Heureusement ya pas grand chose à changer

static const int NUM_BREAKS[] = { 5, 1, 1 ,1 };	// Nombre de break dans chaque lvlv
static const int BREAKS_LVL_1[] = { 2,10,20,39,49 };	// List de tout les moment de repos dans le script de spawn.
static const int BREAKS_LVL_2[] = { 120 };	
static const int BREAKS_LVL_3[] = { 120 };	
static const int BREAKS_LVL_4[] = { 120 };	

// Par Level
static const int numWaves[] = { 120 };	// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
static const int finalhour[] = { 100 };	// À quel wave le final hour aura lieu


static float ratio;					// Nombre de wave à faire
static float nextWave;				// La wave de l'event actuel
static int waitForNxtSpawn;			// Pendant un break, Si le total de spawn dépasse ce montant, on progresse dans la bar et on stop le break

// UI
static const std::string tip[2] = { "  > "," <  " };
static const int barLength = 40;	// Dimension de la bar
static Coord crd;
static Colors progClr;	// // Est jaune. Devient rouge durant le fianl hour

static bool Is_Break_Here(int lvl, int waveTot)	// Check si un break à lieu ici
{
	for (int i = 0; i < NUM_BREAKS[lvl]; i++)
	{
		if (waveTot == BREAKS_LVL_1[i])
			return true;
	}
	return false;
}

static void Draw_tip(bool side)	// True = left false = right
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

static void Draw_Whole_Bar(int lvl)	// Happens first
{
	int waveTot = 0;
	float nextWave = 0;
	float ratio = (numWaves[lvl]) / ((float)barLength );
	Colors baseClr = GRAY;

	crd = { Find_Ctr_X(barLength) - (int)tip[true].length() /*- 1*/, map.Get_Box_Limit(UP) - 3 };	// pos de départ

	Draw_tip(true); crd.x += (int)tip[true].length();	//  left tip

	// Draw chaque ligne (devrait s'arrêter à 30 théoriquement )
	for (waveTot = 0; waveTot < numWaves[lvl]; waveTot++)
	{
		if (Is_Break_Here(lvl, waveTot)) // Check si on draw un break ici
		{
			// Affiche le symbole du break
			ConsoleRender::Add_Char(crd, '|', LIGHT_GREEN); crd.x++;
			nextWave += ratio;
		}
		else
			if (finalhour[lvl] == waveTot)
			{
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_VER, LIGHT_RED); crd.x++;
				baseClr = RED;
				nextWave += ratio;
			}
			else
				if ((int)nextWave == waveTot)	// On passe au prochain
				{
					ConsoleRender::Add_Char(crd, TXT_CONST.DOT, baseClr); crd.x++;
					nextWave += ratio;
					// Start l'animation du prochain
				}
	}

	Draw_tip(false);	// right tip
}

// pas de spawn sur les break? Pas de spawn sur les break!|


static void Progress()
{
	nextWave += ratio;
	Dr_Er_Cursor(false);	// delete le curseur précédant
	crd.x++;	// avance d'une case :`D
	if (ev_ProgressAnimation.Is_Active())
	{
		ev_ProgressAnimation.Cancel();								// lazy shit
		ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.DOT, progClr);	// lazy shit
	}
}



// Signale au joueur combien de waves y reste avant la fin
void Ev_Progress_Bar()
{
	if (!ev_ProgressBar.Is_Active())
	{
		Draw_Whole_Bar(gCurrentLevel - 1);
		ratio = numWaves[gCurrentLevel - 1] / ((float)barLength);	// On se fie à cette valeur pour progresser dans la bar
		crd = { Find_Ctr_X(barLength) - 1, map.Get_Box_Limit(UP) - 3 };	// pos de départ
		nextWave = 0;
		progClr = LIGHT_YELLOW;

		ev_ProgressBar.Activate();
		ev_ProgressBar.Start(1000);
		ev_ProgressBar.delay.Start_Timer(20000, 1, true);
	}
	else
		while (ev_ProgressBar.delay.Tick())
		{
			if (gSpawnCycleTot == numWaves[gCurrentLevel - 1])	// reached the end
			{
				ev_ProgressBar.Cancel();
				return;
			}

			if (gSpawnCycleTot == finalhour[gCurrentLevel - 1])
			{
				if (progClr != LIGHT_RED) // dumb condition, but understandable
				{
					Progress(); 
					progClr = LIGHT_RED;	// it's serious time
					Ev_Break_Animation();	// start l'animation du drette sur le finalhour
				}

				continue;
			}

			// if final hour?
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
				if (Is_Break_Here(gCurrentLevel - 1, gSpawnCycleTot))
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
				ConsoleRender::Add_Char(crd, TXT_CONST.DOT, progClr);
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
