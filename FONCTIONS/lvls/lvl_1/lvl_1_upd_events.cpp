


#include "msg_events/EV_Hello.h"

#include "lvl_1_upd_events.h"



		//static int activeEvents; 		// Nombre d'event actifs en ce moment.			Hey, That's too complex! Stop that!

// C'EST ICI QUE ÇA SE PASSE
void Lvl_1_Upd_Events()
{
	Lvl_1_Upd_Msg_Events();
	Lvl_1_Upd_Non_Msg_Events_Lol();
}

void Lvl_1_Upd_Msg_Events()// Observe si les conditions sont bonnes pour trigger un event
{
	// msg events.			juste du texte!
	// comment différencier les types d'events????
	// other events
}

void Lvl_1_Upd_Non_Msg_Events_Lol()// Gère et Update tout les event en cours pour le niveau 1
{
	// The bare minimum!

	Ev_Hello();
	// event Frappu()		Check si les conditions sont met. Fait l'event tout de suite
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
	// event Frappu()
}