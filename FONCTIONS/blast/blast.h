#pragma once

#include "../grid/grd_incrementor.h"
#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"
#include "../walls/walls.h"
#include "../link/link.h"
#include "../time/countdown_clock.h"

/*
	Le blast ça va être la façon pour le joueur de détruire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur à partir de sa position de départ. Ce projectile va avancé jusqu'à ce qu'il 
	atteigne un obstacle. Quand le projectile s'arrête, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est détruit

*/
struct BlastType						
{
	WallStrength strength;	// La force du wall qui sera créé.	/ Change aussi l'apparence du blast actif
	LinkType linkType;		// Le type de Link qui sera créé	/ Change l'apparence aussi? 
};							// Change les propriétés du blast

extern const BlastType DFLT_BLAST;				// Les propriétés principales du Blast par défaut
extern const Distance DFLT_BLAST_LENGTH_HOR;		// La longueur par défaut du blast 
extern const Distance DFLT_BLAST_LENGTH_VER;		// La hauteur par défaut du blast
extern const time_t DFLT_BLAST_SPD_VER;				// Vitesse par défaut du blast 
extern const time_t DFLT_BLAST_SPD_HOR;

// Quand le joueur appuie sur une touche de tir, il faut Setup les proprités du blast qu'il va tirer. Ces propriétés seront entreposer dans cette class
// SIDENOTE: Une seule structure de blast sera créé(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement changé

class Blast
{
	friend void Change_Blast();	 // Testing blast types

	protected:
		friend class UI_MoveBlast;	// L'animation du blast 
		friend class WallGrid;		// Accès pour enregistré des nouveaux murs
		friend class AllGrids;
		friend class LinkGrid;		// Pour enregistré des nouveaux Links

	bool active;			// Le blast est actif ou non. Quand il est actif il est en train de se déplacer

	//UI
	unsigned char sym;		// Le symbole du blast sera unique et répété(juste une longue ligne)
	Colors color;			// La couleur du blast sera unique, ou changera dépandamment de ton animation.
	Distance length;		// Donne la longueur max du blast qui va être tiré en nombre de case dans la console
	Distance maxlengthHor = DFLT_BLAST_LENGTH_HOR;	// La longueur du blast selon l'axe des X. Peut être augmenté ou réduite durant la game
	Distance maxlengthVer = DFLT_BLAST_LENGTH_VER;	// La longueur du blast selon l'axe des Y. Peut être augmenté ou réduite durant la game 
	int speed;	/*milliseconds*/					// Vitesse du blast(ou délaie entre chaque affichage)
	time_t speedVer = DFLT_BLAST_SPD_VER;		// Vitesse du blast verticale
	time_t speedHor = DFLT_BLAST_SPD_HOR;		// Vitesse du blast horizontale
	
	// POSITION/DÉPLACEMENT
	int grdLimit;					// L'endroit ou le blast va s'arrêter dans son épopé linéaire
	Distance nbSteps;		// Le nombre de déplacement que le blast à fait dans la console (1 case = un déplacement)
	Distance btwLinks;				// LA distance qui sépare chaque élément du grid de links. Sert de référence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de déplacement à faire avant que le blast se retrouve sur la même position qu'un élément LINK.

	GridIndexIncrementor grdPos;		// HITBOX: Position dans le grid. Vérifie colision avec les link que le blast traverse en avançant dans le grid. 
	CoordIncrementor frontXY;			// UI: Sert à uniquement à afficher chaque symbole de l'animation (dans une direction). Sert aussi à trimer la longueur du blast dans l'animation
	CoordIncrementor tailXY;			// UI: Sert  à trimer la longueur du blast dans l'animation
	Direction dir;						// Ça direction dans la consoles
	CDTimer updateTimer;				// Permet de limiter la vitesse de l'update de la position du blast

	// POST-BLAST	/* temporaire
	WallStrength strength = WallStrength::REGULAR;	// La force du wall qui sera créé.	/ Change aussi l'apparence du blast actif
	LinkType linkType = LinkType::REGULAR;		// Le type de Link qui sera créé	/ Change l'apparence aussi? 

	// SETUP DU BLAST
	void Setup_Blast_UI();					// Assigne l'apparence du blast
	void Setup_Grid_Limit();								// Calcul la limite ou le blast va devoir s'arrêter
	void Setup_Position_Incrementors(GrdCoord &startPos);	// Sa position 
	void Setup_Dist_Btw_Links();								// Setup la distance qui va séparer chaque élément du Link Grid que le blast va parcourir
	void Setup_Length();					// Ajuste la longueur du blast qui sera tiré
	void Setup_Speed();											// La vitesse d'affichage du blast(temps de pause entre chaque)

	// CHANGEMENT DES PROPRIÉTÉS DE BASES
	void Modify_Max_LengthHor(Distance newLength) { maxlengthHor = newLength; }		// Longueur horizontale
	void Modify_Max_LengthVer(Distance newLength) { maxlengthVer = newLength; }		// Longueur vertical
	void Modify_SpeedHor(unsigned int spd) { speedHor = spd; }			// Vitesse horizontale
	void Modify_SpeedVer(unsigned int spd) { speedVer = spd; }			// Vitesse verticale

	// MISE EN ACTION DU BLAST
	bool Has_Reached_Limit();		// Vérifie si le blast à atteint la fin de son périple
	bool Blast_Is_On_LinkGrid();	// Vérifie si la "tête" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }		// Reset le temps que ça va prendre pour rencontrer un autre Link
	void Stop_Blast();	// stop le blast...... le grus

	// POST-BLAST
	int Nb_Of_Links_To_Activate();
	int Nb_Of_Walls_Per_Blast();		// Calcul le nombre de walls à enregistrer après un blast.
public:
	// GET UTILES
	const CoordIncrementor* const Get_Front_XY() { const CoordIncrementor* const copy = &frontXY; return copy; }		// Retourne un pointeur constant vers l'adresse, pour pouvoir copier correctement l'axe, qui est en fait un pointeur vers une crd
	Direction Get_Dir() { return dir; }
	Distance Get_Distance_Travelled() { return nbSteps; }

	// FONCTIONS PRINCIPALES 

	bool Is_Active() { return active; }	// is it dow?
	void Setup_Blast( GrdCoord &startPos, Direction &blastDir/* const BlastType& type = DFLT_BLAST*/);	// Setup tout les paramètre du blast pour le tir
	void UPD_Blast_Shot();	// le tir du blast...
};

// Les objets blasts :D

extern Blast blastP1;
extern Blast blastP2;

