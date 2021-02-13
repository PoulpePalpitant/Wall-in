#include <math.h>
#include "blast_ammo_animator.h"
#include "../time/timerOP.h"

#include "../UI/map.h"
#include "../events/events.h"
#include "../events/global_events/feedback/ev_ammo_depleted.h"


namespace DrawBlastAmmo {

	static Event ev_DrFullBar(Ev_Dr_Bar_From_Scratch, MAX_BAR_SIZE);
	static Event ev_DrAmmoCountFromScratch(Ev_Dr_Ammo_Count_From_Scratch);
	static Event ev_DrAmmoGain(Ev_Dr_Ammo_Gain,100);

	bool isShown = false;		// si le player vois l'UI 
	bool erDozen = false;		// si on doit effacer la dizaine
	double ratioBarPerAmmo = 1;		// Nombre de munition pour chaque char de la bar 
	double nextAmmoEr = 1;			// Le nombre de munition à atteindre pour progresser dans la bar
	double nextAmmoDraw = 1;

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
		return { map.Get_Limit(RIGHT) + mapToBar, (map.Get_Limit(UP) - 1) };
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

			if (blastP1.Get_Ammo_Manager().Get_Nb_Emergency_Ammo() > 0)
			{
				Dr_Emergency_Ammo(1);
				Dr_Emergency_Ammo(2);
			}
			else
				Dr_Emergency_Ammo(blastP1.Get_Ammo_Manager().Get_Nb_Emergency_Ammo());

