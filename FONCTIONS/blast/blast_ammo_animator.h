#pragma once

#include "blast.h"
#include "../UI/txtstyle.h"

namespace DrawBlastAmmo {

	const int  MAX_BAR_SIZE = 10;	// Longueur de la bar vertical qui va représenter la quantité d'ammo
	extern bool isShown;			// si le player vois l'UI d'ammo

	extern float ratio;				// Nombre de munition pour chaque char de la bar 
	extern int nextAmmoEr;			// Le nombre de munition à atteindre pour progresser dans la bar
	extern bool erDozen;			// Efface la dizaine

	// UI
	static const char tip[2] = { (unsigned char)250 , (unsigned char)196 };	// Si je met des tip
	static const char barSym = (unsigned char)179;		// Symbole de la bar
	static const char ctrSym = (unsigned char)196;		// Symbole au milieu quand la bar est vide
	extern int barLength;		// Dimension de la bar actuelle
	
	// COLORS
	static const Colors treshClr[3]{ WHITE, YELLOW, LIGHT_RED };		// Pour chacun des tresholds franchie, l'on change la couleur de la bar pour la suivante
	static const float prcentClrTresh[2]{ .50, .25 };		// Si l'on franchie ces valeurs en pourcentage pour le nombre de munition, progClr va changé pour la prochaine couleur
	extern Colors progClr;				// Couleur des chars de la bar -> blanc -> jaune -> rouge	selon la progression


	// Bunche of stuff pour les animations
	extern std::string queueTitle;
	extern std::string line;

	extern Coord titleCrd;			// La corrd du ttitre principal
	extern Distance btwTitle;		// Distance entre le titre de la queue et la limite gauche à droite. On va slide les charactère à gauche et à droite. 
	extern Distance mapToBar;		// Distance entre la bordure de la map et la bar
	extern Distance barToCount;		// Distance entre la bar et le nombre représentant l'ammo count
	//extern int barX;				// Position en x de la bar
	//extern int yOriBar;				// Le point d'origine d'où va s'afficher la bar

	struct Drawer
	{
		unsigned char sym;
		Colors clr;
		SpeedTimer timer;
		int currStep = 0;
		bool active = false;
	};

	class DrawerQueue
	{
		friend void Clear_All_States(bool eraseMap);	// Gros reset button

		int animationSteps;
		int MAX_QUEUE = 0;	// devrait être const sérieurx
		int total = 0;

		void Remove_All();
	public:
		Drawer* queue;			// public stuff
		int Get_Total() { return total; }
		void Step(int index, int speed = 0, int steps = 1, bool infinite = false);		// Avance l'event d'un step
		void Cancel(Coord XY);		// Stop l'animation sur cette position
		bool Add(Coord XY);		// Ajoute un élément à draw
		void Remove(int index);

		DrawerQueue(int MAX, int steps)
		{
			MAX_QUEUE = MAX;
			animationSteps = steps;
			queue = new Drawer[MAX];
		}

		~DrawerQueue()
		{
			delete[] queue;
		}
	};

	Colors Get_Treshold_Color(int barLength);	// Retourne la couleur que la bar aurait selon une longueur
	


	// INSTANT
	void Show_Ammo_UI(bool instant = false);	// Affiche l'interface d'ammo
	void Hide_Ammo_UI();	// Efface l'ui instantannément
	void Dr_Or_Er_Bar(int length, Colors clr = WHITE, bool erase = false);  // Affiche la bar, selon une couleur
	void Dr_Bar_Tips(int distance, Colors clr = WHITE, bool erase = false); // Affiche les 2 extrémités
	void Dr_Ammo_Count(int count, Colors clr = BRIGHT_WHITE);						// Le nombre
	void Er_Ammo_Count();													// partis


	// ANIMATION
	void Ev_Dr_Bar_From_Scratch();				 // Affiche la bar au complet
	void Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de manière progressive

	void Ev_Dr_Ammo_Add();		 // Quand il y a un ajout d'ammo
	void Ev_Dr_Ammo_Remove();	 // Quand un ammo est utilisé

}



