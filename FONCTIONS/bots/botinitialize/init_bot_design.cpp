#include "../bot.h"


void Bot::Init_Bot_Design(CustomBotStats& customBot)
{
	this->sym = BOT_DESIGN_1C[dir];

	if (customBot.is)
	{
		clr = customBot.clr;
		fixedColor = customBot.fixedColor;
	}
	else
	{
		switch (type)
		{
		case BotType::REGULAR: clr = WHITE; break;
		}
	}
}