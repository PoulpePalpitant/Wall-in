
#include "mod_queue_animator_consume.h"


namespace DrawModifierQueue {
													
	DrawerQueue consume = {};		// Queue d'animation pour le swipe gauche-droite quand le premier élément est retiré

	// 13
	static const int baseSpd = 5000;// vitesse constante

	void UI_Dr_Consume_First()
	{
		if (!consume.total) return;	// Liste vide

		static Drawer* draw;	/// my pencil	
		static int X;				// facilite l'affichage
		static int Y;				// facilite l'affichageS
		static int toUpdate;
		static int updated;				// nb d'animations updaté

		updated = 0;
		toUpdate = consume.total;

		if (toUpdate == 2)
			toUpdate;

		for (int index = 0; updated < toUpdate; index++)
		{
			if (!consume.Is_Active(index))
				continue;	// passe au suivant

			if (index > 3)
				continue;

			draw = &consume.drawer[index];

			while (draw->timer.Tick())
			{
				X = titleCrd.x + btwTitle;	//yep
				Y = titleCrd.y + yPos[0];	//xep

				// ANIMATION TIME
				switch (draw->currStep)
				{
				case 0:
					ConsoleRender::Add_Char({ X + 1, Y }, 219);
					ConsoleRender::Add_Char({ X + 2, Y }, 219);
					ConsoleRender::Add_Char({ X + 3, Y }, 219);
					ConsoleRender::Add_Char({ X + 4, Y }, 219);
					ConsoleRender::Add_Char({ X - 1, Y }, 219);
					ConsoleRender::Add_Char({ X - 2, Y }, 219);
					ConsoleRender::Add_Char({ X - 3, Y }, 219);
					ConsoleRender::Add_Char({ X - 4, Y }, 219);
					ConsoleRender::Add_Char({ X + 6,Y }, 250, LIGHT_RED);
					ConsoleRender::Add_Char({ X - 6,Y }, 250, LIGHT_RED);
					//ConsoleRender::Add_String(line, { titleCrd.x + 3, titleCrd.y + 4 }, LIGHT_RED);
					draw->timer.Start_Timer(baseSpd);
					draw->currStep++;
					break;

				case 1:
					ConsoleRender::Add_Char({ X + 1, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X + 2, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X + 3, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X + 4, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X - 1, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X - 2, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X - 3, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X - 4, Y }, TXT_CONST.SPACE, BLACK);
					ConsoleRender::Add_Char({ X + 6,Y }, 250, WHITE);
					ConsoleRender::Add_Char({ X - 6,Y }, 250, WHITE);
					//ConsoleRender::Add_String(line, { titleCrd.x + 3, titleCrd.y + 4 }, WHITE);
					consume.Remove(index);// fin
					break;
				}
			}
			updated++;	// updated

		}

	}

}