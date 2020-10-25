#include "blast_ammo_animator.h"

#include "../UI/map.h"
#include "../events/events.h"

namespace DrawBlastAmmo {

	static Event ev_DrFullBar(Ev_Dr_Bar_From_Scratch, MAX_BAR_SIZE);

	bool isShown = false;		// si le player vois l'UI 
	bool erDozen = false;		// si on doit effacer la dizaine
	float ratio = 1;			// Nombre de munition pour chaque char de la bar 
	int nextAmmoEr = 1;			// Le nombre de munition à atteindre pour progresser dans la bar

	//	UI
	Colors progClr = BRIGHT_WHITE;				// Couleur des chars de la bar -> blanc -> jaune -> rouge	selon la progression
	Distance btwTitle = 4;		// Distance entre le titre de la queue et la limite gauche à droite. On va slide les charactère à gauche et à droite. 
	Distance mapToBar = 4;			// Distance entre la bordure de la map et la bar
	Distance barToCount	 = 2;		// Distance entre la bar et le nombre représentant l'ammo count
	int barLength = MAX_BAR_SIZE;				// Dimension de la bar actuelle


	static Coord Get_Ori()		// Permet de trouver la coord d'origine d'où on va afficher la bar
	{
		return { map.Get_Box_Limit(RIGHT) + mapToBar, map.Get_Ctr_Y() / 2 };
	}


	// Détermine la couleur de la bar selon le pourcentage d'ammo utilisé
	// ----------------------------------------------

	Colors Get_Treshold_Color(int barLength)	// Retourne la couleur que la bar aurait selon une longueur
	{
		static Colors clr;
		static float tresholds[2];
		tresholds[0] = MAX_BAR_SIZE * prcentClrTresh[0];
		tresholds[1] = MAX_BAR_SIZE * prcentClrTresh[1];

		if (barLength > tresholds[0])
			clr = treshClr[0];
		else
			if (barLength > tresholds[1])
				clr = treshClr[1];
			else
				clr = treshClr[2];
		return clr;
	}

	// Change la couleur de la bar selon le pourcentage d'ammo utilisé
	void Upd_Progression_Color()
	{
		progClr = Get_Treshold_Color(barLength);
	}

	// Affiche la bar au complet pour la première foi
	// **********************************************

	void Ev_Dr_Bar_From_Scratch()	
	{
		static Coord ori;
		static int barSize;

		if (!ev_DrFullBar.Is_Active())
		{
			barSize = 0;
			ori = Get_Ori();	// Le point d'origine de la bar
			ev_DrFullBar.Activate();
			ev_DrFullBar.Start(0);
			ev_DrFullBar.delay.Start_Timer(20000, 1,true);
		}
		else
		{
			while (ev_DrFullBar.delay.Tick())
			{
				Dr_Or_Er_Bar(barSize, Get_Treshold_Color(barSize));

				if(++barSize == barLength)
					ev_DrFullBar.Cancel();
			}
		}
	}

	void Ev_Dr_Ammo_Count_From_Scratch()		 // Affiche le nombre d'ammo de manière progressive
	{
		return;
	}

	// AFFICHAGES INSTANTANNÉE DE L'UI
	// *******************************

	void Dr_Or_Er_Bar(int length, Colors clr , bool erase) // Affiche la bar, selon une couleur
	{
		Coord ori = Get_Ori();	// Le point d'origine de la bar

		if (length == 0 && !erase)
			ConsoleRender::Add_Char(ori, ctrSym, clr);	// Symbole d'ammo vide central
		else
			ConsoleRender::Add_Char(ori, barSym, clr);	// Ammo non vide, la bar sera donc uniforme

		for (int i = 1; i <= length; i++)
		{
			Dr_Bar_Tips(i,clr,erase);
		}
	}

	void Dr_Bar_Tips(int distance, Colors clr, bool erase) // Affiche les extrémité de la bar. 0 ne possède pas de tip. 
	{
		if (distance <= 0) // On n'affiche pas le point central avec ça
			return; 

		static Coord ori; ori = Get_Ori();	// Le point d'origine de la bar
		ConsoleRender::Add_Char({ ori.x ,ori.y + distance }, barSym, clr);	// Char en haut du point central
		ConsoleRender::Add_Char({ ori.x ,ori.y - distance }, barSym, clr);	// Char en bas du point central
	}

