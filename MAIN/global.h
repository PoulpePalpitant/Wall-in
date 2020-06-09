#pragma once 
#include <iostream>   // pour le cout
#include <conio.h>   // pour le _getch()
#include <string>	// pour le string
#include <iomanip> // pour les manipulateurs
#include <windows.h> //pour le time, et toute sorte de shits.
#include < ctime >	// pour utiliser la fonction clock()
#include "console(v1.9).h"
#include "WinUser.h"

using namespace std;


//***************************************************************
//	LA LISTE DE TOUS LES VARIABLES GLOBALES QUE JE DOIS RETIRER *
//	DE MAIN	et spreader dans les différentes fonctions			*			
//***************************************************************


// Types pour le jeu

using Time = unsigned int;		// pour les timer
using Indice = int;
using In = Indice;				//In = à l'indice des tableaux
using Deplacement = int;		// Pour les déplacements
using Distance = int;			// Pour calculer les distances entre les choses, selon les axes de directions
using Coordinates = int;
using border = int;				//Dimension de la map
using CoordinatesXY = int;
using C_D = unsigned int;		// Compteur


// TAILLE DES TABLEAUX

const In MaxNumBOTS = 50;			// Nombre Maximum de BOTS affichés à l'écran
const In MaxSpawn_COORD = 15;		// Nombre de Spawns maximum présent sur une bordure
const In ML = 300;					//Max nombres de link
const In C = 3600;					//Nb de charactere max dans la console
const In Bo = 4;					// Bo pour Border. Représente le nombre de côté du terrain de jeu, qui est une console rectangulaire
const In Bi = 2;					// Bi pour binaire. 2 choix
int Index;

//Direction Nord Sud Est Ouest, sur l'axe X et Y, positif (1) ou négatif(-1)
enum Axe { y, x };									//Y = 0, alors false,    X = 1 alors true!
enum Direction { UP, LEFT, DOWN, RIGHT };
enum Polarisation { Pos = 1, Neg = -1, NUL = 0 }; // Je vais intégré ça dans la direction!!! :O
Polarisation Pos_Neg;

// Des couleurs
enum Colors
{
	BLACK = 0, GRAY = 8,
	BLUE = 1, LIGHT_BLUE = 9,
	GREEN = 2, LIGHT_GREEN = 10,
	AQUA = 3, LIGHT_AQUA = 11,							// Numbers after 15 include background colors
	RED = 4, LIGHT_RED = 12,
	PURPLE = 5, LIGHT_PURPLE = 13,
	YELLOW = 6, LIGHT_YELLOW = 14,
	WHITE = 7, BRIGHT_WHITE = 15
};

enum Statut { DEAD, ALIVE, INVINCIBLE};		// Statut Héro 



// Logique de Blocage des Spawns 

// La classe Side désigne deux côté possible du terrain de jeu en relation avec la bordure ou un BOT sera créé: Le A et le B. 
// Le Side A représente la bordure soit UP ou LEFT
// Le Side B représente la bordure RIGHT ou DOWN	(même logique que la lecture d'un livre)
// Les Bordures A et B sont importantes, car c'est sur ces deux Bordures perpendiculaires qu'originerait un BOT pouvant entrer en colision
// avec celui qu'on essaie de créer. On utilise donc Side pour blocker ces Coordonnées de «spawns» selon un indice de temps. 

// Calculé dans la fonction Spawn_BOT()
enum Sides { A, B };

// Représente l'ensemble des variables nécessaire pour empêcher les «Spawns» perpendiculaires à la bordure de création d'un BOT 
// de faire spawner des BOTS pouvant entrer en colision avec celui qu'on vient d'être créé
struct Perpendicular_Spawn_Block
{

	Polarisation polar_BOT;				// La polarisation positive ou négative du mouvement du BOT qu'on vient de créer. Si négatif, on va inversé la direction dans lequel on va passer dans le tableau de spawn à blocker
	Direction spwn_Side[Bi];			// Désigne quels sont les deux Bordures de Spawns à blocker
	Distance betwn_Spwn[Bi];			// La distance séparant chaque spawn perpendiculaire. Soit ShipMoveX ou ShipMoveY

