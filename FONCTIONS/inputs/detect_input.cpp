

#include <conio.h>

#include "validate_input.h"
#include "detect_input.h"

#include "../UI/console_output/dsp_char.h"


void Detect_Input()
{
	if ((_kbhit()))
		Validate_Input();		// Les actions du joueur se font ici

	Clear_Cache();
}

void Clear_Cache()	// Clear le tampon du getch pour mes inputs de base
{
	while (_kbhit())	// tampon vidé
		_getch();
}


void Test_Animation(Colors one, Colors two);	// So pretty...

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