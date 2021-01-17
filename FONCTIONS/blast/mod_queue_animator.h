#pragma once

#include "blast_modifier_queue.h"

namespace DrawModifierQueue {

	const int  MAX_QUEUE_SIZE = 5;

	extern bool isShown;		// si le player vois la queue

	// Bunche of stuff pour les animations
	extern std::string queueTitle;
	extern std::string line;

	extern Coord fakeTitleCrd;			// La corrd du ttitre principal
	extern Coord realTitleCrd;
	extern Distance btwTitle;		// Distance entre le titre de la queue et la limite gauche à droite. On va slide les charactère à gauche et à droite. 
	extern int limitLeftX;			// // La limite à gauche d'où l'animation va scroller le texte
	extern int limitRightX;		// La limite à droite ou l'animation va scroller le texte
	extern int yPos[MAX_QUEUE_SIZE];		// La ligne on va s'afficher chaque élément de la queue

	struct Drawer
	{
		unsigned char sym;
		Colors clr;
		SpeedTimer timer;
		int currStep = 0;
		bool cancel = false;		// empêche de draw le symbole du milieu. Survient que le joueur se déplace dessus, ou qu'un blast passe à travers
		bool active = false;
	};

	class DrawerQueue
	{
	public:
		Drawer drawer[MAX_QUEUE_SIZE];
		int total;
		void Cancel();					// Stop l'animation de l'item sur cette position
		void Remove(int index);
		void Remove_All();

		bool Add_To_Index(Modifier modifier, int index);	// Ajoute un item à draw
		bool Add_To_Next_Available(Modifier modifier);	// Ajoute un item à draw
		bool Is_Active(int index);
	};


	void Show_Queue_UI();	// Affiche la queue
	void Hide_Queue_UI();	// Efface la queue
	void Show_Queue_No_Ammo_UI();
	void Show_Excess();		// Les trois tits points qui apparaissent pour signaler qu'il y a plus que 5 éléments dans la queue
	void Hide_Excess();
	void Reorder_Rest_Of_Queue();

	void Set_Mod_Queue_Pos();

	void Set_Char_From_Mod(Modifier mod, unsigned char& sym, Colors& clr);

	void Update_Modifier_Queue();	// Update les autres animations

}



