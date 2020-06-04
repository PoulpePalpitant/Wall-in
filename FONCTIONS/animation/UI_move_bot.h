#pragma once 

#include "../bots/bot.h"

// Va créer l'animation du bot

class UI_MoveBot {
	friend class BotMove;
private:
	static void Move_Bot_Forward(Bot* bot);
	static void Erase_Bot(Bot* bot, Coord &pos);

protected:
	friend class Bot;
	static void Animate_Bot(Bot* bot, Coord &prevPos);
};
