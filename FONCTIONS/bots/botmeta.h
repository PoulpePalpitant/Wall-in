#pragma once



class BotMeta {
	
public:
	int alive;		// Le nombre de bots en vie en ce moment
	int spawned;		// Le nombre de bots spawné
	int dead;		// Le nombre de bots qui ont péris
	//static int dmgDone;

	void New_Bot() { this->alive++; this->spawned++; }
	void Bot_Died(){ this->alive--; this->dead++; }
};

extern BotMeta gBotMetaReg;		// L'objet global botmeta

//struct MetaAllBot		// si jamais ta d'autres sortes bots
//{
//	int TotAlive;
//	int TotSpawned;
//	int TotDead;
//	int TotWallDestroyed;
//	int TotDmgDone;
//};