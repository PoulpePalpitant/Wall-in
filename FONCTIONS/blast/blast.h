#pragma once

#include "../grid/grd_incrementor.h"
#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"
#include "../walls/walls.h"
#include "../link/link.h"
#include "../time/countdown_clock.h"
#include "../time/movement_timer.h"
#include "../global_types/global_types.h"

/*
	Le blast �a va �tre la fa�on pour le joueur de d�truire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur � partir de sa position de d�part. Ce projectile va avanc� jusqu'� ce qu'il 
	atteigne un obstacle. Quand le projectile s'arr�te, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est d�truit

*/
struct BlastType						
{
	WallStrength strength;	// La force du wall qui sera cr��.	/ Change aussi l'apparence du blast actif
	Modifier mod;		// Le type de Link qui sera cr��	/ Change l'apparence aussi? 
};							// Change les propri�t�s du blast

extern const BlastType DFLT_BLAST;				// Les propri�t�s principales du Blast par d�faut
extern const Distance DFLT_BLAST_LENGTH_HOR;		// La longueur par d�faut du blast 
extern const Distance DFLT_BLAST_LENGTH_VER;		// La hauteur par d�faut du blast
extern const time_t DFLT_BLAST_SPD_VER;				// Vitesse par d�faut du blast 
extern const time_t DFLT_BLAST_SPD_HOR;

// Quand le joueur appuie sur une touche de tir, il faut Setup les proprit�s du blast qu'il va tirer. Ces propri�t�s seront entreposer dans cette class
// SIDENOTE: Une seule structure de blast sera cr��(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement chang�

class Blast
{
	friend void Change_Blast();	 // Testing blast types

	protected:
		friend class UI_MoveBlast;	// L'animation du blast 
		friend class WallGrid;		// Acc�s pour enregistr� des nouveaux murs
		friend class AllGrids;
		friend class LinkGrid;		// Pour enregistr� des nouveaux Links

	bool active;			// Le blast est actif ou non. Quand il est actif il est en train de se d�placer

	//UI
	unsigned char sym;		// Le symbole du blast sera unique et r�p�t�(juste une longue ligne)
	Colors color;			// La couleur du blast sera unique, ou changera d�pandamment de ton animation.
	Distance length;		// Donne la longueur max du blast qui va �tre tir� en nombre de case dans la console
	Distance maxlengthHor = DFLT_BLAST_LENGTH_HOR;	// La longueur du blast selon l'axe des X. Peut �tre augment� ou r�duite durant la game
	Distance maxlengthVer = DFLT_BLAST_LENGTH_VER;	// La longueur du blast selon l'axe des Y. Peut �tre augment� ou r�duite durant la game 
	int speed;	/*milliseconds*/					// Vitesse du blast(ou d�laie entre chaque affichage)
	time_t speedVer = DFLT_BLAST_SPD_VER;		// Vitesse du blast verticale
	time_t speedHor = DFLT_BLAST_SPD_HOR;		// Vitesse du blast horizontale
	
	// POSITION/D�PLACEMENT
	int grdLimit;					// L'endroit ou le blast va s'arr�ter dans son �pop� lin�aire
	Distance nbSteps;		// Le nombre de d�placement que le blast � fait dans la console (1 case = un d�placement)
	Distance btwLinks;				// LA distance qui s�pare chaque �l�ment du grid de links. Sert de r�f�rence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de d�placement � faire avant que le blast se retrouve sur la m�me position qu'un �l�ment LINK.

	GridIndexIncrementor grdPos;		// HITBOX: Position dans le grid. V�rifie colision avec les link que le blast traverse en avan�ant dans le grid. 
	CoordIncrementor frontXY;			// UI: Sert � uniquement � afficher chaque symbole de l'animation (dans une direction). Sert aussi � trimer la longueur du blast dans l'animation
	CoordIncrementor tailXY;			// UI: Sert  � trimer la longueur du blast dans l'animation
	Direction dir;						// �a direction dans la consoles
	SpeedTimer updateTimer;				// Permet de limiter la vitesse de l'update de la position du blast

	// POST-BLAST	/* temporaire
	WallStrength strength = WallStrength::REGULAR;	// obselete: force du blast
	Modifier modifier;		// Produit un effet unique quand le blast s'arr�te, notamment sur les links et les walls

	// SETUP DU BLAST
	void Setup_Blast_UI();					// Assigne l'apparence du blast
	void Setup_Grid_Limit();								// Calcul la limite ou le blast va devoir s'arr�ter
	void Setup_Position_Incrementors(GrdCoord &startPos);	// Sa position 
	void Setup_Dist_Btw_Links();								// Setup la distance qui va s�parer chaque �l�ment du Link Grid que le blast va parcourir
	void Setup_Length();										// Ajuste la longueur du blast qui sera tir�
	void Setup_Speed();											// La vitesse d'affichage du blast(temps de pause entre chaque)
	

	// CHANGEMENT DES PROPRI�T�S DE BASES
	void Modify_Max_LengthHor(Distance newLength) { maxlengthHor = newLength; }		// Longueur horizontale
	void Modify_Max_LengthVer(Distance newLength) { maxlengthVer = newLength; }		// Longueur vertical
	void Modify_SpeedHor(unsigned int spd) { speedHor = spd; }			// Vitesse horizontale
	void Modify_SpeedVer(unsigned int spd) { speedVer = spd; }			// Vitesse verticale

	// MISE EN ACTION DU BLAST
	bool Has_Reached_Limit();		// V�rifie si le blast � atteint la fin de son p�riple
	bool Blast_Is_On_LinkGrid();	// V�rifie si la "t�te" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }		// Reset le temps que �a va prendre pour rencontrer un autre Link
	void Stop_Blast();	// stop le blast...... le grus

	// POST-BLAST
	int Nb_Of_Links_To_Activate();
	int Nb_Of_Walls_Per_Blast();		// Calcul le nombre de walls � enregistrer apr�s un blast.
public:
	void  Set_Strength(WallStrength strgth) { strength = strgth; }	// Set la strength du blast(surviens g�n�ralement lors du transfert d'un wall. la strght sera la m�me que le wall)
	
	// GET UTILES
	const CoordIncrementor* const Get_Front_XY() { const CoordIncrementor* const copy = &frontXY; return copy; }		// Retourne un pointeur constant vers l'adresse, pour pouvoir copier correctement l'axe, qui est en fait un pointeur vers une crd
	Direction Get_Dir() { return dir; }
	Distance Get_Distance_Travelled() { return nbSteps; }
	Modifier Get_Modifier() { return modifier; }

	// FONCTIONS PRINCIPALES 

	bool Is_Player_Shooting_Border(Direction dir);			// Si le joueur est coll� sur une bordure, et tir dessus, le blast fail
	bool Is_Active() { return active; }	// is it dow?
	void Setup_Blast( GrdCoord &startPos, Direction &blastDir, bool consume = true);	// Setup tout les param�tre du blast pour le tir. Consume ou pas les �l�ments de laqueue(utilis� uniquement si le blast est un transfert)
	void Setup_Modifier(Modifier mod);							// Le modifier du blast, voir global_types.h
	void UPD_Blast_Shot();	// le tir du blast...

	// Special: Clear le blast quand on le cancel
	void Cancel() { active = false; }
	void Clear_Blast();
};

// Les objets blasts :D

extern Blast blastP1;
extern Blast blastP2;

