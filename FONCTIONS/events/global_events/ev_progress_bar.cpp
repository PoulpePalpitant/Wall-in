#include "ev_progress_bar.h"

#include "../../lvls/lvl_script.h"
#include "../events.h"
#include "../../time/spawn_cycle.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/map.h"

// les cript de break des progress bar
#include "../../lvls/lvl_1/lvl_1_prg_bar_scrpt.h"

static Event ev_ProgressBar(Ev_Progress_Bar, 6);

// got lazy here
// Permet d'inscrire certains "break" dans la progress bar au endroit dans le spawn script ou une certaine longues pause à lieu. J'ai décidé de faire ça manuellement.
// Cette décision m'oblige à updater continuellement les ce script autant que le spawn script si je souhaite une cohérence entre les deux. Heureusement ya pas grand chose à changer

static const int NUM_BREAKS[] = { 3, 1, 1 ,1 };	// Nombre de break dans chaque lvlv
static const int BREAKS_LVL_1[] = { 15,39,49 };	// List de tout les moment de repos dans le script de spawn.
static const int BREAKS_LVL_2[] = { 120 };	
static const int BREAKS_LVL_3[] = { 120 };	
static const int BREAKS_LVL_4[] = { 120 };	

// Par Level
static const int numWaves[] = { 120 };	// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
static const int finalhour[] = { 100 };	// À quel wave le final hour aura lieu


static float ratio;					// Nombre de wave à faire
static float nextWave;				// La wave de l'event actuel

// UI
static const std::string tip[2] = { " > "," < " };
static const int barLength = 30;	// Dimension de la bar
static Coord crd;

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
		ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); crd.x++;
		ConsoleRender::Add_String(tip[true], crd, BRIGHT_WHITE);
	}
	else
	{
		ConsoleRender::Add_String(tip[false], crd, BRIGHT_WHITE); crd.x +=(int)tip[false].length();
		ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); 
	}
}

static void Draw_Whole_Bar(int lvl)	// Happens first
{
	int waveTot = 0;
	float nextWave = 0;
	float ratio = numWaves[gCurrentLevel - 1] / (float)barLength;
	Colors baseClr = GRAY;

	crd = { Find_Ctr_X(barLength) - (int)tip[true].length() - 1, map.Get_Box_Limit(UP) - 3 };	// pos de départ

	Draw_tip(true); crd.x += (int)tip[true].length();	//  left tip

	// Draw chaque ligne (devrait s'arrêter à 30 théoriquement )
	for (waveTot = 0; waveTot < numWaves[lvl]; waveTot++)
	{
		if (Is_Break_Here(lvl, waveTot)) // Check si on draw un break ici
		{
			// Affiche le symbole du break
			ConsoleRender::Add_Char(crd, TXT_CONST.LINE_VER, GREEN); crd.x++;
		}
		else
			if (finalhour[lvl] == waveTot)
			{
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_VER, LIGHT_RED); crd.x++;
				baseClr = RED;
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


// Signale au joueur combien de waves y reste avant la fin
void Ev_Progress_Bar()
{
	if (!ev_ProgressBar.Is_Active())
	{
		ratio = (numWaves[gCurrentLevel - 1] + NUM_BREAKS[gCurrentLevel - 1]) / (float)barLength;	// On se fie à cette valeur pour progresser dans la bar
		Draw_Whole_Bar(gCurrentLevel - 1);
		crd = { Find_Ctr_X(barLength) /*+ (int)tip[true].length() + 1*/, map.Get_Box_Limit(UP) - 3 };	// pos de départ

		ev_ProgressBar.Activate();
		ev_ProgressBar.Start(1000);
		ev_ProgressBar.delay.Start_Timer(1000,1 , true);
	}
	else
		while (ev_ProgressBar.delay.Tick())
		{
			if (gSpawnCycleTot == numWaves[gCurrentLevel - 1])	// reached the end
			{
				ev_ProgressBar.Cancel();
				return;
			}
			else
				if ((int)nextWave == gSpawnCycleTot)	// On passe au prochain
				{
					nextWave += ratio;
					crd.x++;
					ev_ProgressBar.Go_To_X_Step(1);
					ev_ProgressBar.delay.Stop();
					ev_ProgressBar.delay.Start_Timer(5000); // Start l'animation d'une wave
				}
				else
					if (Is_Break_Here(gCurrentLevel - 1, gSpawnCycleTot))
					{
						crd.x++;
						ev_ProgressBar.Go_To_X_Step(6); 					// start l'animation du break
						ev_ProgressBar.delay.Stop();
						ev_ProgressBar.delay.Start_Timer(gSpwBotTimer.Get_Speed(), 1, true);
					}

			switch (ev_ProgressBar.Get_Current_Step())
			{
			case 0: break;
			case 1:
				// Début Animation de bar qui flash
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, BRIGHT_WHITE);
				ev_ProgressBar.Advance(5000);
				break;

			case 2:// Flash la bar 
				ConsoleRender::Add_Char(crd, 254, BRIGHT_WHITE);
				ev_ProgressBar.Advance(5000);
				break;


			case 3:
				ConsoleRender::Add_Char(crd, 219, LIGHT_RED); 
				ev_ProgressBar.Advance(5000);
				break;

			case 4:
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, RED);
				ev_ProgressBar.Advance(5000);
				break;

			case 5:
				// Fin animation qui flash
				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, LIGHT_YELLOW); 
				ev_ProgressBar.Go_To_X_Step(0);
				ev_ProgressBar.delay.Start_Timer(5000, 1 , true);
				break;

			case 6:
				if (gSpawnCycleTot % 2 == 0)
				{	// Animation qui flash
					ConsoleRender::Add_Char(crd, TXT_CONST.DOT, LIGHT_YELLOW);	// sur la bar 
					ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, TXT_CONST.DOT, BRIGHT_WHITE); // 1 case en haut
					ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, TXT_CONST.DOT, BRIGHT_WHITE); // 1 case en bas
				}
				else { // une fois sur deux, on efface pour clignoter
					ConsoleRender::Add_Char(crd, TXT_CONST.DOT, LIGHT_GREEN);	// sur la bar 
					ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, TXT_CONST.SPACE); // 1 case en haut
					ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, TXT_CONST.SPACE); // 1 case en bas

				}

				break;	// Devrait être canceléé par le progrès dans les spawn wave
			}
		}

}
