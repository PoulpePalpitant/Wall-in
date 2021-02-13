//
//
//
//
//#include "msg_dispatcher.h"
//#include "events.h"
//#include "global_events/ev_pause_game.h"
//
//
//
//// DEF DES STATICS
//
//Event* Event::eventsID[MAX_NUM_EVENTS] = {};	// TOUT LES EVENTS
//FixedList<int>Event::toUpdate(MAX_NUM_EVENTS);	// Initialisation, une fois, de la queue d'event actifs à updater 
//int Event::total;	// Nombre d'events dans le jeu
//
//void Safety();	// si, somehow, le timer est à OFF et que l'event est activé , on l'arrête
//
//
//void Event::Activate()
//{
//	isActive = true;	
//	toUpdate.Register(ID);	// Ajoute l'event à la liste à updater
//}
//
//void Event::Deactivate()
//{
//	static int index;
//
//	isActive = false; 
//	if(toUpdate.Find_Element(ID, index))
//		toUpdate.Unregister(index);	//	Retire l'event à la liste de "à updater"
//}
//
//void Event::Cancel_All()	// Gros moyen
//{
//	// the inefficient, but correct way
//	for (int id = 0; id < MAX_NUM_EVENTS; id++)
//	{
//		if (eventsID[id] && eventsID[id]->Is_Active()) // check si non-nul, et si actif
//			eventsID[id]->Deactivate();
//	}
//}
//
//
//// UPDATE TOUT LES EVENT EN COURS !!!!!!!!!!!!!!!!!!!!!!!!
//void Event::Update_Active_Events()
//{
//
//	for (toUpdate.index = 0; toUpdate.index < toUpdate.Get_Total(); toUpdate.index++)		// Tant qu'on a des events qui n'ont pas été updaté
//	{
//		eventsID[toUpdate.Copy_Element(toUpdate.index)]->Handle_It();		// Ne jamais touché à toUpdate.index en dehors d'ici :()
//	}																		// Pour l'instant, un event pourrait en activer un autre, et rallonger cette loop!
//}
//
//bool Event::Stop_If_No_More_Steps()
//{
//	if (curSteps > MAX_STEPS)		// > c'est un fail safe
//	{
//		Deactivate();			// We deactivate!!!
//		return true;
//	}
//	else
//		return false;
//}
//
//// Avance l'event d'un stade. Surtout bon pour de l'animation en ce moment. Mais peut aussi être utilisé pour créer un peu de délay entre les choses
//void Event::Advance(int speed, int numMove)
//{
//	if (!delay.Is_On()) // Si ya pu aucun moves à faire,
//	{
//		curSteps++;	// Avance d'un Step 
//
//		if (!Stop_If_No_More_Steps()) // Désactive l'event quand il à atteint son stade final		
//			delay.Start_Timer(speed, numMove);	// Créer un nouveau délay entre le prochain update
//	}
//}			
//
//void Event::Start(int speed, int numMove )			// Start l'event!	blob blob
//{
//	curSteps = 1;	// First Step 
//	delay.Start_Timer(speed, numMove);	// Créer un nouveau délay entre le prochain update
//}
//
//void Event::Cancel()									// Termine abruptement l'event 
//{
//	delay.Stop();		// stahpping it
//	Deactivate();			// We deactivate!!!
//}