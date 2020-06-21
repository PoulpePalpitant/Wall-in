#pragma once

#include "../UI/coord.h"
#include "../UI/direction.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"
#include "../grid/grid.h"
#include "../grid/spawngrid.h"
#include "../grid/grd_incrementor.h"
#include "spawnwarning.h"
#include "../UI/map.h"


enum class BotType{ REGULAR, TOUGH, SUPERSONIC, GHOSTER };		// Le ghoster transforme tout murs qu'il touche en un mur indestructible par les bots. Comment le stop? : si tu pèse sur space sur un boute . : tous les walls de la chaine deviennent gold?

const int MAX_NUM_BOTS = 35;		// Nombre de bot maximum dans la console

const unsigned char BOT_DESIGN_1C[4]{ 202,185,203,204 };		// Le design du BOt à 1 charactère

struct CustomBotStats
{
//	bool NoWarning;					// La possibilité de ne pas afficher de warning	, fait un niveau là dessu à la place
	int health;	int speed;			// Stats custom
	bool is;						// Permet de vérifier si on initialise un Bot custom.. devrait pt être dans la fct spawn. plus loin dans le futur

};

// Si tu veux spécifier des stats custom pour plus qu'un bot, tu va devoir faire des tableaux mon gars
extern CustomBotStats gCustomBot;	// Permet de faire des bots customs 

class Bot
{
private:
	friend class BotMove;		// Pour les déplacements des bots

	bool Take_Dmg(int dmgs);						// le bot prend du dégât, quand il rentre dans un mur

	// DESIGN
	char sym;						// Le symbole du Bot. Les Bots normaux N,auront qu'un seul symbol. Si tu veux changer de design, fais-toi une autre class
	bool fixedColor = false;		// Détermine si la couleur reste fixe tout au long
	Colors clr = Colors::WHITE;	// Couleur du bot

	// STATS
	int hp ;								// La puissance d'un bot, soit le nombre de mur reégulier qu'il peut traverser avant d'être détruit. si égal à zéro, le bot est DEAD
	int speed ;								// Le nombre de case de déplacement par cycle.   Si tu veux faire de quoi de plus custom, faudrait que tu abandonne les movecycle global, et que tu en assigne un à chaque bot(meh)
	BotType type = BotType::REGULAR;			// Son type ? Ne contient pas vraiement d'information, sert pas mal juste pour l'initialisation du Bot, meh

	// DÉPLACEMENTS/Position
	Direction dir;						// Ça direction de déplacement
	Coord XY;							// Coordonéée du bot en valeure compressée
	Distance btwWalls;					// LA distance qui sépare chaque élément du grid de walls. Sert de référence pour la prochaine variable
	C_D tillNxtWall;					// Donne le nombre actuel de Bot_move_cycle, de cycles de mouvement de Bot, avant que le Bot se retrouve sur la même position qu'un wall. Se renouvelle de la même manière.
	GridIndexIncrementor nxtWallCrd;	// Donne la coordonnée en colonnes et lignes du prochain mur que le bot va percuter. Se renouvelle à chaque fois que le bot traverse un élément du wall grid sans crever
	GrdCoord onAWall;		// Donne la coordonnée en colonnes et lignes du prochain mur que le bot va percuter. Se renouvelle à chaque fois que le bot traverse un élément du wall grid sans crever
	SpawnWarning spwnWarning;			// Mon implantation lazy du warning qui arrive avant qu'un bot spawn


	int stepCount = 0;		//	Le nombre de déplacement fait depuis le début de son éxistence.
	int stepLeft;			//	Le nombre de déplacement pour atteindre l'autre decôté de la box, par rapport à sa position actuelle 
	int stepLeftMax;		//	Nb de déplacement total à faire au moment du spawn,

	void Init_Bot_Coord_Stuff(SpwCrd& spGrdCrd);												// Le design du bot est initialisé( son symbole et sa couleur)
	void Init_Step_Count();																		// La distance qu'il doit parcourir and shit
	void Init_Bot_Stats(CustomBotStats* customBot = NULL);											//  Initialise health and speed : Le type du Bot doit être initialisé d'abord.
	void Init_Bot_Design(CustomBotStats* customBot = NULL);											// Le design du bot est initialisé( son symbole et sa couleur)
	void Init_Dist_Btw_Walls();																	// Initialise btwWalls
	void Find_First_Wall_Grd_Index(Direction indexBoxSide, int indexrow, GridIndexIncrementor& wallcrd);	// Trouver l'index [c][r] du premier wall que le bot va rencontrer

public:		
	// MÉTHODES D'ACCÈS GET
	Direction Get_Dir() { return dir; }						// Direction de déplacement
	Coord Get_XY() { return XY; }							// Coord XY
	GridIndexIncrementor Get_nxtWallCrd() { return nxtWallCrd; }
	C_D Get_Cycles_Till_Nxt_Wall() { return tillNxtWall; } // Nombre de cycles avant le prochain impact de wall
	int Get_Steps_Count() { return stepCount; }				// Nombre de steps fais par le bot
	int Get_Step_Left() { return stepLeft; }				// Nombre de steps à faire restant
	int Get_Max_Possible_Steps() { return stepLeftMax; }	// Nombre de steps qu'il devait faire dès le moment de son spawn
	BotType Get_Type() { return type; }						// Le type
	int Get_Power() { return hp; }						// son power
	
	// MÉTHODES QUI UPDATE LES PROPRIÉTÉS DU BOT
	void Strt_Nxt_Wall_Time(){
		tillNxtWall = btwWalls / 
			speed; }				// Reset le temps que ça va prendre pour rencontrer un autre wall
	void Upd_Nxt_Wall_Time() { tillNxtWall--; }									// Réduit de 1 le compteur
	void Upd_Progression_Color();												// Change la couleur du bot quand il s'approche de plus en plus de son escape

	// UI
	static void UI_Draw_Bot(Bot* bot, Coord& nxtPos);	// draw le bot
	static void UI_Erase_Bot(Bot* bot);	// l'efface
	static void Animate_Bot(Bot* bot, Coord& nxtPos);	// efface et draw le bot
	void UI_Dis_Warning(); //prout // Affiche le symbole du warning, et l'efface aussi. C'est en quelque sorte l'animation du spawn warning ici.



	// INTÉRACTIONS
	bool Is_Dead();		// vérifie si un bot est mort
	void Destroy_Bot();	// Destruction d'un bot
	void Create_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised);	// Construit en utilisant d'autre fonctions
	bool Bot_Impact(Wall* wall);					// Quand un bot rentre dans un wall

	// GESTION DE LA LISTE DES BOTS
	//friend class BotList;	// La classe Botlist va s'en charger
	//Bot* pPrev;				// Pointeur vers le bot précédent de la liste de bots NON
	//Bot* pNext;				// Pointeur vers le prochain bot de la liste

	// INITALISATION DU BOT -  // Tous les définitions se retrouveront dans d'autres cpp
	//friend Bot* Create_New_Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised);			// NOT A MEMBBER OF CLASS BOT!!!
};

