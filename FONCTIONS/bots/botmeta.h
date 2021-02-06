#pragma once


class BotMeta {
	
public:
	int alive;	
	int spawned;
	int dead;		
	
	void New_Bot() { this->alive++; this->spawned++; }
	void Bot_Died(){ this->alive--; this->dead++; }
};

extern BotMeta gAllBotMeta;		// L'objet global botmeta

