
#include "mod_queue_animator_consume.h"


namespace DrawModifierQueue {
													
	DrawerQueue consume = {};		// Queue d'animation pour le swipe gauche-droite quand le premier élément est retiré

	static const int BASE_SPEED = 5000;

	void UI_Dr_Consume_First()
	{
		if (!consume.total) return;	

		static Drawer* draw;		
		static int X;				
		static int Y;				
		static int toUpdate;
		static int updated;			

		updated = 0;
		toUpdate = consume.total;

		for (int index = 0; updated < toUpdate; index++)
		{
			if (!consume.Is_Active(index))
				continue;

			draw = &consume.drawer[index];
			updated++;	

			while (draw->timer.Tick())
			{
				X = fakeTitleCrd.x + btwTitle;	//yep
				Y = fakeTitleCrd.y + yPos[0];	//xep

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
					draw->timer.Start_Timer(BASE_SPEED);
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
					consume.Remove(index);
					break;
				}
			}

		}

	}

}