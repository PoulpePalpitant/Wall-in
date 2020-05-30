#include <thread>			// testing
#include <conio.h>

#include "validate_input.h"
#include "detect_input.h"

void Detect_Input()
{
	int input;

	while (_kbhit())	// tampon vidé
		_getch();

	input = 0;

	do
	{
		if ((_kbhit()))
			input++;

	} while (input < 1); // Loop de détectionj d'input

	//std::thread inputThread(Check_Input);	// pour l'instant, chaque input est threadé and thast how we do
	//inputThread.join();

	Validate_Input();		// Les actions du joueur se font ici
	

	//std::thread blastThread(&Blast::Blast_Shot, &blastP1, type, crd, keyDirection); // Thread tir de blast
	//blastThread.join();	// On attend que le blast finis avant de détecter d'autres inputs

	/*
		NOW:
		Threader un blast
		Tir du blast à partir d'une bordure
		----Enregistrer les links et walls---- done
	
		Tir de blast sur les Links
		--Wall Redirect--
		--Player mouvement--
		Tir de blast quand t'es sur un Link
		Tir de blast quand t'es sur un link et sur une  bordure
		Tir de blast quand t'es sur un link et qu'un autre link est trop proche


	*/

}

