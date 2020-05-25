#include <Windows.h>
#include <thread>			// testing
#include <conio.h>

#include "../blast/blast.h" // testing
#include "../grid/linkgrid.h"

#include "detect_input.h"


void Check_Input()
{

	// Le début d'une détection d'input qui à de l'allure
	//static MSG keyHit;

	//switch (keyHit.message)
	//{


	//}


	// for now though
	static char key;
	static Direction keyDirection; //Enregistre une touche d'action de tir du blast
	key = -1;
		// Reset la direction

	switch (key = _getch())
	{
	case 'w':keyDirection = UP; break;
	case 'a':keyDirection = LEFT; break;
	case 's':keyDirection = DOWN; break;
	case 'd':keyDirection = RIGHT; break;
	default: keyDirection = RESTE_ICITTE; 
	}
		
	
	/*
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		keyDirection = LEFT;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		keyDirection = RIGHT;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		keyDirection = UP;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		keyDirection = DOWN;
	}*/

	// TEST LE BLAST
	GrdCoord crd{ 7,7 };
	BlastType type = BlastType::REGULAR;
	//std::thread blastThread(&Blast::Blast_Shot, &blastP1, type, crd, keyDirection); // Thread tir de blast
	//blastThread.join();	// On attend que le blast finis avant de détecter d'autres inputs

	// BLAST FONCTIONNE EN S'ARRÊTANT SUR LES BORDURES
	Blast* blast = NULL;
	if (keyDirection != RESTE_ICITTE)
	{
		blast = blastP1.Blast_Shot(BlastType::REGULAR, crd, keyDirection);
		linkGrid.Activate_Links_From_Blast(blast);
	}
	/*
		NOW:
		Threader un blast
		Tir du blast à partir d'une bordure
		----Enregistrer les links et walls----
	
		Tir de blast sur les Links
		--Wall Redirect--
		--Player mouvement--
		Tir de blast quand t'es sur un Link
		Tir de blast quand t'es sur un link et sur une  bordure
		Tir de blast quand t'es sur un link et qu'un autre link est trop proche


	*/

}