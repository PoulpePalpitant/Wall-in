#include "bot.h"

#include "../UI/console_output/render_list.h"
#include "../walls/walls.h"
#include "botmeta.h"
#include "../spawns/ev_spawn_Jerry.h"
#include "../events/msg_dispatcher.h"

extern CustomBotStats gCustomBot = {};	

void Reset_Custom_Bot()
{
	gCustomBot.clr = WHITE;
	gCustomBot.health = 1;
	gCustomBot.warningDelay = SPWN_DLAY;
	gCustomBot.fixedColor = false;
	gCustomBot.is = false;
}

bool Bot::Is_Dead()										
{
	if (this->hp <= 0)
		return true;
	else
		return false;
}

void Bot::Destroy_Bot()
{
	this->hp = 0;		// this boi is dead
	ConsoleRender::Add_Char(this->XY, TXT_CONST.SPACE, this->clr);		
	gAllBotMeta.Bot_Died();	
	
	if (jerryTime)
		MsgQueue::Register(JERRY_DIED);	// pooR Jerry
}


// Cr�ation d'un bot
void Bot::Create_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised, bool instant)	
{
	static CustomBotStats customBot;	customBot.is = false;

	if (isBotCustomised)
	{
		customBot = gCustomBot;		
		Reset_Custom_Bot();				
	}

	this->type = type;	

	// INITIALISATION DES VARIABLES DE POSITIONS 'N SHIT
	Init_Bot_Coord_Stuff(spGrdCrd);

	// INITIALISATION DU DESIGN DU BOT 
	Init_Bot_Design(customBot);

	// INITIALISE LES STATS DU BOT
	Init_Bot_Stats(customBot);						

	// Le warning de spawn du bot
	if (instant)
		this->spwnWarning.Init_Spawn_Warning(dir, 0);
	else
		if (customBot.is)
			this->spwnWarning.Init_Spawn_Warning(dir, customBot.warningDelay);
		else
			this->spwnWarning.Init_Spawn_Warning(dir, SPWN_DLAY);

	// INITIALISE DISTANCE � PARCOURIR
	Init_Step_Count();								

	Init_Dist_Btw_Walls();							
	tillNxtWall = GAP_BTW_GRID - 1;

	gAllBotMeta.New_Bot();		
}


void Bot::Upd_Progression_Color()
{
	static int Halfway; Halfway = stepLeftMax / 2;	// Le bot est � moiti� chemin >:| 
	static int HURRY; HURRY = 10;					// Il reste 10 bot moves!!
	
	if (this->stepLeft == Halfway)
		clr = Colors::LIGHT_YELLOW;
	else if (stepLeft == HURRY)
		clr = Colors::LIGHT_RED;
}

// Le bot prend du d�g�t, quand il rentre dans un mur
// ----------------------------------------------

bool Bot::Take_Dmg(int dmg)
{
	bool deadBot = false;

	this->hp -= dmg;	
	if (this->Is_Dead())
	{
		this->Destroy_Bot(); 
		deadBot = true;
	}

	return deadBot;	
			   
}

bool Bot::Bot_Impact(Wall* wall)
{
	if (!wall->Is_Activated())
		return false;

	bool deadBot = false;
	int HP;	

	HP = wall->Get_Hp();

	if (wall->Get_Type() != WallType::WEAK) // just passing.	
	{
		wall->Take_Damage(this->Get_Power()); // Taking dmg here!
		deadBot = Bot::Take_Dmg(HP);	 	  // Hey me too!
	}
	else
	{
		wall->Set_Type(WallType::REGULAR);
	}

	if (deadBot)
		wall->Remove_Bot_On_Me();	

	return deadBot;
}

// Classic Draw/ erase
void Bot::Animate_Bot(Bot* bot, Coord& nxtPos)
{
	UI_Erase_Bot(bot);	            
	UI_Draw_Bot(bot, nxtPos);		
}

void Bot::UI_Draw_Bot(Bot* bot, Coord& nxtPos)
{
	ConsoleRender::Add_Char(nxtPos, bot->sym, bot->clr);
}

void Bot::UI_Erase_Bot(Bot* bot)	
{
	ConsoleRender::Add_Char(bot->XY, TXT_CONST.SPACE);
}

/*/prout prout*/
//�CA pas d'affaire ici, mais bon
void Bot::UI_Dis_Warning() {
	if (this->spwnWarning.nbWarnCycles% 2 == 0)
		ConsoleRender::Add_Char(this->XY, this->spwnWarning.warnSym, this->spwnWarning.warnColor);	// Affiche le warning que le bot s'en vient ( clignotement, alterne entre effacement et symbole : >, ' ', >, ' '
	else
		ConsoleRender::Add_Char(this->XY, TXT_CONST.SPACE);	
}