	Distance from_BOT_To_Side[Bi];		// Représente la distance séparant le BOT à la Bordure perpendiculaire. Sert à trouver le premier point d'intersection
	Distance from_BOT_To_Intersection[Bi];//AJOUTÉ	// Représente la distance séparant le BOT au point d'intersection. Sert à trouver le nombre de cycles de mouvement des bots avantler premier impact
	CoordinatesXY frst_Spwn_Intersection[Bi];	// La coordonnée perpendiculaire au spawn, X OU Y(selon la direction du mouvement du BOT tout juste spawné) de la première colision perpendiculaire possible. Sert à trouver la première COORDXY du premier Block Possible
	CoordinatesXY first_BlockXY[Bi];	// Sert d'outil de comparaison pour trouver la première COORDXY de spawn à blocker . À noter que cette coordonnée peut se trouver entre deux spawns. On utilise donc une deuxième COORD pour la trouver.
	CoordinatesXY next_Closest_Spwn[Bi];// Cette coordonnée se retrouve à une distance de Spawn plus loin que first_BlockXY. Entre ces deux coordonnées se trouve forcément le premier Spawn à blocker
	In first_Block_Coord[Bi];			// La coordonnée du premier Spawn à blocker. Ceci est égal à son indice dans le tableau des spawns

	int cycles_Before_Impact[Bi];		// Le nombre de Cycle de mouvements des BOTS avant le premier impact. On le trouve par cette équation(la distance entre le bot et l'intersection - la distance entre Block et l'intersection): from_BOT_To_Side - from_BOT_To_Intersection 
	Time min_Time_Impact[Bi];			// Désigne quel est le premier Cycle de Mouvement des Bots ou un spawn provoquerait une colision
	bool no_Need_To_Block[Bi];			// Désigne le fait que le BOT actuel est trop loin pour qu'un spawn perpendiculaire créer une colision
	bool spwn_Found[Bi];				// Le premier Spawn à blocker est trouvé!
};

Perpendicular_Spawn_Block perp_Sp_Blck;	//--------------------------- pas encore utilisé


// Enregistre tout les indices des spawn coord qui fut invalide pour le spawn des bots de ce cycle
struct Inv_Coord_ind
{
	int Ind;
	Inv_Coord_ind* nxt = NULL;
};

// Enregistre tout les coordXY qui fut invalide pour le spawn des bots de ce cycle
struct Inv_SpCrd
{
	int spwnXY;
	Inv_SpCrd* nxt = NULL;
};


// à faire plus tard i guess
//Structure pour les dimensions de la map+
struct MapBorder { border limit[4]; };
MapBorder box;		// La box est l'aire de déplacement du joueur
MapBorder spawn;	// Les spawns des bots sont localisés sur une bordure un peu à l'extérieur de la box. 

// VARIABES GLOBALES!!!

//Position et Dimension du Terrain de jeu
_COORD con;	// Dimension de la console
int CoordX = 0, CoordY = 0, CoordXY;
int GridX = 0, GridY = 0, GridXY;			// GridXY permet de chercher les Coordonnées dans les tableaux.
int WallX, WallY, WallXY;					//La Map du jeu est une sorte de Grid ou chaque intersections est une 		
const int CompresseurXY = 1000;				// positions XY contenant le Ship, un Link, VitalLink ou un tit «Boute».												
Distance Box_to_Spawn = 1;					// Distance entre la Coordonnée de Spawn et le bordure de la box	*IMPORTANT*

struct Coord { int X = box.limit[RIGHT] / 2;  int Y = box.limit[DOWN] / 2; };

// Pour un certain affichage de stats
const string StatsT[] = { "Current time: ","Current BOT Cycle: ", "Next BOT Move : ", "Current Spawn Cycle: ","Next Spawn : ", "TOT Spw Cyc: " };

//	Chaque tableau sera initialisé à 0 ou -1. Si une variable contient 0, elle devient valide pour l'inscription d'une nouvelle valeure.
//	Sinon, elle devient valide pour une destruction de donnée (réinisialisation à 0 de la variable)

//WALLS 

