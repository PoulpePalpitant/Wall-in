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


enum class BotType{ REGULAR };		

const int MAX_NUM_BOTS = 200;		

const unsigned char BOT_DESIGN_1C[4]{ 202,185,203,204 };

struct CustomBotStats
{
	int health = 1;					
	Colors clr = WHITE;
	bool fixedColor = false;
	int warningDelay = SPWN_DLAY;
	bool is = false;				
};

void Reset_Custom_Bot();

extern CustomBotStats gCustomBot;	// Permet de faire des bots customs 

class Bot
{
private:
	friend class BotMove;		// Pour les déplacements des bots

	bool Take_Dmg(int dmgs);	// le bot prend du dégât, quand il rentre dans un mur

	// DESIGN
	char sym;					
	bool fixedColor = false;	
	Colors clr = Colors::WHITE;	

	// STATS
	int hp ;								
	int speed ;								
	BotType type = BotType::REGULAR;		

	Direction dir;						
	Coord XY;							
	Distance btwWalls;					
	C_D tillNxtWall;					// Donne le nombre actuel de Bot_move_cycle, de cycles de mouvement de Bot, avant que le Bot se retrouve sur la même position qu'un wall. Se renouvelle de la même manière.
	GridIndexIncrementor nxtWallCrd;	
	GrdCoord onAWall;		
	SpawnWarning spwnWarning;			// Mon implantation lazy du warning qui arrive avant qu'un bot spawn


	int stepCount = 0;		
	int stepLeft;			
	int stepLeftMax;		

	void Init_Bot_Coord_Stuff(SpwCrd& spGrdCrd);												
	void Init_Step_Count();																		
	void Init_Bot_Stats(CustomBotStats& customBot);											
	void Init_Bot_Design(CustomBotStats& customBot);											
	void Init_Dist_Btw_Walls();																	
	void Find_First_Wall_Grd_Index(Direction indexBoxSide, int indexrow, GridIndexIncrementor& wallcrd);	// Trouver l'index [c][r] du premier wall que le bot va rencontrer

public:		
	Direction Get_Dir() { return dir; }						
	Coord Get_XY() { return XY; }							
	GridIndexIncrementor Get_nxtWallCrd() { return nxtWallCrd; }
	C_D Get_Cycles_Till_Nxt_Wall() { return tillNxtWall; } 
	int Get_Steps_Count() { return stepCount; }				
	int Get_Step_Left() { return stepLeft; }				
	int Get_Max_Possible_Steps() { return stepLeftMax; }	
	BotType Get_Type() { return type; }						
	int Get_Power() { return hp; }						
	int Get_Warnings() {	return spwnWarning.nbWarnCycles;}
	
	
	void Strt_Nxt_Wall_Time(){	tillNxtWall = btwWalls / speed; }				// Reset le temps que ça va prendre pour rencontrer un autre wall
	void Upd_Nxt_Wall_Time() { tillNxtWall--; }									
	void Upd_Progression_Color();												

	// UI
	static void UI_Draw_Bot(Bot* bot, Coord& nxtPos);	
	static void UI_Erase_Bot(Bot* bot);	
	static void Animate_Bot(Bot* bot, Coord& nxtPos);
	void UI_Dis_Warning(); //prout // Affiche le symbole du warning, et l'efface aussi. C'est en quelque sorte l'animation du spawn warning ici.



	// INTÉRACTIONS
	bool Is_Dead();		
	void Destroy_Bot();	
	void Create_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised,  bool instant = false);
	bool Bot_Impact(Wall* wall);					

};

