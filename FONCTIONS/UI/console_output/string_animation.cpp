


#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	// Uniquement pour empêcher f'afficher par dessus le joueur
#include "../../time/timerOP.h"
#include "string_animation.h"


//StringAnimationList strList;


CharData StringQueue::Pop_First()	// Prend le prochain élément dans la liste
{
	nbChar--;
	return queue[curr++];	// Je devrait tester ça first, mais ça devrait work
}

void StringQueue::Add_String(Coord crd, std::string txt, Colors clr, bool erase) // Ajoute chaque charactère de la string dans la queue
{
	int size = (int)txt.length();	// Assignation de la longueur de la string 	
	if (erase)
	{
		for (int ch = 0; ch < size; ch++)
		{
			Add(crd, TXT_CONST.SPACE, clr);
			crd.x++;										// Incrémente x pour le prochain charactère	
		}
	}
	else
		for (int ch = 0; ch < size; ch++)
		{
			Add(crd, txt[ch], clr);
			crd.x++;										// Incrémente x pour le prochain charactère	
		}
}

void StringQueue::Add(Coord crd, char sym, Colors clr)		// Ajoute l'item à draw dans la list
{
	static CharData tempDrawer = {};

	tempDrawer.crd = crd;
	tempDrawer.symbol = sym;
	tempDrawer.clr = clr;

	queue[nbChar] = tempDrawer;
	nbChar++;
}
