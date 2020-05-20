#pragma once

#include "../UI/coord.h"
#include "../UI/direction.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"
#include "../grid/grid.h"
#include "spawnwarning.h"
//#include "./botinitialize/"


enum class BotType{ REGULAR, TOUGH, SUPERSONIC, GHOSTER };		// Le ghoster transforme tout murs qu'il touche en un mur indestructible par les bots. Comment le stop? : si tu pèse sur space sur un boute . : tous les walls de la chaine deviennent gold?

const unsigned char BOT_DESIGN_1C[4]{ 202,185,203,204 };		// Le design du BOt à 1 charactère
//const char BOT_DESIGN_2C[4]{ 202,185,203,204 };		// Le design du BOt à 2charactères, si jamais t'en fais un

struct CustomBot
{
	bool NoWarning;					// La possibilité de ne pas afficher de warning	
	int health;	int speed;			// Stats custom
	char boSym;	Colors botColor;	// Possibilité de changer le Design
};

// Si tu veux spécifier des stats custom pour plus qu'un bot, tu va devoir faire des tableaux mon gars
extern CustomBot gCustomBot;	// Permet de faire des bots customs 
extern bool gIsBotCustom;		// Permet de vérifier si on initialise un Bot custom.. devrait pt être dans la fct spawn. plus loin dans le futur

class Bot
{
private:

	// DESIGN
	char sym;						// Le symbole du Bot. Les Bots normaux N,auront qu'un seul symbol. Si tu veux changer de design, fais-toi une autre class
	bool fixedColor = false;		// Détermine si la couleur reste fixe tout au long
	Colors color = Colors::WHITE;	// Couleur du bot

	// STATS
	int health;									// La puissance d'un bot, soit le nombre de mur reégulier qu'il peut traverser avant d'être détruit
	int speed = 1;								// Le nombre de case de déplacement par cycle.   Si tu veux faire de quoi de plus custom, faudrait que tu abandonne les movecycle global, et que tu en assigne un à chaque bot(meh)
	BotType type = BotType::REGULAR;			// Son type ? Ne contient pas vraiement d'information, sert pas mal juste pour l'initialisation du Bot, meh

	// DÉPLACEMENTS/Position
	Direction dir;						// Ça direction de déplacement
	Coord XY;							// Coordonéée du bot en valeure compressée
	GridIndexIncrementor nxtWallCrd;	// Donne la coordonnée en colonnes et lignes du prochain mur que le bot va percuter. Se renouvelle à chaque fois que le bot traverse un élément du wall grid sans crever
	Distance btwWalls;					// LA distance qui sépare chaque élément du grid de walls. Sert de référence pour la prochaine variable
	C_D tillNxtWall;					// Donne le nombre actuel de Bot_move_cycle, de cycles de mouvement de Bot, avant que le Bot se retrouve sur la même position qu'un wall. Se renouvelle de la même manière.

	int stepCount = 0;		//	Le nombre de déplacement fait depuis le début de son éxistence.
	int stepLeft;			//	Le nombre de déplacement pour atteindre l'autre decôté de la box, par rapport à sa position actuelle 
	int stepLeftMax;		//	Nb de déplacement total à faire au moment du spawn,

	// GESTION DE LA LISTE DES BOTS
	friend class BotList;	// La classe Botlist va s'en charger
	Bot* prev;				// Pointeur vers le bot précédent de la liste de bots
	Bot* next;				// Pointeur vers le prochain bot de la liste
	
	// INITALISATION DU BOT -  // Tous les définitions se retrouveront dans d'autres cpp
	friend Bot* Create_New_Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised);			// NOT A MEMBBER OF CLASS BOT!!!

	void Init_Bot_Coord_Stuff(GrdCoord& spGrdCrd);												// Le design du bot est initialisé( son symbole et sa couleur)
	void Init_Step_Count();																		// La distance qu'il doit parcourir and shit
	void Init_Bot_Stats(CustomBot* customBot = NULL);											//  Initialise health and speed : Le type du Bot doit être initialisé d'abord.
	void Init_Bot_Design(CustomBot* customBot = NULL);											// Le design du bot est initialisé( son symbole et sa couleur)
	void Init_Dist_Btw_Walls();																	// Initialise btwWalls
	void Find_First_Wall_Grd_Index(Direction indexBoxSide, int indexrow, GridIndexIncrementor& wallcrd);	// Trouver l'index [c][r] du premier wall que le bot va rencontrer
	void Init_Spawn_Warning(Direction botDir, C_D warnCycles = SPWN_DLAY);						// to figure out

public:		
	// MÉTHODES D'ACCÈS GET
	Direction Get_Dir() { return dir; }						// Direction de déplacement
	Coord Get_XY() { return XY; }							// Coord XY
	C_D Get_Cycles_Till_Nxt_Wall() { return tillNxtWall; } // Nombre de cycles avant le prochain impact de wall
	int Get_Steps_Count() { return stepCount; }				// Nombre de steps fais par le bot
	int Get_Step_Left() { return stepLeft; }				// Nombre de steps à faire restant
	int Get_Max_Possible_Steps() { return stepLeftMax; }	// Nombre de steps qu'il devait faire dès le moment de son spawn
	BotType Get_Type() { return type; }						// Le type

	// MÉTHODES QUI UPDATE LES PROPRIÉTÉS DU BOT
	void Strt_Nxt_Wall_Time(){ tillNxtWall = btwWalls / speed; }				// Reset le temps que ça va prendre pour rencontrer un autre wall
	void Upd_Nxt_Wall_Time() { tillNxtWall--; }									// Réduit de 1 le compteur
	void Upd_Progression_Color(Colors& Color, int NumStepsLeft, int Max_Steps);	// Change la couleur du bot quand il s'approche de plus en plus de son escape

	// CONSTRUCTOR
	Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised)	// Construit en utilisant d'autre fonctions
	{
		static CustomBot* customBot;	customBot = NULL;

		// Le bot qui va suivre est customized
		if (isBotCustomised)
			customBot = &gCustomBot;		// Je pourrais mettre ce test dans chacune des fonctions suivantes aussi

		this->type = type;	// Le type de bot est initialisé

		// INITIALISATION DES VARIABLES DE POSITIONS 'N SHIT
		Init_Bot_Coord_Stuff(spGrdCrd);

		// INITIALISATION DU DESIGN DU BOT 
		Init_Bot_Design(customBot);

		// INITIALISE LES STATS DU BOT
		Init_Bot_Stats(customBot);						// Le type du Bot doit être initialisé d'abord

		// INITIALISE DISTANCE À PARCOURIR
		Init_Step_Count();								// À besoin de la direction et de la vitesse du bot

		Init_Dist_Btw_Walls();							// Fait juste initialiser btwWalls
		Strt_Nxt_Wall_Time();							// Pour starter le prochain timer

		// Je crois qu'il serait pertinent de faire une nouvelle classe de bot uniquement si ses mouvements ou ses intéractions avec les autres objets du jeux sont différentes

	}

	// Les constructors sont tough à design :O					 Indeed...
};


