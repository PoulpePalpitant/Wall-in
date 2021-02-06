
#include "../../player/player.h"
#include "string_animation.h"




CharData StringQueue::Pop_First()	
{
	nbChar--;
	return queue[curr++];	
}

void StringQueue::Add_String(Coord crd, std::string txt, Colors clr, bool erase) 
{
	int size = (int)txt.length();	
	if (erase)
	{
		for (int ch = 0; ch < size; ch++)
		{
			Add(crd, TXT_CONST.SPACE, clr);
			crd.x++;										
		}
	}
	else
		for (int ch = 0; ch < size; ch++)
		{
			Add(crd, txt[ch], clr);
			crd.x++;										
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