/*		Les Walls sont essentiellement les résidus des blasts. Une Accumulation de blast créer des chaînes de murs
		reliés par des des points LINK. Si un impact survient au mileu d'un wall, CELUI-CI sera détruit, en plus de tous
		les autres walls qui ne seront plus connectés à la bordure de la console.

		Pour décompresser WallXY et LinkXY en Coordonnée x et Y
			Wallx = Valeure entière de WallXY		WallX = WallXY[0]; = 120
			Wally = 	-> si WallXY= 120.30		WallY = WallXY[0] * 100 - WallX * 100 ; = 30
*/

int Wall[C] = {};	//Quand WALLXY n'est pas égal à 0.00, ça veut dire qu'un mur est présent sur la coordonnée

bool Create_Walls = true;	//	Création de walls
bool Create_Boute = true;	//	Création d'un Boute
bool Le_Boute = false;		//	Si on affiche un Boute "."
bool Wall_Transfer = false;

//	STRUCTURES DE WALLS

int VitalLinkXY[ML] = {};	//Le vitalLink est le parent des links. Si un vitallink est brisé, tous les links associé successivement sont brisés
int LinkXY[ML] = {};			//Ce sont les enfants des vitallink, les points qui servent de chaines pour les structures
int VitalCompteur[ML] = {};		//Permet de savoir le nombre de link qui dépende du vitalLink (varie de 1 à 3) 
int LinkIndice[ML] = {};		//L'indice du VitalLink = La valeur de LinkIndice. L'indice du linkindice = à l'indice du LinkxY , bref un pointeur un peu bâtard
int LinkDirection[ML] = {};		//La direction qu'à pris le Blast lors de la création du Link ..  «Voir DirectionB»  ..
//NOTE : Une coord xy peut vas avoir à la fois un Link et et VitalLink. La seule exception est un ALPHA, donc le premier, il n'aura qu'un VitalLink

int L = 0, VL = 0;	//Les indices suivant permettEnt de liER les vitallink avec les Link

//	Les conditions pour l'enregistrement de nouvelles valeurs dans les tableaux de Structure de Walls
int NbBlastLink, MaxBlastLink;
int NbBlastLinkX = 3, NbBlastLinkY = 2;	//Nombre d'intersection maximum(Link/vitalLink) que peut créer un Blast
int NbWallX = 4, NbWallY = 2;	//	Le nombre de Walls séparant chaque links sur l'axe des X et Y
//calculé dans une fonction

int CmbDeWalls;
bool NoVLSym = false, Skip_FirstVL = false;
int Couleur = 15;


//	DESTRUCTION DES STRUCTURES

int CoordLeft, CoordRight, Destruction;
int VL_Left, VL_Right, VL_Origin;
bool DESTROY_STRUCTURE = false, DestroyLeft_Right = false, One_Link_Destruction = false;
int NumVLtoDestroy;
int VitalLink_Destruction[ML] = {};

int DirectionX, DirectionY;
int FirstIndex;
int NbdeWalls;	// Nombre de Walls à détruire

//Pour ton animation de Destruction Post-Mortem
int Destruction_Animation[10][500];
int Counter_Walls = 0;
int Counter_Destruction = 0;


//	HÉRO
struct HERO
{
	int health = 3;							// Le nombre de fois que des bots doivent s'enfuir pour perdre la partie
	Colors clr = Colors::LIGHT_GREEN;
	Statut statut = ALIVE;
};

HERO hero;


char HeroSym = 197;
const char AllPlyrSym[5] = { 193,180,194,195,197 };	// Haut, Left, Down, Droite,  Neutre
int HeroX = 0;									//La coordonnée XY du Ship dans la console
int HeroY = 0, HeroXY;
int HeroMoveX = 5, HeroMoveY = 3, HeroMoveXY;	//La distance que peut parcourir le Ship pour un Mouvement sur les X et Y
char mouvement, action;							//Inputs du joueur.
bool Hero_Move = false;
bool BackStep = false;							// mouvement : "WASD" = Déplacement		Haut Gauche Bas Droite
bool MouvementValide = true;					// action :  Flèches du clavier = Tir du Blast dans une des quatre directions
										   // BackSTep: Si le joueur tir de trop près sur quelquechose, il recule d'un pas

//	DESIGN BLAST

