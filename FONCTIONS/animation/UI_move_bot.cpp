




#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "../UI/console_output/dsp_char.h"

#include "UI_move_bot.h"

// Classic Draw/ erase
void UI_MoveBot::Animate_Bot(Bot* bot, Coord &prevPos) 
{
	Erase_Bot(bot, prevPos);	// Wonderful animation
	Move_Bot_Forward(bot);		// wonderful animation
}

void UI_MoveBot::Move_Bot_Forward(Bot* bot)
{
	// Affichage du symbole du blast 
	UI_Dsp_Char(bot->XY, bot->sym, bot->clr);
}

void UI_MoveBot::Erase_Bot(Bot* bot, Coord &pos)	// ERASE le bot
{
	// Efface le bot
	UI_Dsp_Char(pos, TXT_CONST.SPACE);
}