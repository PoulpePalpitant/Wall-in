#pragma once

#include "blast.h"
#include "../UI/txtstyle.h"


namespace DrawBlastAmmo {

	const int  MAX_BAR_SIZE = 15;	// Longueur de la bar vertical qui va représenter la quantité d'ammo. Exclut les tips
	extern bool isShown;			// si le player vois l'UI d'ammo

	extern double ratioBarPerAmmo;				// Nombre de munition pour chaque char de la bar 
	extern bool erDozen;			// Efface la dizaine

	// UI
	static const char tip[3] = { (unsigned char)250 , (unsigned char)196,  (unsigned char)194 };	//Les tips en bas et en haut de la bar. le dernier c'est pour connecter la bar avec le tip quand ils se touchent
	static const char barSym = (unsigned char)179;		// Symbole de la bar
	extern int barLength;		// Dimension de la bar actuelle. Exclut les tips
	
	// COLORS BAR
	static const Colors barTreshClr[3]{ BRIGHT_WHITE, LIGHT_YELLOW, LIGHT_RED };		// Pour chacun des tresholds franchie, l'on change la couleur de la bar pour la suivante
	static const float prcentBarClrTresh[2]{ .65, .25 };				// Si l'on franchie ces valeurs en pourcentage pour le nombre de munition, barProgClr va changé pour la prochaine couleur
	extern Colors barProgClr;				// Couleur des chars de la bar -> blanc -> jaune -> rouge	selon la progression

	// COLORS AMMMO COUNT
	extern int ammoMaxTresholdClr;										// Le nombre d'ammunitions max qui a été setté. Ce montant est fixé, il changera uniquement à la prochaine fois que Set_Ammo est utilisé
	static const Colors ammoTreshClr[4]{LIGHT_AQUA, BRIGHT_WHITE, LIGHT_YELLOW, LIGHT_RED };		// Pour chacun des tresholds franchie, l'on change la couleur de la bar pour la suivante
	static const float prcentAmmoClrTresh[2]{ .50, .25 };		// Si l'on franchie ces valeurs en pourcentage pour le nombre de munition, ammoProgClr va changé pour la prochaine couleur
	extern Colors ammoProgClr;				// Couleur du nombre d'ammo

	// Bunche of stuff pour les animations
	extern std::string queueTitle;
	extern std::string line;

	extern Coord titleCrd;			// La corrd du ttitre principal
	extern Distance btwTitle;		// Distance entre le titre de la queue et la limite gauche à droite. On va slide les charactère à gauche et à droite. 
	extern Distance mapToBar;		// Distance entre la bordure de la map et la bar
	extern Distance barToCount;		// Distance entre la bar et le nombre représentant l'ammo count
	

	Colors Get_Bar_Treshold_Color(int barLength);	// Retourne la couleur que la bar aurait selon une longueur
	Colors Get_Ammo_Treshold_Color(int currAmmo);	// Retourne la couleur que le compteur d'ammo aurait selon le nombre de tir fait
	Coord Get_Ori();		// Permet de trouver la coord d'origine d'où on va afficher la bar. Cette crd se fit elle même au coin HAUT_DROIT de la map. 



	// INSTANT
	void Show_Ammo_UI(bool instant = false);	// Affiche l'interface d'ammo
	void Hide_Ammo_UI();	// Efface l'ui instantannément
	void Dr_Or_Er_Bar(int length, Colors clr = WHITE, bool erase = false);  // Affiche la bar, selon une couleur
	void Dr_Bar_Sym(int distance, Colors clr = WHITE, bool erase = false ); // Affiche le symbole de la bar selon une distance du point d'origine en bas. 
	void Dr_Bar_Tip(bool topTip, Colors clr = WHITE, bool erase = false, bool connected = false); // Affiche l'une des 2 extrémités. False = botTip
	void Dr_Ammo_Used();		// Le joueur tir, L'UI s'UPDATE
	void Dr_Bar_Remove();	 // Réduit la bar selon le ratio
	void Dr_Ammo_Title(bool show = 1);	
	void Dr_Emergency_Ammo(int ammo);
	void Dr_Ammo_Gain();
	void Ev_Dr_Ammo_Gain();		 // Tit animation quand ya un ammo pickup

	void Dr_Ammo_Count(int count, Colors clr = BRIGHT_WHITE);				// Le nombre
	void Er_Ammo_Count();													// partis
	void Update_Ammo_Count();	 


	// ANIMATION
	void Ev_Dr_Bar_From_Scratch();				 // Affiche la bar au complet
	void Ev_Dr_Ammo_Count_From_Scratch();		 // Affiche le nombre d'ammo de manière progressive
	void Ev_Dr_Ammo_Count_Add();		 // Quand il y a un ajout d'ammo
	void Ev_Dr_Bar_Add();		 // Quand il y a un ajout d'ammo



}



