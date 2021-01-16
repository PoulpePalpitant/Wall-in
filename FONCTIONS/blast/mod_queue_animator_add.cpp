
#include "mod_queue_animator_add.h"


namespace DrawModifierQueue {
													
	DrawerQueue addNew = {};		// Queue d'animation pour l'ajout d'un élément dans la queue

	static const int baseSpd = 7000;// vitesse constante


	void UI_Dr_Add_New_Element()	// Fait apparaitre un élément de la liste de modifier queue à droite de l'écran. Chaque drawer correspond à une ligne
	{
		if (!addNew.total) return;	// Liste vide

		static Drawer* draw;	/// my pencil	
		static int X;				// facilite l'affichage
		static int Y;				// facilite l'affichage
		static int YIndex;			// Le combientième élément de la queue, sera affiché sur une certaine ligne
		static int toUpdate;			// nb d'animations à update durant ce cycle
		static int updated;				// nb d'animations updaté

		updated = 0;
		toUpdate = addNew.total;

		for (int index = 0; updated < toUpdate; index++)
		{
			if (!addNew.Is_Active(index))
				continue;	// passe au suivant

			draw = &addNew.drawer[index];

			while (draw->timer.Tick())
			{
				X = fakeTitleCrd.x + btwTitle;	//yep
				Y = fakeTitleCrd.y + yPos[index];	//xep

				// ANIMATION TIME
				switch (draw->currStep)
				{
				case 0:
					ConsoleRender::Add_Char({ X - btwTitle, Y }, 250, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle, Y }, 250, GRAY);
					draw->timer.Start_Timer(baseSpd);
					break;

				case 1:
					ConsoleRender::Add_Char({ X - btwTitle + 1, Y }, TXT_CONST.MINUS, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle - 1, Y }, TXT_CONST.MINUS, GRAY);
					draw->timer.Start_Timer(baseSpd + 2000);
					break;

				case 2:
					ConsoleRender::Add_Char({ X - btwTitle + 2, Y }, 196, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle - 2, Y }, 196, GRAY);
					ConsoleRender::Add_Char({ X - btwTitle, Y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle, Y }, TXT_CONST.SPACE);
					draw->timer.Start_Timer(baseSpd + 4000);
					break;

				case 3:
					ConsoleRender::Add_Char({ X - btwTitle + 3, Y }, 196, WHITE);
					ConsoleRender::Add_Char({ X + btwTitle - 3, Y }, 196, WHITE);
					ConsoleRender::Add_Char({ X - btwTitle + 1, Y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 1, Y }, TXT_CONST.SPACE);
					draw->timer.Start_Timer(baseSpd + 8000);
					break;

				case 4:
					if(!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, 250, GRAY);

					ConsoleRender::Add_Char({ X - btwTitle + 2, Y },TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 2, Y },TXT_CONST.SPACE);
					draw->timer.Start_Timer(baseSpd + 8000);
					break;

				case 5:
					if (!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, TXT_CONST.MINUS, WHITE);

					ConsoleRender::Add_Char({ X - btwTitle + 3, Y },TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 3, Y },TXT_CONST.SPACE);
					draw->timer.Start_Timer(baseSpd + 4000);
					break;

				case 6:
					if (!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, draw->sym, draw->clr);
					addNew.Remove(index);	// enleve le dernier
					//draw->timer.Start_Timer(baseSpd + 4000);
					break;

				//case 7:
				//	draw->timer.Start_Timer(baseSpd + 20000);
				//	break;
				//case 8:
				//	draw->timer.Start_Timer(baseSpd + 15000);
				//	break;
				//case 9:
				//	draw->timer.Start_Timer(baseSpd + 8000);
				//	break;
				//case 10:
				//	draw->timer.Start_Timer(baseSpd + 8000);
				//	break;
				//case 11:
				//	draw->timer.Start_Timer(baseSpd + 8000);
				//	break;
				//case 12:
				//	draw->timer.Start_Timer(baseSpd + 8000);
				//	break;
				//case 13:
				//	draw->timer.Start_Timer(baseSpd + 8000);				
				//	break;
				}

				draw->currStep++;

			}

			updated++;
		}

	}

}