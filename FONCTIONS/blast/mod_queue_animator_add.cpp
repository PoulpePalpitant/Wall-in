
#include "mod_queue_animator_add.h"


namespace DrawModifierQueue {
													
	DrawerQueue addNew = {};	

	static const int BASE_SPEED = 7000;


	void UI_Dr_Add_New_Element()	// Fait apparaitre un élément de la liste de modifier queue 
	{
		if (!addNew.total) return;	

		static Drawer* draw;	
		static int X;			
		static int Y;			
		static int YIndex;		
		static int toUpdate;	
		static int updated;		

		updated = 0;
		toUpdate = addNew.total;

		for (int index = 0; updated < toUpdate; index++)
		{
			if (!addNew.Is_Active(index))
				continue;	

			draw = &addNew.drawer[index];

			while (draw->timer.Tick())
			{
				X = fakeTitleCrd.x + btwTitle;		
				Y = fakeTitleCrd.y + yPos[index];	

				// ANIMATION TIME
				switch (draw->currStep)
				{
				case 0:
					ConsoleRender::Add_Char({ X - btwTitle, Y }, 250, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle, Y }, 250, GRAY);
					draw->timer.Start_Timer(BASE_SPEED);
					break;

				case 1:
					ConsoleRender::Add_Char({ X - btwTitle + 1, Y }, TXT_CONST.MINUS, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle - 1, Y }, TXT_CONST.MINUS, GRAY);
					draw->timer.Start_Timer(BASE_SPEED + 2000);
					break;

				case 2:
					ConsoleRender::Add_Char({ X - btwTitle + 2, Y }, 196, GRAY);
					ConsoleRender::Add_Char({ X + btwTitle - 2, Y }, 196, GRAY);
					ConsoleRender::Add_Char({ X - btwTitle, Y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle, Y }, TXT_CONST.SPACE);
					draw->timer.Start_Timer(BASE_SPEED + 4000);
					break;

				case 3:
					ConsoleRender::Add_Char({ X - btwTitle + 3, Y }, 196, WHITE);
					ConsoleRender::Add_Char({ X + btwTitle - 3, Y }, 196, WHITE);
					ConsoleRender::Add_Char({ X - btwTitle + 1, Y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 1, Y }, TXT_CONST.SPACE);
					draw->timer.Start_Timer(BASE_SPEED + 8000);
					break;

				case 4:
					if(!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, 250, GRAY);

					ConsoleRender::Add_Char({ X - btwTitle + 2, Y },TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 2, Y },TXT_CONST.SPACE);
					draw->timer.Start_Timer(BASE_SPEED + 8000);
					break;

				case 5:
					if (!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, TXT_CONST.MINUS, WHITE);

					ConsoleRender::Add_Char({ X - btwTitle + 3, Y },TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + btwTitle - 3, Y },TXT_CONST.SPACE);
					draw->timer.Start_Timer(BASE_SPEED + 4000);
					break;

				case 6:
					if (!draw->cancel)
						ConsoleRender::Add_Char({ X , Y }, draw->sym, draw->clr);
					addNew.Remove(index);	
					break;
				}

				draw->currStep++;

			}

			updated++;
		}

	}

}