	void Hide_Ammo_UI() // Efface l'ui instantannément
	{
		Dr_Or_Er_Bar(MAX_BAR_SIZE, WHITE, true);
		isShown = false;
	}

	// ACTIVATION DE L'UI POUR LES YEUX
	//******************************

	void Show_Ammo_UI(bool instant)
	{
		barLength = MAX_BAR_SIZE;	// Cette size pourrait être relative
		ratio = barLength / blastP1.Get_Ammo_Manager().Get_Nb_Ammo();
		nextAmmoEr = barLength - ratio;

		if (instant)
		{
			Dr_Or_Er_Bar(barLength, LIGHT_GREEN);
		}
		else
		{
			if (!isShown)
			{
				Ev_Dr_Bar_From_Scratch();				 // Draw la bar au complet
				Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de manière progressive
			}
		}

		isShown = true;
	}
//
//
//	bool DrawerQueue::Is_Active(int index)
//	{
//		if (index > MAX_QUEUE_SIZE - 1)
//			return false;//throw " brah tahts too far";
//		else
//			return drawer[index].active;
//	}
//
//	void DrawerQueue::Remove(int index)	// On delete rien au final
//	{
//		drawer[index].active = false;
//		total--;
//	}
//	void DrawerQueue::Remove_All()
//	{
//		for (int i = 0; i < MAX_QUEUE_SIZE; i++)
//			drawer[i].active = false;
//		total = 0;
//	}
//
//	void DrawerQueue::Cancel()	// Modifie une animation en cours si on cancel. Il faut soit effacer, ou empêcher de draw les char aux endroits qu'ils ne devraient pas être
//	{
//		for (int index = 0; index < MAX_QUEUE_SIZE; index++)
//			drawer[index].cancel = true;
//
//	}
//
//	bool DrawerQueue::Add_To_Index(Modifier modifier, int index)		// Ajoute l'item à draw à la fin de la liste
//	{
//		static Drawer tempDrawer = {};
//
//		if (Is_Active(index))	// temp solution
//			Remove(index);
//
//		if (index < MAX_QUEUE_SIZE)
//		{
//			Set_Char_From_Mod(modifier, tempDrawer.sym, tempDrawer.clr);
//			tempDrawer.timer.Start_Timer(0);		// First step de l'animation
//			tempDrawer.active = true;	// se fait à chaque fois pour rien
//
//			drawer[index] = tempDrawer;
//			total++;
//			return true;
//		}
//		else
//			return false;
//	}
//
//}
//
//static void Ev_Progress_Animation();
//static void Ev_Break_Animation();
//static void Dr_Er_Cursor(bool draw);
//
//static Event ev_ProgressAnimation(Ev_Progress_Animation, 6);	// pour faire afficher un ti progrès dans la bar
//static Event ev_BreakAnimation(Ev_Break_Animation, 1);	// Animation surt les points break
//static Event ev_ProgressBar(Ev_Progress_Bar);
//static Event ev_DrawWholeBar(Ev_Draw_Whole_Bar, 1);
//static Event ev_DrawWholeBarFast(Ev_Draw_Whole_Bar_Fast, 1);
//
//
//
//// got lazy here
//// Permet d'inscrire certains "break" dans la progress bar au endroit dans le spawn script ou une certaine longues pause à lieu. J'ai décidé de faire ça manuellement.
//// Cette décision m'oblige à updater continuellement les ce script autant que le spawn script si je souhaite une cohérence entre les deux. Heureusement ya pas grand chose à changer
//
//
//
//
//static float ratio;					// Nombre de wave à faire
//static float nextWave;				// La wave de l'event actuel
//static int waitForNxtSpawn;			// Pendant un break, Si le total de spawn dépasse ce montant, on progresse dans la bar et on stop le break
//
//// UI
//static const std::string tip[2] = { "  > "," <  " };
//static const int barLength = 70;	// Dimension de la bar
//static Coord crd;
//static Colors progClr;	// // Est jaune. Devient rouge durant le fianl hour
//
//static bool Is_Checkpoint_Here(int lvl, int waveTot)	// Check si un checkpoint  à lieu ici
//{
//	int const* pCHECKPOINT_LVL;	// le pointeurs vers les checkpoints de niveau
//
//	switch (lvl + 1)	// vraiment cave
//	{
//	case 1:pCHECKPOINT_LVL = LVL1_CHECKPOINT; break;
//	case 2:pCHECKPOINT_LVL = LVL2_CHECKPOINT; break;
//	case 3:pCHECKPOINT_LVL = LVL3_CHECKPOINT; break;
//	case 4:pCHECKPOINT_LVL = LVL4_CHECKPOINT; break;
//	default: return false;
//	}
//
//	for (int i = 0; i < NUM_CHECKPOINT[lvl]; i++)
//	{
//		if (waveTot == pCHECKPOINT_LVL[i])
//			return true;
//	}
//	return false;
//}
//
//static void Draw_tip(Coord crd, bool side)	// True = left false = right
//{
//	if (side)
//	{
//		//ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); crd.x++;
//		ConsoleRender::Add_String(tip[true], crd, BRIGHT_WHITE);
//	}
//	else
//	{
//		ConsoleRender::Add_String(tip[false], crd, BRIGHT_WHITE); crd.x +=(int)tip[false].distance();
//		//ConsoleRender::Add_Char(crd, TXT_CONST.DOT, BRIGHT_WHITE); 
//	}
//}
//
//
//void Ev_Draw_Whole_Bar_Fast()	// Happens first
//{
//	static int waveTot;
//	static float nextWave;
//	static float ratio;
//	static Colors baseClr;
//	static Coord coord;
//
//	if (!ev_DrawWholeBarFast.Is_Active())
//	{
//		waveTot = nextWave = 0;
//		ratio = (NUMWAVES[gCurrentLevel - 1]) / ((float)barLength);
//		baseClr = GRAY;
//		coord = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - (int)tip[true].distance() , map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
//		Draw_tip(coord, true); coord.x += (int)tip[true].distance();	//  left tip
//
//		ev_DrawWholeBarFast.Activate();
//		ev_DrawWholeBarFast.Start(0);
//		ev_DrawWholeBarFast.delay.Start_Timer(200000, NUMWAVES[gCurrentLevel - 1]);
//	}
//	else
//		while (ev_DrawWholeBarFast.delay.Tick())
//		{
//			if (FINALHOUR[gCurrentLevel - 1] == waveTot) // Check si on draw le finalhour ici
//			{
//				finalHour = coord;
//				ConsoleRender::Add_Char(coord, TXT_CONST.LINE_VER, LIGHT_RED); coord.x++;
//				baseClr = RED;
//				nextWave += ratio;
//			}
//			else
//				if (Is_Checkpoint_Here(gCurrentLevel - 1, waveTot)) // draw checkpoint
//				{
//					// Affiche le symbole du break
//					ConsoleRender::Add_Char(coord, '|', LIGHT_GREEN); coord.x++;
//					nextWave += ratio;
//				}
//				else
//					if ((int)nextWave == waveTot)	// On passe au prochain
//					{
//						if (nextWave >= gSpawnCycleTot)
//						{
//							ConsoleRender::Add_Char(coord, TXT_CONST.DOT, baseClr); coord.x++;
//						}
//						else
//						{
//							ConsoleRender::Add_Char(coord, TXT_CONST.DOT, progClr); coord.x++;
//						}
//
//						
//						nextWave += ratio;
//						// Start l'animation du prochain
//					}
//			waveTot++;
//		}
//
//	if (!ev_DrawWholeBarFast.delay.Is_On())
//	{
//		Draw_tip(coord, false);	// right tip, à la fin
//		ev_DrawWholeBarFast.Cancel();	// safety
//	}
//
//}
//
//
//
//static void Progress()
//{
//	nextWave += ratio;
//	Dr_Er_Cursor(false);	// delete le curseur précédant
//	crd.x++;	// avance d'une case :`D
//	if (ev_ProgressAnimation.Is_Active())
//	{
//		ev_ProgressAnimation.Cancel();								// lazy shit
//		ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.DOT, progClr);	// lazy shit
//	}
//}
//
//// pas de spawn sur les break? Pas de spawn sur les break!|
//// Signale au joueur combien de waves y reste avant la fin 
//void Ev_Progress_Bar()
//{
//	if (!ev_ProgressBar.Is_Active())
//	{
//		nextWave = 0;
//		ratio = NUMWAVES[gCurrentLevel - 1] / ((float)barLength);	// On se fie à cette valeur pour progresser dans la bar		
//		crd = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - 1, map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
//		progClr = LIGHT_YELLOW;
//
//		if (gSpawnCycleTot == 0)	// Version normal	
//			Ev_Draw_Whole_Bar();
//		else
//		{
//			Ev_Draw_Whole_Bar_Fast();	// Version checkpoint: Commence la progression plus loin sur la bar (à l'endroit ou le checkpoint est)
//
//			while (nextWave < gSpawnCycleTot)
//				Progress();
//		}
//
//
//		ev_ProgressBar.Activate();
//		ev_ProgressBar.Start(1000);
//		ev_ProgressBar.delay.Start_Timer(20000, 1, true);
//	}
//	else
//		while (ev_ProgressBar.delay.Tick())
//		{
//			if (gSpawnCycleTot == NUMWAVES[gCurrentLevel - 1])	// reached the end
//			{
//				ev_ProgressBar.Cancel();
//				return;
//			}
//
//			if (gSpawnCycleTot == FINALHOUR[gCurrentLevel - 1])
//			{
//				if (progClr != LIGHT_RED) // dumb condition, but understandable
//				{
//					Progress(); 
//					progClr = LIGHT_RED;	// it's serious time
//					Ev_Break_Animation();	// start l'animation du drette sur le FINALHOUR
//				}
//
//				continue;
//			}
//
//			// if final hour?
//			if (ev_BreakAnimation.Is_Active())	// Si l'animation de break est active
//			{
//				if (waitForNxtSpawn != gSpawnCycleTot)	// Faut attendre le prochain spawn
//				{
//					ev_BreakAnimation.Cancel();// Stop le break
//					Progress();	// Quand un break arrive, il faut avancer de 2 le ratio, sinon ça décale
//					Ev_Progress_Animation(); // progress
//				}
//			}
//			else
//				if (Is_Checkpoint_Here(gCurrentLevel - 1, gSpawnCycleTot))
//				{
//					waitForNxtSpawn = gSpawnCycleTot;
//					Progress();	// we progress
//					Ev_Break_Animation();	// start l'animation du break
//				}
//				else
//					if ((int)nextWave == gSpawnCycleTot)	// On passe au prochain
//					{
//						Progress(); // efface le curseur précédant et on avance
//						Ev_Progress_Animation();
//					}
//		}
//}
//
//
//void Ev_Progress_Animation()
//{
//	if (!ev_ProgressAnimation.Is_Active())
//	{
//		Dr_Er_Cursor(true);	// avance le curseur
//		ev_ProgressAnimation.Activate();
//		ev_ProgressAnimation.Start(7000);
//	}
//	else
//		while (ev_ProgressAnimation.delay.Tick())
//		{
//			switch (ev_ProgressAnimation.Get_Current_Step())
//			{
//
//			case 1:
//				// Début Animation de bar qui flash
//				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, WHITE);
//				ev_ProgressAnimation.Advance(8000);
//				break;
//
//			case 2:
//				ConsoleRender::Add_Char(crd, TXT_CONST.PLUS, BRIGHT_WHITE);
//				ev_ProgressAnimation.Advance(5000);
//				break;
//
//			case 3:// Flash la bar 
//				ConsoleRender::Add_Char(crd, 254, BRIGHT_WHITE);
//				ev_ProgressAnimation.Advance(5000);
//				break;
//
//			case 4:
//				ConsoleRender::Add_Char(crd, 219, LIGHT_RED);
//				ev_ProgressAnimation.Advance(6000);
//				break;
//
//			case 5:
//				ConsoleRender::Add_Char(crd, TXT_CONST.LINE_HOR, RED);
//				ev_ProgressAnimation.Advance(4000);
//				break;
//
//			case 6:
//				// Fin animation qui flash
//				ConsoleRender::Add_Char(crd, TXT_CONST.DOT, progClr);
//				ev_ProgressAnimation.Advance(0);
//				break;
//			}
//		}
}

