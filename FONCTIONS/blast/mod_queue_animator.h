#pragma once

#include "blast_modifier_queue.h"

namespace DrawModifierQueue {

	const int  MAX_QUEUE_SIZE = 5;

	extern bool isShown;		

	// Bunche of stuff pour les animations
	extern std::string queueTitle;
	extern std::string line;
	extern Coord fakeTitleCrd;			
	extern Coord realTitleCrd;
	extern Distance btwTitle;		
	extern int limitLeftX;			
	extern int limitRightX;			
	extern int yPos[MAX_QUEUE_SIZE];

	struct Drawer
	{
		unsigned char sym;
		Colors clr;
		SpeedTimer timer;
		int currStep = 0;
		bool cancel = false;	
		bool active = false;
	};

	class DrawerQueue
	{
	public:
		Drawer drawer[MAX_QUEUE_SIZE];
		int total;
		void Cancel();			
		void Remove(int index);
		void Remove_All();

		bool Add_To_Index(Modifier modifier, int index);	
		bool Add_To_Next_Available(Modifier modifier);	
		bool Is_Active(int index);
	};


	void Show_Queue_UI();	
	void Hide_Queue_UI();	
	void Show_Queue_No_Ammo_UI();
	void Show_Excess();		
	void Hide_Excess();
	void Reorder_Rest_Of_Queue();

	void Set_Mod_Queue_Pos();

	void Set_Char_From_Mod(Modifier mod, unsigned char& sym, Colors& clr);

	void Update_Modifier_Queue();	

}



