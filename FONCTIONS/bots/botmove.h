#pragma once

#include "../UI/coord.h"
#include "bot.h"

class BotMove {
	static bool Bot_Is_On_WallGrid(const Bot* const bot);
public:
	static void Move_Bots();
};