const char BlastSymX = 196, BlastSymY = '\263', BlastSymBoute = '\372', VitalLinkSym = 'O', ALPHASym = '\333';
const int TailleBlastX = 10, TailleBlastY = 3;							//Longueur du Blast: TailleBlast % ShipMove = 0. Toujours!!!!!!!!!!!
char BlastSym;															// Prend la form de BlastSymX ou BlastSymY
int CleanBlast, CleanBlastX = 0, CleanBlastY = 0, TailleBlast = 0;		//Limite la longueur du blast selon la taille en x et y

//	ANIMATION DU BLAST

int BlastFin = 0,			//La limite que le blast ne peut franchir(soit une sorte de box imaginaire pour le moment)	. Voir BOXfin au début	
BlastX = 0,					//La position xy pour cout un blast
BlastY = 0,
NSWE = 0,					//La direction Nord Sud Est West que va prendre le blast(selon touche fleche clavier)	
DirectionB;					//La direction positive ou négative que va prendre le blast dans la console : 
							//Positif = Droite-Bas		,			Négatif = Gauche-Haut									
Axe X_ou_Y = Axe::x;				//Axe de mouvement:	true = X(1) = horizontal 	false = Y(0) = vertical   
bool BlastStop = false;		//Désigne l'arrêt du Blast. Survient quand le Blast atteint la Coord d'un Link Ou VitalLink 
int BlastSizeLoop = 0;		//Désigne combien de case le Blast à parcourue, commence à 0

//	VARIABLES DE BOTS!

unsigned int BOT_Move_Cycle;			// On bouge les BOT à chaque x click de la Clock du processuer!
unsigned int Current_BOT_MOVE_Cycle;	// Le cycle instantanné du mouvement des bots. On déplace tout les BOTS à chaque cycles
unsigned int Next_BOT_MOVE_Cycle;		// Le prochain cycle des mouvements des bots. Est déterminé selon la vitesse des bots (BOT_Move_Cycle)
int BOTXY[MaxNumBOTS];					// Coordonéée du bot en valeure compressée
int BOT_Direction[MaxNumBOTS];			// Ça direction de déplacement
bool Move_BOTS_this_Cycle = true;		// Détermine si on bouge, ou on a déjà bougé les BOTS durant ce cycles
bool BOT_Escape = false;				// Si un bot sort de la box. Selon le niveau, on perd la game ou 1 de vie
int SPWN_DLAY = 9;						// Le nombre de bot move cycle avant que le bot va commencer à avancer

// VARIABLES D'ÉVÈNEMENTS LVL1
bool FastStart = false;			// Enclanche le tutorial
								// Donne des infos sur les mouvements de chaque bots: 											
struct BOT_Tracker
{
	int TotalSteps[MaxNumBOTS] = {};		//	Le nombre de déplacement nécessaire pour sortir de la box.
	int StepsToEscape[MaxNumBOTS];			//	Le nombre de déplacement nécessaire rapport à sa position actuelle dans la box
	int MaxSteps[MaxNumBOTS];				//	Nb de déplacement total à faire au moment du spawn,
	int warCountdown[MaxNumBOTS];				// Le countdown qui sert à montrer qu'un bot va spawner!!!
	int MaxBotDistanceX;					// Le nombre déplacement Max qu'un Bot peut parcourir selon son axe
	int MaxBotDistanceY;

	Colors color[MaxNumBOTS];		// Couleur du bot
	char warSym[MaxNumBOTS];		// Le symbole qui warn le player que le bot s'en vient!!
	int nbSym[MaxNumBOTS] = {};		// Donne le nombre de charactère à afficher pour afficher le BOT. Par défaut c'est 1. Là j'essaye deux
	int TOT_Alive = 0;				// Le nombre de bots spawné
	int TOT_Spawned = 0;
};

//Devrait plutôt être
// Bot
// BotMeta(Meta data)

BOT_Tracker BOT;

//		Le design temporaire du bot pour aider le joueur a mieux voir dans quel direction il va
struct BOT_Design { char BOT_Sym[MaxNumBOTS]; };	BOT_Design BOT_design;	// Devrait être dans la struct BOT >:(
const char BOT_temp_Design[4]{ 202,185,203,204 };
const char BOT_Wrng_Design[4]{ 'V','>','^','<' };
const char BOT_Design_2c[4]{ 202,185,203,204 };	// Le design du BOt à 2charactères

char BOT_Sym[4][2] = { {'b','p'}, {}, {}, {} };

