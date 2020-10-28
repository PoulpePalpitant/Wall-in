#include "blast_ammo_animator.h"
#include "../time/timerOP.h"
#include <math.h>

#include "../UI/map.h"
#include "../events/events.h"

namespace DrawBlastAmmo {

	static Event ev_DrFullBar(Ev_Dr_Bar_From_Scratch, MAX_BAR_SIZE);
	static Event ev_DrAmmoCountFromScratch(Ev_Dr_Ammo_Count_From_Scratch);

	bool isShown = false;		// si le player vois l'UI 
	bool erDozen = false;		// si on doit effacer la dizaine
	double ratioBarPerAmmo = 1;			// Nombre de munition pour chaque char de la bar 
	double nextAmmoEr = 1;			// Le nombre de munition à atteindre pour progresser dans la bar

	//	UI
	Colors barProgClr = BRIGHT_WHITE;				// Couleur des chars de la bar -> blanc -> jaune -> rouge	selon la progression
	Colors ammoProgClr = LIGHT_GREEN;				// Couleur du nombre d'ammo
	int ammoMaxTresholdClr = 0;

	// XYZ
	Distance btwTitle = 4;		// Distance entre le titre de la queue et la limite gauche à droite. On va slide les charactère à gauche et à droite. 
	Distance mapToBar = 5;			// Distance entre la bordure de la map et la bar
	Distance barToCount = 3;		// Distance entre la bar et le nombre représentant l'ammo count
	int barLength = MAX_BAR_SIZE;	// Dimension de la bar actuelle


	static Coord Get_Ori()		// Permet de trouver la coord d'origine d'où on va afficher la bar. Cette crd se fit elle même au coin HAUT_DROIT de la map. 
	{
		return { map.Get_Box_Limit(RIGHT) + mapToBar, (map.Get_Box_Limit(UP) - 1) };
	}


	// Détermine la couleur de la bar selon le pourcentage d'ammo utilisé
	// ----------------------------------------------

	Colors Get_Bar_Treshold_Color(int barLength)	// Retourne la couleur que la bar aurait selon une longueur
	{
		static Colors clr;
		static float tresholds[2];
		tresholds[0] = MAX_BAR_SIZE * prcentBarClrTresh[0];
		tresholds[1] = MAX_BAR_SIZE * prcentBarClrTresh[1];

		if (barLength > tresholds[0])
			clr = barTreshClr[0];
		else
			if (barLength > tresholds[1])
				clr = barTreshClr[1];
			else
				clr = barTreshClr[2];
		return clr;
	}

	// Change la couleur de la bar selon le pourcentage d'ammo utilisé
	static bool Upd_Bar_Progression_Color()
	{
		Colors clr = Get_Bar_Treshold_Color(barLength);

		if (barProgClr != clr)
		{
			barProgClr = clr;
			return true;
		}
		else
			return false;
	}

	Colors Get_Ammo_Treshold_Color(int currAmmo)	// Retourne la couleur que le compteur d'ammo aurait selon le nombre de tir fait
	{
		static Colors clr;
		static float tresholds[2];
		tresholds[0] = ammoMaxTresholdClr * prcentAmmoClrTresh[0];
		tresholds[1] = ammoMaxTresholdClr * prcentAmmoClrTresh[1];

		if (currAmmo > ammoMaxTresholdClr)
			clr = ammoTreshClr[0];
		else
			if (currAmmo > tresholds[0])
				clr = ammoTreshClr[1];
			else
				if (currAmmo > tresholds[1])
					clr = ammoTreshClr[2];
				else
					clr = ammoTreshClr[3];
		return clr;
	}

	// Change la couleur du compteur selon le pourcentage d'ammo utilisé
	static bool Upd_Ammo_Progression_Color()
	{
		Colors clr = Get_Ammo_Treshold_Color(blastP1.Get_Ammo_Manager().Get_Nb_Ammo());

		if (ammoProgClr != clr)
		{
			ammoProgClr = clr;
			return true;
		}
		else
			return false;
	}

