#include <thread>			// testing
#include <conio.h>

#include "validate_input.h"
#include "detect_input.h"

#include "../UI/console_output/dsp_char.h"
void Test_Animation(Colors one, Colors two);	// So pretty...


void Detect_Input()
{


	int input;



	input = 0;


		
		
		if ((_kbhit()))
			Validate_Input();		// Les actions du joueur se font ici

		while (_kbhit())	// tampon vidé
			_getch();


	//std::thread inputThread(Check_Input);	// pour l'instant, chaque input est threadé and thast how we do
	//inputThread.join();
	std::thread test(Test_Animation, RED, WHITE);

	
	
	if (test.joinable())	// test de thread
		test.join();
		
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

void Test_Animation(Colors one, Colors two)	// So pretty...
{
	Coord crd = { 0, 2 };
	int max = 80;
	unsigned char sym = 178;

	while (crd.x <= max) {

		if (crd.x % 2 == 0)
			UI_Dsp_Char(crd, sym, one);
		else
			UI_Dsp_Char(crd, 178, two);

		crd.x++;
	}

}