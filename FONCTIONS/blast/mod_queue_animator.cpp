
#include "mod_queue_animator.h"
#include "mod_queue_animator_add.h"
#include "mod_queue_animator_consume.h"
#include "../UI/map.h"
#include "../items/items.h"

namespace DrawModifierQueue {

	bool isShown = false;			

	std::string queueTitle = "NEXT SHOT TYPE";
	static std::string excess = ". . .";
	std::string line = { (char)242,(char)242,(char)242};
	
	Coord fakeTitleCrd = {};	
	Coord realTitleCrd = {};	// don't try to understand
	
	Distance btwTitle = 4;		
	int yPos[MAX_QUEUE_SIZE] = { 3, 7 ,9 ,11 ,13 };		// La ligne on va s'afficher chaque élément de la queue


	void Set_Mod_Queue_Pos()
	{
		fakeTitleCrd.x = map.Get_Limit(LEFT) - 20;

		if (map.Get_Height() <= 13)
			fakeTitleCrd.y = map.Get_Limit(UP);
		else
			fakeTitleCrd.y = map.Get_Limit(UP) + map.Get_Height() / 4;

		realTitleCrd.y = fakeTitleCrd.y;
		realTitleCrd.x = fakeTitleCrd.x - 3;
	}

	void Show_Queue_UI()
	{
		ConsoleRender::Add_String(queueTitle, realTitleCrd, WHITE, TXT_SPD_FAST);
		ConsoleRender::Add_String(line, { fakeTitleCrd.x + 3, fakeTitleCrd.y + 4 });
		isShown = true;	
	}
	void Hide_Queue_UI()
	{
		std::string eraser = "               ";
		ConsoleRender::Add_String(queueTitle, realTitleCrd, WHITE, 0, true);

		// Efface les deux tits points sur les côtés
		ConsoleRender::Add_Char({ fakeTitleCrd.x - 2,fakeTitleCrd.y + 3 }, TXT_CONST.SPACE);
		ConsoleRender::Add_Char({ fakeTitleCrd.x + 10,fakeTitleCrd.y + 3 }, TXT_CONST.SPACE);

		// Not time for this shit anymore
		for (int i = 0; i < 15; i++)
			ConsoleRender::Add_String(eraser, { fakeTitleCrd.x - 5,fakeTitleCrd.y + i });

		Hide_Excess();	
		isShown = false;
	}

	void Show_Queue_No_Ammo_UI() {
		ConsoleRender::Add_String(queueTitle, realTitleCrd, WHITE, 0, true);
	}


	void Show_Excess() // Les trois tits points qui apparaissent pour signaler qu'il y a plus que 5 éléments dans la queue
	{
		ConsoleRender::Add_String(excess, { fakeTitleCrd.x + 2,fakeTitleCrd.y + yPos[MAX_QUEUE_SIZE - 1] +3 }, WHITE);
	}
	void Hide_Excess()
	{
		ConsoleRender::Add_String(excess, { fakeTitleCrd.x + 2,fakeTitleCrd.y + yPos[MAX_QUEUE_SIZE - 1] + 3 }, WHITE, 0,  true);
	}

	void Reorder_Rest_Of_Queue()	// Les prochains éléments avancent d'une coche
	{
		int mod;
		unsigned char sym;
		Colors clr;
		Coord crd = { fakeTitleCrd.x + btwTitle, fakeTitleCrd.y };
		int size = BlastModifierQueue::What_Is_Size();	

		if (size > MAX_QUEUE_SIZE)
			size = MAX_QUEUE_SIZE;	

		for (int line = 1; line <= size; line++)
		{
			BlastModifierQueue::queue.Get_Nth_Element(line, mod);
			Set_Char_From_Mod((Modifier)mod, sym, clr);
			ConsoleRender::Add_Char({ crd.x, crd.y + yPos[line - 1] }, sym, clr);			
		}

		if (size < MAX_QUEUE_SIZE)	
		{
			crd.y += yPos[size];
			ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		}
	}


	void Set_Char_From_Mod(Modifier mod, unsigned char& sym, Colors& clr)
	{
		switch (mod)
		{
		case Modifier::REGULAR:		break;
		case Modifier::BUFFER:		sym = 254;	clr = LIGHT_YELLOW;	 break;
		case Modifier::BLOCKER:		sym = 158; 	clr = LIGHT_RED;	 break;
		case Modifier::CORRUPTER:	sym = 207;	clr = LIGHT_PURPLE;	 break;
		case Modifier::ENERGIZER:	sym = 176;	clr = LIGHT_PURPLE;	 break;
		case Modifier::COLOR_B: 	sym = 176;	clr = LIGHT_AQUA;	 break;
		case Modifier::BLIND_COLOR:	sym = 176;	clr = BRIGHT_WHITE;	 break;
		}
	}

	void Update_Modifier_Queue()
	{
		UI_Dr_Add_New_Element();
		UI_Dr_Consume_First();
	}

	bool DrawerQueue::Is_Active(int index)
	{
		if (index > MAX_QUEUE_SIZE - 1)
			return false;
		else
			 return drawer[index].active; 
	}

	void DrawerQueue::Remove(int index)	// On delete rien au final
	{
		drawer[index].active = false;
		total--;
	}
	void DrawerQueue::Remove_All()
	{
		for (int i = 0; i < MAX_QUEUE_SIZE; i++)
			drawer[i].active = false;
		total = 0;
	}

	void DrawerQueue::Cancel()	
	{
		for (int index = 0; index < MAX_QUEUE_SIZE; index++)
			drawer[index].cancel = true;
		
	}
	bool DrawerQueue::Add_To_Next_Available(Modifier modifier)	
	{
		if (total < MAX_QUEUE_SIZE)
		{
			for (int index = 0; index < MAX_QUEUE_SIZE; index++)
			{
				if (drawer[index].active == false)
				{
					Set_Char_From_Mod(modifier, drawer[index].sym, drawer[index].clr);
					drawer[index].timer.Start_Timer(0);		
					drawer[index].currStep = 0;
					drawer[index].cancel = false;
					drawer[index].active = true;	

					total++;
					return true;
				}
			}
		}
		
		return false;

	}


	bool DrawerQueue::Add_To_Index(Modifier modifier, int index)		
	{

		if (Is_Active(index))	
			Remove(index);

		if (index < MAX_QUEUE_SIZE)
		{
			Set_Char_From_Mod(modifier, drawer[index].sym, drawer[index].clr);
			drawer[index].timer.Start_Timer(0);		
			drawer[index].active = true;	
			drawer[index].cancel = false;
			drawer[index].currStep = 0;

			total++;
			return true;
		}
		else
			return false;
	}

}