// SPAWNS: Tableaux de liaison entre BOTS et SPawns et création de Coordonnées SPAWNXY

int BoxSide;					// Numéros associés aux bordure de la box
int MaxSpawn_CoordinatesX;		// Nombre de COORD de spawn Maximum sur les bordures horizontales UP(0) et DOWN(2)
int MaxSpawn_CoordinatesY;		// Nombre de COORD de spawn Maximum sur les bordures verticales LEFT(1) et RIGHT(3)
int MaxSpawnBlocks;				// Prend l'une des deux valeurs plus haut
int Indice_Spawn_COORD, NextSpawnXY;

int Spawn_Cycle;					// Vitesse des spawns
unsigned int Current_Spawn_Cycle;	// Le cycle des spawns actuel
unsigned int Next_Spawn_Cycle;		// Le prochain cycle de spawn

bool Spawn_this_Cycle = true;								//Permet de Spawner un ou plusieurs bot durant ce cycle
bool HorizontalSpawn = false, VerticalSpawn = false;		// Le prochain spawn sera vertical, ou horizontal	
bool Random_Spawn_COORD = true, Random_Boxside = true;	// Le prochain bot spawnera sur une COORD Aléatoire
bool Spawn_Valide = true;									// Vérifie si le spawn est valide( si faux, c'est que le bot entrerait en contact avec un autre BOT si il spawnait
bool Same_Side;												// Si tu fais plusieurs spawns d'une même shot, tu peux les spawners sur la même bordure
bool Multi_Spawn;											// Désigne le fait que plusieurs bot seront spawnés durant ce cycle, en même temps
int NumSpawn;											// Le nombre de spawns relatif durant un cycle de "Current_Spawn_Cycle"
int NumSpawnTOT;										// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
int Spwn_cycleTOT = 0;

struct Sp_CoordIn { int min; int max; bool active = false; };

Sp_CoordIn CoordIntv;					// Le prochain spawn de bot se situera entre un interval min et maximum de coord de spawn

//	Les Coordonnées des Spawn permettant de faire apparaître les BOTS
int SpawnXY[4][MaxNumBOTS] = {};		//4 = les quatres côté de la box

//	Variable servant à blocker toutes les Spawn qui ferait apparaître un Bot qui serait en collision directe avec le Bot actuel qu'on essaie de faire apparaître
int Spawn_Block[4][MaxSpawn_COORD][MaxNumBOTS] = {};	// Chaque coord de spawn "[4][MaxSpawn_COORD]" possède une valeure de temps associé à l'indice d'un BOTXY

//	Le SpawnXY juste en face du BOT actuel. On le block pour éviter une colision frontal. On met une valeure de temps pour chaque bot. Aussi longtemps que le temps actuel est inférieur à l'une de ces valeurs de temps, aucun bot ne peut spawn
bool front_Spawn_Block[4][MaxSpawn_COORD][MaxNumBOTS] = {};		// false
In front_Spawn_COORD[MaxNumBOTS] = {};		// permet de retrouver facilement la coordonnée du front spawn à blocker selon l'indice d'un bot

// LEVELS
bool Initialize_Level = true;
bool EndLevel = false;
int LVL_Script = 1;
int FinalChallengeTIME = 0;
bool LastBreath = false; //	Truc spécial qui arrive à la fin d'un niveau!( si on dépasse le FinalChallengeTIME)

struct LvlEvent { bool EvDone[20] = {}; int EvTOT = 0; };		// Pour tracker les events

LvlEvent lvlMsgEv[7];		// Les évènements purement en liens avec l'affichage de texts and shit
LvlEvent LVLNb[7];			// Les évènements autres		7 niveaux

//	TIMER 
clock_t Current_time, Timer_Start, Timer_End, Time_Passed;

//LOOP
int i, ii, j, W, Blockthisshit;
int input = 0;
bool loop = true;
int swag = 1;	// «Swag»

//Animation Ghost
int GhostX = 6;
int GhostY = box.limit[DOWN];
int UpDown = 0;
bool Merge = false;


//Affichage Messages et décompte
int countdown = 1000;

struct MESG { bool aff = true; bool del = true; };		// Permet de savoir si on affiche ou efface un message durant la game
MESG msg;
