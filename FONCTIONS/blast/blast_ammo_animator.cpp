#include <math.h>
#include "blast_ammo_animator.h"
#include "../time/timerOP.h"

#include "../UI/map.h"
#include "../events/events.h"
#include "../events/global_events/feedback/ev_ammo_depleted.h"


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

	// TITLES
	std::string ammoTitle = "AMMO";


	Coord Get_Ori()		// Permet de trouver la coord d'origine d'où on va afficher la bar. Cette crd se fit elle même au coin HAUT_DROIT de la map. 
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

			// Draw pas la bar si ta pas d'ammo
			if (blastP1.Get_Ammo_Manager().Get_Nb_Ammo() == 0)
			{
				Dr_Or_Er_Bar(MAX_BAR_SIZE, WHITE, true);	// Met la bar vide SAFETY
				Dr_Bar_Tip(1);	// draw them tips
				//Dr_Bar_Tip(0);
				return;
			}

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
		static const float SPEED_MULTIPLIER = 2.5;	// durée de 3 secondes
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

			if (nbShots < 3)
				speed *= 10;

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
		if (length == 0 && !erase)
			Dr_Bar_Tip(false, GREEN, erase, false);	// bot tip
		else
		{
			for (int i = 1; i <= length; i++)
				Dr_Bar_Sym(i, clr, erase);

			if (length == MAX_BAR_SIZE)
			{
				Dr_Bar_Tip(true, clr, erase, true);	// top tip

				if (erase)
					Dr_Bar_Tip(false, WHITE, erase, false);	// efface le tip si on veut effacer la bar bot tip

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
		Coord crd = Get_Ori();
		Er_Ammo_Count(); // Erase le nombre précédant
		ConsoleRender::Add_String(std::to_string(count), { crd.x + barToCount ,crd.y }, clr, 0);	// draw par-dessus
	}

	void Er_Ammo_Count()
	{
		static std::string eraseNum = "   ";	// pour erase un nombre
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

	// Indicateur supplémentaire
	// *******************************************************
	void Dr_Ammo_Title(bool show)		// Le joueur tir, L'UI s'UPDATE
	{
		ConsoleRender::Add_String(ammoTitle, { (map.Get_Box_Limit(RIGHT) + 11),(map.Get_Box_Limit(UP) - 1) }, WHITE, TXT_SPD_DR, show);	// AMMO
	}



	// ACTIVATION DE L'UI POUR LES YEUX
	//******************************

	void Show_Ammo_UI(bool instant)
	{
		int ammo = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// Nombre de munitions du joueur
		Cancel_Ev_Ammo_Depleted();

		barLength = MAX_BAR_SIZE;	// Cette size pourrait être relative
		ratioBarPerAmmo = (ammo / (double)barLength);
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

		Dr_Ammo_Title(false);
		isShown = true;
	}
}