			// Draw pas la bar si ta pas d'ammo
			if (blastP1.Get_Ammo_Manager().Get_Nb_Ammo() == 0)
			{
				Dr_Or_Er_Bar(MAX_BAR_SIZE, WHITE, true);	// Met la bar vide SAFETY
				Dr_Bar_Tip(1, LIGHT_RED, 0, 0);
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

				if(blastP1.Get_Ammo_Manager().Get_Nb_Emergency_Ammo() > 0)
					if(barSize == barMax / 2)
						Dr_Emergency_Ammo(1);	// Affiche la première moitié de la bar

				if (barSize == barMax)
				{
					Dr_Or_Er_Bar(barSize, Get_Bar_Treshold_Color(barSize));	// last char

					toClear = MAX_BAR_SIZE - barMax;

					// fait juste clear le reste à cause d'un bug visuel. Lazy, met ça marche, pas
					for (int i = 0; i < toClear; i++)
						Dr_Bar_Sym(barMax + i, WHITE, true);

					if(blastP1.Get_Ammo_Manager().Get_Nb_Emergency_Ammo() > 0)
						Dr_Emergency_Ammo(2);	// Affiche la 2e tite bar au complet

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
		static const int fractions = 3;
		static int count, nbShots, speed;
		static float nxtCount, currCount;;
		static float countRatio;

		static float totTime/*, speed*/;

		if (!ev_DrAmmoCountFromScratch.Is_Active())
		{

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
		Dr_Ammo_Title(false);
		isShown = false;
	}

	void Update_Ammo_Count()	 // Réduit de 1 le nombre d'ammo
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

		if (ammo <= round(nextAmmoEr) || nextAmmoEr < 0)	// UPDATE la bar
		{
			if (!ev_DrFullBar.Is_Active())
			{
				Dr_Bar_Sym(barLength, WHITE, true);	// Réduit la longueur de la bar

				if (barLength == MAX_BAR_SIZE)
					Dr_Bar_Tip(true, WHITE, 0, 0);	// déconnect le petit char du tip
				
				if(barLength > 0)
					barLength--;

				if (Upd_Bar_Progression_Color())
					Dr_Or_Er_Bar(barLength, barProgClr);	// Recolorie la bar au complet


				if (ammo == 0) //draw le top tips en rouges. Efface l'autre
				{
					Dr_Bar_Tip(1, LIGHT_RED, 0, 0);
					Dr_Bar_Tip(0, WHITE, 1, 0);	
				}
			}
			else
				barLength--;


			nextAmmoDraw = ammo +  ratioBarPerAmmo; 
			
			if (nextAmmoEr > 0)
			{
				nextAmmoEr -= ratioBarPerAmmo;
				
				if (!(nextAmmoEr < 0 && ammo > 0))
					Dr_Bar_Remove();	// On le refait une deuxième fois, car il se peut que l'on doit erase 2 fois la bar si le nombre de tir est plus petit que la bar
			}
		}
	}

	// UPDATE L'UI INSTANTANNÉMENT DÈS QUE LE JOUEUR TIR DU GUN
	// *******************************************************
	void Dr_Ammo_Used()		// Le joueur tir, L'UI s'UPDATE
	{
		Dr_Bar_Remove();	 // Réduit pt la longueur de la bar
		Update_Ammo_Count();	 // Réduit de 1 le nombre d'ammo
	}

	// Indicateur supplémentaire
	// *************************
	void Dr_Ammo_Title(bool show)		// Le joueur tir, L'UI s'UPDATE
	{
		int ammoCount = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();

		if (show)
		{
			if (ammoCount < 100)
				ConsoleRender::Add_String(ammoTitle, { (map.Get_Limit(RIGHT) + 11),(map.Get_Limit(UP) - 1) }, WHITE, TXT_SPD_DR);	// AMMO
			else
			{
				ConsoleRender::Add_String("       ", { (map.Get_Limit(RIGHT) + 11),(map.Get_Limit(UP) - 1) }, WHITE, TXT_SPD_DR);	
				ConsoleRender::Add_String(ammoTitle, { (map.Get_Limit(RIGHT) + 12),(map.Get_Limit(UP) - 1) }, WHITE, TXT_SPD_DR);	// AMMO
			}
		}
		else
			ConsoleRender::Add_String("       ", { (map.Get_Limit(RIGHT) + 10),(map.Get_Limit(UP) - 1) }, WHITE, 0, 1);	// AMMO

	}


	// EMERGENCY AMMO
	// **************

	void Dr_Emergency_Ammo(int ammo)
	{
		
		Coord ori = Get_Ori();	// Le point d'origine de la bar
		ori.x += 3;

		Colors clr = WHITE;


		if (ammo == 2)
		{
			// Ammo 1
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 11 }, tip[2], WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 10 }, barSym, WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 9 },  barSym, WHITE);
		}
		if (ammo == 1)
		{
			// Efface L'autre Ammo
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 11 }, tip[1], WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 10 }, TXT_CONST.SPACE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 9 }, TXT_CONST.SPACE);

			// Ammo 2
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 8 }, barSym, WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 7 }, barSym, WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 6 }, 193, WHITE);
			clr = LIGHT_YELLOW;
		}

		if (ammo == 0)
		{
			// Efface L'autre Ammo
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 10 }, TXT_CONST.SPACE, WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 9 }, TXT_CONST.SPACE, WHITE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 8 },  TXT_CONST.SPACE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 7 },  TXT_CONST.SPACE);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 11 }, tip[1], LIGHT_RED);
			ConsoleRender::Add_Char({ ori.x ,ori.y + MAX_BAR_SIZE + 1 - 6 }, tip[1], LIGHT_RED);
			clr = LIGHT_RED;
		}

		ConsoleRender::Add_Char({ ori.x + 2,ori.y + MAX_BAR_SIZE + 1 - 9 }, TXT_CONST.PLUS, WHITE);
		ConsoleRender::Add_String(std::to_string(ammo), { ori.x + 4  ,ori.y + MAX_BAR_SIZE + 1 - 9 }, clr);	// 

	}


	// Un ajout!
	//**********

	void Dr_Ammo_Gain()
	{
		int ammo = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// Nombre de munitions du joueur

		if (ev_DrAmmoGain.Is_Active())
			ev_DrAmmoGain.Cancel(); // Stop l'animation
		Ev_Dr_Ammo_Gain();

		// Si la bar à atteint son max, faut adapté le ratio
		if (barLength == MAX_BAR_SIZE)
		{
			ratioBarPerAmmo = ammo / (float)MAX_BAR_SIZE  ;
			ammoMaxTresholdClr = ammo - 1;
			nextAmmoEr = ammo - ratioBarPerAmmo;
		}
		else
			if (ammo >= round(nextAmmoDraw))
			{
				//Dr_Or_Er_Bar(barLength, Get_Bar_Treshold_Color(barLength));	// last char

				if (!ev_DrFullBar.Is_Active())
				{
					barLength++;
					
					Dr_Bar_Sym(barLength, Get_Bar_Treshold_Color(barLength));	// Allonge la bar

					if (barLength == MAX_BAR_SIZE)
						Dr_Bar_Tip(1, BRIGHT_WHITE, 0, 1);	// reconnect le ptit tip
					

					if (Upd_Bar_Progression_Color())
						Dr_Or_Er_Bar(barLength, barProgClr);	// Recolorie la bar au complet

					if (ammo == 1) // redraw le vieux tip
						Dr_Bar_Tip(0);
				}
				else
					barLength++;

				nextAmmoDraw += ratioBarPerAmmo;
				nextAmmoEr = ammo - ratioBarPerAmmo;

				Dr_Ammo_Gain();
			}
	}


	// ACTIVATION DE L'UI POUR LES YEUX
	//******************************

	void Show_Ammo_UI(bool instant)
	{
		int ammo = blastP1.Get_Ammo_Manager().Get_Nb_Ammo();	// Nombre de munitions du joueur
		
		if (Is_Ev_Ammo_Depleted_Active())
			Cancel_Ev_Ammo_Depleted();


		barLength = !ammo ? 0 : MAX_BAR_SIZE;
		ammoMaxTresholdClr = !ammo ? MAX_BAR_SIZE : ammo;
		ratioBarPerAmmo = !ammo ? 1 : (ammo / (double)MAX_BAR_SIZE);

		nextAmmoEr = ammo - ratioBarPerAmmo;
		nextAmmoDraw = ammo + ratioBarPerAmmo;


		if (instant)
		{
			Dr_Or_Er_Bar(MAX_BAR_SIZE, LIGHT_GREEN);
			Dr_Ammo_Count(ammo, LIGHT_GREEN);
		}
		else
		{

			Ev_Dr_Bar_From_Scratch();				 // Draw la bar au complet
			Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de manière progressive

		}

		Dr_Ammo_Title(true);
		isShown = true;
	}





	void Ev_Dr_Ammo_Gain()		 // Affiche le coueur à ses différents stades
	{
		static Coord  xy;
		static int speed = 150000;

		if (!ev_DrAmmoGain.Is_Active())
		{
			xy = Get_Ori();
			xy.x += barToCount - 1;
		
			ev_DrAmmoGain.Activate();
			ev_DrAmmoGain.Start(0);
			ev_DrAmmoGain.delay.Start_Timer(speed, 3);	
		}
		else
			while (ev_DrAmmoGain.delay.Tick())
			{
				switch (ev_DrAmmoGain.Get_Current_Step())
				{
				case 1:
					ConsoleRender::Add_Char(xy, COOL_CHARS[rand() % NUM_COOL_CHARS], LIGHT_GREEN);
					xy.x++;
					ev_DrAmmoGain.Advance(0);
					break;

				case 2: 
					xy.x-= 4;
					ConsoleRender::Add_Char(xy, TXT_CONST.SPACE);
					ev_DrAmmoGain.Advance(0);
					ev_DrAmmoGain.delay.Stop();
					ev_DrAmmoGain.delay.Start_Timer(50000, 2);
					break;

				case 3: 
					xy.x++;
					ConsoleRender::Add_Char(xy, TXT_CONST.SPACE);
					ev_DrAmmoGain.Advance(0);
					break;

				case 4: 
					Dr_Ammo_Count(blastP1.Get_Ammo_Manager().Get_Nb_Ammo(), ammoProgClr);
					break;
				}
			}
	}


}
