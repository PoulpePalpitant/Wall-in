
#include "../UI/console_output/render_list.h"
#include "../walls/walls.h"
#include "botmeta.h"
#include "../spawns/ev_spawn_Jerry.h"
#include "../events/msg_dispatcher.h"
#include "bot.h"

extern CustomBotStats gCustomBot = {};	// Permet de faire des bots customs 

void Reset_Custom_Bot()
{
	gCustomBot.clr = WHITE;
	gCustomBot.health = 1;
	gCustomBot.warningDelay = SPWN_DLAY;
	gCustomBot.fixedColor = false;
	gCustomBot.is = false;
}

bool Bot::Is_Dead()											// vérifie si un bot est mort
{
	if (this->hp <= 0)
		return true;
	else
		return false;
}

void Bot::Destroy_Bot()
{
	this->hp = 0;		// Remet le HP à 0. this boi is dead
	ConsoleRender::Add_Char(this->XY, TXT_CONST.SPACE, this->clr);		//Effacement!
	gAllBotMeta.Bot_Died();	// One more :(
	
	if (jerryTime)
		MsgQueue::Register(JERRY_DIED);	// pooR Jerry
}


// Création d'un bot
void Bot::Create_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised)	// Construit en utilisant d'autre fonctions
{
	static CustomBotStats customBot;	customBot.is = false;

	// Le bot qui va suivre est customized
	if (isBotCustomised)
	{
		customBot = gCustomBot;		// Je pourrais mettre ce test dans chacune des fonctions suivantes aussi
		Reset_Custom_Bot();				/// for now, on reset le custom bot à chaque fois
	}

	this->type = type;	// Le type de bot est initialisé

	// INITIALISATION DES VARIABLES DE POSITIONS 'N SHIT
	Init_Bot_Coord_Stuff(spGrdCrd);

	// INITIALISATION DU DESIGN DU BOT 
	Init_Bot_Design(customBot);

	// INITIALISE LES STATS DU BOT
	Init_Bot_Stats(customBot);						// Le type du Bot doit être initialisé d'abord

	// Le warning de spawn du bot
	if(customBot.is)
		this->spwnWarning.Init_Spawn_Warning(dir, customBot.warningDelay);
	else
		this->spwnWarning.Init_Spawn_Warning(dir, SPWN_DLAY);

	// INITIALISE DISTANCE À PARCOURIR
	Init_Step_Count();								// À besoin de la direction et de la vitesse du bot

	Init_Dist_Btw_Walls();							// Fait juste initialiser btwWalls
	//Strt_Nxt_Wall_Time();							// Pour starter le prochain timer
	tillNxtWall = GAP_BTW_GRID - 1;

	gAllBotMeta.New_Bot();		// +1 les mecs!

	// Je crois qu'il serait pertinent de faire une nouvelle classe de bot uniquement si ses mouvements ou ses intéractions avec les autres objets du jeux sont différentes
}


// Change la couleur du BOT selon sa progression
// ----------------------------------------------

void Bot::Upd_Progression_Color()
{
	static int Halfway; Halfway = stepLeftMax / 2;	// Le bot est à moitié chemin >:| 
	static int HURRY; HURRY = 10;					// Il reste 10 bot moves!!
	
	if (this->stepLeft == Halfway)
		clr = Colors::LIGHT_YELLOW;
	else if (stepLeft == HURRY)
		clr = Colors::LIGHT_RED;
}

// Le bot prend du dégât, quand il rentre dans un mur
// ----------------------------------------------

bool Bot::Take_Dmg(int dmg)
{
	bool deadBot = false;

	this->hp -= dmg;	// power = HP

	if (this->Is_Dead())
	{
		this->Destroy_Bot(); // da bot is destroyed
		deadBot = true;
	}

	return deadBot;	// success?
	/*else update ça couleur ou son design I guess*/
			   
}


// Les trucs qui se passent quand un  bot rentre dans un wall
bool Bot::Bot_Impact(Wall* wall)
{
	if (!wall->Is_Activated())	// Le wall n'était pas activé, le bot survis!
		return false;

	bool deadBot = false;
	int HP;	// l'hp du wall, AVANT l'impact
	HP = wall->Get_Hp();

	if (wall->Get_Strgt() != WallStrength::NONE) // Affiche le wall par dessus le bot le gros, just passing.	 Les bots passent à travers les corrupted
	{
		wall->Take_Damage(this->Get_Power()); // Taking dmg here!
		deadBot = Bot::Take_Dmg(HP);		// Hey me too!
	}

	if (deadBot)
		wall->Remove_Bot_On_Me();	// le bot est dead, remove it!

	return deadBot;
}

// Classic Draw/ erase
void Bot::Animate_Bot(Bot* bot, Coord& nxtPos)
{
	UI_Erase_Bot(bot);	// Wonderful animation
	UI_Draw_Bot(bot, nxtPos);		// wonderful animation
}

void Bot::UI_Draw_Bot(Bot* bot, Coord& nxtPos)
{
	// Affichage du symbole du bot
	ConsoleRender::Add_Char(nxtPos, bot->sym, bot->clr);
}

void Bot::UI_Erase_Bot(Bot* bot)	// ERASE le bot
{
	// Efface le bot
	ConsoleRender::Add_Char(bot->XY, TXT_CONST.SPACE);
}

/*/prout prout*/
//¨CA pas d'affaire ici, mais bon
void Bot::UI_Dis_Warning() {
	if (this->spwnWarning.nbWarnCycles% 2 == 0)
		ConsoleRender::Add_Char(this->XY, this->spwnWarning.warnSym, this->spwnWarning.warnColor);	// Affiche le warning que le bot s'en vient ( clignotement, alterne entre effacement et symbole : >, ' ', >, ' '
	else
		ConsoleRender::Add_Char(this->XY, TXT_CONST.SPACE);	// Efface le symbole du warning précédent
}