	// Affiche la bar au complet pour la première foi
	// **********************************************

	void Ev_Dr_Bar_From_Scratch()
	{
		static int barSize;
		static int barMax;
		static int toClear; 

		if (!ev_DrFullBar.Is_Active())
		{
			barSize = 0;
			barMax = MAX_BAR_SIZE;

			Dr_Bar_Tip(1);	// draw them tips
			Dr_Bar_Tip(0);

			ev_DrFullBar.Activate();
			ev_DrFullBar.Start(0);
			ev_DrFullBar.delay.Start_Timer(20000, 1, true);
		}
		else
		{
			while (ev_DrFullBar.delay.Tick())
			{
				Dr_Or_Er_Bar(barSize, Get_Bar_Treshold_Color(barSize));
				
				if (barLength < barMax)
					barMax = barLength;
				else
					barSize++;

				if (barSize == barMax)
				{
					Dr_Or_Er_Bar(barSize, Get_Bar_Treshold_Color(barSize));	// last char

					toClear = MAX_BAR_SIZE - barMax;

					// fait juste clear le reste à cause d'un bug visuel. Lazy, met ça marche, pas
					for (int i = 0; i < toClear; i++)
						Dr_Bar_Sym(barMax + i, WHITE, true);
						

					ev_DrFullBar.Cancel();
				}
				// si ça dépasse faudrait effacer les résidus

			}
		}
	}

	// Affiche le compte des munitions pour la première fois
 // ********************************************************

	void Ev_Dr_Ammo_Count_From_Scratch()		 // Affiche le nombre d'ammo de manière progressive
	{
		static const int DURATION = 3000;	// durée de 3 secondes
		static const float SPEED_MULTIPLIER = 1.5;	// durée de 3 secondes
		static const float fractionsSpeed[] = { 2 / 3.f, 1 / 3.f, 1 / 6.f };	// vitesse relative à la progression
		static const float fractionsSpeed2[] = { 1 / 2.f, 1 / 4.f, 3 / 16.f, 1 / 16.f };	// vitesse relative à la progression
		static const int fractions = 3;
		static int count, nbShots, speed;
		static float nxtCount, currCount;;
		static float countRatio;

		static float totTime/*, speed*/;

		if (!ev_DrAmmoCountFromScratch.Is_Active())
		{
			//countRatio = DURATION / nbShots;
			//currCount = DURATION;
			//nxtCount = currCount -= countRatio;

			count = 0;
			totTime = 0;	// temps à incrémenter
			nbShots = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();
			speed = int(nbShots * (1000 * SPEED_MULTIPLIER) / 3);
			ev_DrAmmoCountFromScratch.Activate();
			ev_DrAmmoCountFromScratch.Start(0);
			ev_DrAmmoCountFromScratch.delay.Start_Timer(speed, 1, true);
		}
		else
		{
			totTime += GameLoopClock::Get_Delta_Time();
			// speed 
			// duration = 3 seconde

			// 1 première seconde tu fais le 2 tier
			// 1 prochaine tu fais le quart
			// 1 dernière tu fais le reste

			//if(ev_DrAmmoCountFromScratch.delay.Get_Time_Left() < )
			while (ev_DrAmmoCountFromScratch.delay.Tick())
			{
				nbShots = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// si le joueur tir pendant l'event, faut réduire ça!

				//v2 
				Dr_Ammo_Count(count, Get_Ammo_Treshold_Color(count));

				count++;
				if (count == (int)(nbShots * fractionsSpeed[0]))
					ev_DrAmmoCountFromScratch.delay.Start_Timer((int)(nbShots * fractionsSpeed[1] * (1000 * SPEED_MULTIPLIER)), 1, true);	// Vitesse pour le quart du total
				else
					if (count == (int)(nbShots * fractionsSpeed[0]) + (int)(nbShots * fractionsSpeed[1]))
						ev_DrAmmoCountFromScratch.delay.Start_Timer(nbShots * (int)(fractionsSpeed[2] * (1000 * SPEED_MULTIPLIER)), 1, true);
					else
						if (count > nbShots)
							ev_DrAmmoCountFromScratch.Cancel();
						//else
						//	if (count == nbShots - 3)
						//		ev_DrAmmoCountFromScratch.delay.Start_Timer(3000, 1, true);
			}
		}
	}

