
#include "botlist.h"
#include "../walls/walls.h"
#include "../UI/console_output/dsp_char.h"

#include "bot.h"

extern CustomBot gCustomBot = {};	// Permet de faire des bots customs 
extern bool gIsBotCustom = false;

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

bool Bot::Take_Dmg(int dmg, Bot*& bot, Bot*& prev)
{
	bool deadBot = false;

	bot->power -= dmg;	// power = HP

	if (bot->power <= 0)
	{
		botList.Destroy_Bot(bot, prev); // da bot is destroyed
		deadBot = true;
	}

	return deadBot;	// success?
	/*else update ça couleur ou son design I guess*/
			   
}


// Les trucs qui se passent quand un  bot rentre dans un wall
bool Bot::Bot_Impact(Bot*& bot, Bot*& prev ,Wall* wall)
{
	bool deadBot = false;
	int HP;	// l'hp du wall, AVANT l'impact
	HP = wall->Get_Hp();

	if (wall->Get_Type() == WallType::CORRUPTED)
		wall->UI_Draw_Or_Erase_Wall();		// Affiche le wall par dessus le bot le gros, just passing.	 Les bots passent à travers les corrupted
	else
	{
		wall->Take_Damage(bot->Get_Power()); // Taking dmg here!
		deadBot = Bot::Take_Dmg(HP, bot, prev);		// Hey me too!
	}

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
	// Affichage du symbole du blast 
	UI_Dsp_Char(nxtPos, bot->sym, bot->clr);
}

void Bot::UI_Erase_Bot(Bot* bot)	// ERASE le bot
{
	// Efface le bot
	UI_Dsp_Char(bot->XY, TXT_CONST.SPACE);
}