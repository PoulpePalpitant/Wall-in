#pragma once

#include "blast.h"
#include "../UI/txtstyle.h"


namespace DrawBlastAmmo {

	const int  MAX_BAR_SIZE = 15;	// Longueur de la bar vertical qui va repr�senter la quantit� d'ammo. Exclut les tips
	extern bool isShown;			// si le player vois l'UI d'ammo

	extern double ratioBarPerAmmo;				// Nombre de munition pour chaque char de la bar 
	extern double nextAmmoEr;			// Le nombre de munition � atteindre pour progresser dans la bar
	extern bool erDozen;			// Efface la dizaine

	// UI
	static const char tip[3] = { (unsigned char)250 , (unsigned char)196,  (unsigned char)194 };	//Les tips en bas et en haut de la bar. le dernier c'est pour connecter la bar avec le tip quand ils se touchent
	static const char barSym = (unsigned char)179;		// Symbole de la bar
	extern int barLength;		// Dimension de la bar actuelle. Exclut les tips
	
	// COLORS BAR
	static const Colors barTreshClr[3]{ BRIGHT_WHITE, LIGHT_YELLOW, LIGHT_RED };		// Pour chacun des tresholds franchie, l'on change la couleur de la bar pour la suivante
	static const float prcentBarClrTresh[2]{ .65, .25 };				// Si l'on franchie ces valeurs en pourcentage pour le nombre de munition, barProgClr va chang� pour la prochaine couleur
	extern Colors barProgClr;				// Couleur des chars de la bar -> blanc -> jaune -> rouge	selon la progression

	// COLORS AMMMO COUNT
	extern int ammoMaxTresholdClr;										// Le nombre d'ammunitions max qui a �t� sett�. Ce montant est fix�, il changera uniquement � la prochaine fois que Set_Ammo est utilis�
	static const Colors ammoTreshClr[4]{LIGHT_AQUA, BRIGHT_WHITE, LIGHT_YELLOW, LIGHT_RED };		// Pour chacun des tresholds franchie, l'on change la couleur de la bar pour la suivante
	static const float prcentAmmoClrTresh[2]{ .50, .25 };		// Si l'on franchie ces valeurs en pourcentage pour le nombre de munition, ammoProgClr va chang� pour la prochaine couleur
	extern Colors ammoProgClr;				// Couleur du nombre d'ammo

	// Bunche of stuff pour les animations
	extern std::string queueTitle;
	extern std::string line;

	extern Coord titleCrd;			// La corrd du ttitre principal
	extern Distance btwTitle;		// Distance entre le titre de la queue et la limite gauche � droite. On va slide les charact�re � gauche et � droite. 
	extern Distance mapToBar;		// Distance entre la bordure de la map et la bar
	extern Distance barToCount;		// Distance entre la bar et le nombre repr�sentant l'ammo count
	//extern int barX;				// Position en x de la bar
	//extern int yOriBar;			// Le point d'origine d'o� va s'afficher la bar

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
		int MAX_QUEUE = 0;	// devrait �tre const s�rieurx
		int total = 0;

		void Remove_All();
	public:
		Drawer* queue;			// public stuff
		int Get_Total() { return total; }
		void Step(int index, int speed = 0, int steps = 1, bool infinite = false);		// Avance l'event d'un step
		void Cancel(Coord XY);		// Stop l'animation sur cette position
		bool Add(Coord XY);		// Ajoute un �l�ment � draw
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

	Colors Get_Bar_Treshold_Color(int barLength);	// Retourne la couleur que la bar aurait selon une longueur
	Colors Get_Ammo_Treshold_Color(int currAmmo);	// Retourne la couleur que le compteur d'ammo aurait selon le nombre de tir fait



	// INSTANT
	void Show_Ammo_UI(bool instant = false);	// Affiche l'interface d'ammo
	void Hide_Ammo_UI();	// Efface l'ui instantann�ment
	void Dr_Or_Er_Bar(int length, Colors clr = WHITE, bool erase = false);  // Affiche la bar, selon une couleur
	void Dr_Bar_Sym(int distance, Colors clr = WHITE, bool erase = false ); // Affiche le symbole de la bar selon une distance du point d'origine en bas. 
	void Dr_Bar_Tip(bool topTip, Colors clr = WHITE, bool erase = false, bool connected = false); // Affiche l'une des 2 extr�mit�s. False = botTip
	void Dr_Ammo_Used();		// Le joueur tir, L'UI s'UPDATE
	void Dr_Ammo_Remove();	 // R�duit de 1 le nombre d'ammo
	void Dr_Bar_Remove();	 // R�duit la bar selon le ratio

	void Dr_Ammo_Count(int count, Colors clr = BRIGHT_WHITE);				// Le nombre
	void Er_Ammo_Count();													// partis


	// ANIMATION
	void Ev_Dr_Bar_From_Scratch();				 // Affiche la bar au complet
	void Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de mani�re progressive
	void Ev_Dr_Ammo_Count_Add();		 // Quand il y a un ajout d'ammo
	void Ev_Dr_Bar_Add();		 // Quand il y a un ajout d'ammo



}