	// AFFICHAGES INSTANTANNÉE DE L'UI
	// *******************************

	void Dr_Or_Er_Bar(int length, Colors clr, bool erase) // Affiche la bar, selon une couleur
	{
		if (length == 0)
			Dr_Bar_Tip(false, GREEN, erase, false);	// bot tip
		else
		{
			for (int i = 1; i <= length; i++)
				Dr_Bar_Sym(i, clr, erase);

			if (length == MAX_BAR_SIZE)
			{
				Dr_Bar_Tip(true, clr, erase, true);	// top tip
			}
		}
	}

	void Dr_Bar_Tip(bool topTip, Colors clr, bool erase, bool connected) // Affiche l'une des 2 extrémités. False = botTip
	{
		static Coord crd;  crd = Get_Ori();	// Le point d'origine de la bar
		static char sym;

		if (erase)
			sym = TXT_CONST.SPACE;
		else
			sym = tip[topTip + connected];

		if (!topTip)
			crd.y = crd.y + MAX_BAR_SIZE + 1;	// 1, pour le tips

		ConsoleRender::Add_Char(crd, sym, clr);	// Tippidy tip
	}

	void Dr_Bar_Sym(int distance, Colors clr, bool erase) // Affiche 1 char de la bar. Point d'origine est en haut drette sur le tip
	{
		static Coord ori; ori = Get_Ori();	// Le point d'origine de la bar
		static char sym;

		if (erase)
			sym = TXT_CONST.SPACE;
		else
			sym = barSym;

		ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - distance }, sym, clr);	// +1 pour dépasser le point d'origine
	}


	void Dr_Ammo_Count(int count, Colors clr)				// Le nombre
	{
		static Coord crd = Get_Ori();

		Er_Ammo_Count(); // Erase le nombre précédant
		ConsoleRender::Add_String(std::to_string(count), { crd.x + barToCount ,crd.y }, clr, 0);	// draw par-dessus
	}

	void Er_Ammo_Count()
	{
		static std::string eraseNum = "    ";	// pour erase un nombre
		static Coord crd = Get_Ori();
		ConsoleRender::Add_String(eraseNum, { crd.x + barToCount ,crd.y });	// Erase le nombre 
	}
	void Hide_Ammo_UI() // Efface l'ui instantannément
	{
		Dr_Or_Er_Bar(MAX_BAR_SIZE, WHITE, true);
		isShown = false;
	}

	void Dr_Ammo_Remove()	 // Réduit de 1 le nombre d'ammo
	{
		if (!ev_DrAmmoCountFromScratch.Is_Active())
		{
			Upd_Ammo_Progression_Color();
			Dr_Ammo_Count(blastP1.Get_Ammo_Manager().Get_Nb_Ammo(), ammoProgClr);
		}
	}

	void Dr_Bar_Remove()	 // Réduit la bar selon le ratio
	{
		int ammo = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// Nombre de munitions du joueur

		if (ammo <= round(nextAmmoEr))	// UPDATE la bar
		{
			if (!ev_DrFullBar.Is_Active())
			{
				Dr_Bar_Sym(barLength, WHITE, true);	// Réduit la longueur de la bar

				if (barLength == MAX_BAR_SIZE)
					Dr_Bar_Tip(true, WHITE, 0, 0);	// déconnect le petit char du tip

				barLength--;

				if (Upd_Bar_Progression_Color())
					Dr_Or_Er_Bar(barLength, barProgClr);	// Recolorie la bar au complet
			}
			else
				barLength--;

			nextAmmoEr -= ratioBarPerAmmo;	// ammo ne sera jamais négatif
			Dr_Bar_Remove();	// On le refait une deuxième fois, car il se peut que l'on doit erase 2 fois la bar si le nombre de tir est plus petit que la bar
		}
	}


	// UPDATE L'UI INSTANTANNÉMENT DÈS QUE LE JOUEUR TIR DU GUN
	// *******************************************************
	void Dr_Ammo_Used()		// Le joueur tir, L'UI s'UPDATE
	{
		Dr_Bar_Remove();	 // Réduit pt la longueur de la bar
		Dr_Ammo_Remove();	 // Réduit de 1 le nombre d'ammo
	}


	// ACTIVATION DE L'UI POUR LES YEUX
	//******************************

	void Show_Ammo_UI(bool instant)
	{
		int ammo = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// Nombre de munitions du joueur


		barLength = MAX_BAR_SIZE;	// Cette size pourrait être relative
		ratioBarPerAmmo = (ammo / (double)barLength  );
		nextAmmoEr = ammo - ratioBarPerAmmo;
		ammoMaxTresholdClr = ammo;

		if (instant)
		{
			Dr_Or_Er_Bar(barLength, LIGHT_GREEN);
			Dr_Ammo_Count(ammo, LIGHT_GREEN);
		}
		else
		{

			Ev_Dr_Bar_From_Scratch();				 // Draw la bar au complet
			Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de manière progressive

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
	//static float ratioBarPerAmmo;					// Nombre de wave à faire
	//static float nextWave;				// La wave de l'event actuel
	//static int waitForNxtSpawn;			// Pendant un break, Si le total de spawn dépasse ce montant, on progresse dans la bar et on stop le break
	//
	//// UI
	//static const std::string tip[2] = { "  > "," <  " };
	//static const int barLength = 70;	// Dimension de la bar
	//static Coord crd;
	//static Colors barProgClr;	// // Est jaune. Devient rouge durant le fianl hour
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
	//	static float ratioBarPerAmmo;
	//	static Colors baseClr;
	//	static Coord coord;
	//
	//	if (!ev_DrawWholeBarFast.Is_Active())
	//	{
	//		waveTot = nextWave = 0;
	//		ratioBarPerAmmo = (NUMWAVES[gCurrentLevel - 1]) / ((float)barLength);
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
	//				nextWave += ratioBarPerAmmo;
	//			}
	//			else
	//				if (Is_Checkpoint_Here(gCurrentLevel - 1, waveTot)) // draw checkpoint
	//				{
	//					// Affiche le symbole du break
	//					ConsoleRender::Add_Char(coord, '|', LIGHT_GREEN); coord.x++;
	//					nextWave += ratioBarPerAmmo;
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
	//							ConsoleRender::Add_Char(coord, TXT_CONST.DOT, barProgClr); coord.x++;
	//						}
	//
	//						
	//						nextWave += ratioBarPerAmmo;
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
	//	nextWave += ratioBarPerAmmo;
	//	Dr_Er_Cursor(false);	// delete le curseur précédant
	//	crd.x++;	// avance d'une case :`D
	//	if (ev_ProgressAnimation.Is_Active())
	//	{
	//		ev_ProgressAnimation.Cancel();								// lazy shit
	//		ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.DOT, barProgClr);	// lazy shit
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
	//		ratioBarPerAmmo = NUMWAVES[gCurrentLevel - 1] / ((float)barLength);	// On se fie à cette valeur pour progresser dans la bar		
	//		crd = { map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - (barLength / 2) - 1, map.Get_Box_Limit(UP) - 4 };	// pos de départ ouch
	//		barProgClr = LIGHT_YELLOW;
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
	//				if (barProgClr != LIGHT_RED) // dumb condition, but understandable
	//				{
	//					Progress(); 
	//					barProgClr = LIGHT_RED;	// it's serious time
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
	//					Progress();	// Quand un break arrive, il faut avancer de 2 le ratioBarPerAmmo, sinon ça décale
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
	//				ConsoleRender::Add_Char(crd, TXT_CONST.DOT, barProgClr);
	//				ev_ProgressAnimation.Advance(0);
	//				break;
	//			}
	//		}
	//}

}