#pragma once


class Bot {
public:
	static int TotSpawned;	// track le nombre de bot spawné durant une partie
	static int TotAlive;	// Track le nombre de bot en vie durant une game
	Bot() { TotSpawned++; TotAlive++; };		// 
};

int Bot::TotAlive = 0;		// Initialisation d'un membre static d'une class doit se faire en dehors de celle-ci!
int Bot::TotSpawned = 0;



class BotMeta {

	// Conserve les metadata des bots in someway
};



class Dummy {
public:
	static int n;
	Dummy() { n++; };
};

