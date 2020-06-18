
#include <thread>
#include <chrono>

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "clock.h"


extern time_t gCrntLvLTime = 0;	 // Temps total �coul� depuis le d�but d'un niveau
extern GameClock gameClockTEST = {};	// TESTETSTESTETSTETSTETSTETSTETSTETSTESTETSTETSSTT
extern long double gLvlTime = 0;	// test de temps du lvl 


void GameClock::Start_Clock()	// Enclanche le temps. Conserve les donn�es reli� au temps �coul�
{
	if (this->running)	// Already running
		return;
	else
		running = true;

	if (time == 0)
		origin = clock();	// setup le point d'origine
}

void GameClock::Tick()
{
	if (running)
	{
		realTime = clock();			// Fin du timer
		time = realTime - origin;	// Actualisation du temps
	
	}
	// 35 ms � chaque loop?
}

void GameClock::Pause_Clock()
{
	this->running = false;
	origin = time;
}

void GameClock::Update_Time()
{
	while (running)	// Horloge d�sactiv�
	{	
		realTime = clock();			// Fin du timer
		time = realTime - origin;	// Actualisation du temps
	}
}

// UI
void GameClock::Dsp_Time(Coord crd, Colors clr)	// Affiche la clock � un certain endroit dans la console
{
	UI_Dsp_String(crd, std::to_string(time), clr, updateDelay);	 // affiche un int sous forme de string dans la console
	// Si tu veux afficher le nom de la clock, fais le manuellement, parce que affiche le nom � chaque fois dans une loop �a prend du jus
	// tu peux mettre une update speed avec std::this_thread::sleep_for(std::chrono::milliseconds(updateDelay));	// Attend 5 miliseconde entre chaque update!!!
}
void GameClock::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String(crd, clockName, clr, time);		// Affiche le nom
}







void CDTimer::Tick_Timer(float dt)	// Update le temps �coul� � partir de delta time
{
	if (this->isRunning)
		this->timeLeft -= dt;	// D�cr�mentation du temps

	if (this->timeLeft <= 0)
		this->isRunning = false;	// Stop le timer
}
void CDTimer::Start_CountDown()	// Enclanche le temps. Conserve les donn�es reli� au temps �coul�
{
	if (this->isRunning)	// �tait d�j� en cours
		return;
	else
		if (timeLeft <= 0 && cdDuration > 0)	// Le Countdown doit avoir une dur�e pour �tre start�
		{
			timeLeft = cdDuration;	// Reset le cooldown
			this->isRunning = true;	// Et on reprend
		}	
}





// UI
void CDTimer::Dsp_Time_Left(Coord crd, Colors clr)	// Affiche la clock � un certain endroit dans la console
{
	UI_Dsp_String(crd, std::to_string(timeLeft), clr);	 // affiche un int sous forme de string dans la console
	// Si tu veux afficher le nom de la clock, fais le manuellement, parce que affiche le nom � chaque fois dans une loop �a prend du jus
	// tu peux mettre une update speed avec std::this_thread::sleep_for(std::chrono::milliseconds(updateDelay));	// Attend 5 miliseconde entre chaque update!!!
}
void CDTimer::Dsp_Name(Coord crd, Colors clr, time_t time)			// Affiche le nom de la clock
{
	UI_Dsp_String(crd, timerName, clr, time);		// Affiche le nom
}

















/* Comment recharge un int avec des floats*/
// BETA

int timeAsInt;
int rechargeValue;
float timePassed;
float rechargeTime = 1.0f;	// 1 seconde

void Update(float TimeDelta)
{
	timePassed += TimeDelta;	// Float qui accumule du temps
	while (timePassed >= rechargeTime)
	{
		timePassed -= rechargeTime;   //Save the remainder for later
		timeAsInt += rechargeValue;
	}
}























/* OLD ONE WITH THREADS*/

//void GameClock::Start_Clock()			// Active l'horloge
//{
//	if (this->running)	// Already running
//		return;
//	else
//		running = true;
//
//	origin = clock();	// setup le point d'origine
//
//	// possibilit�
//	// std::thread * pClockThread = NULL;		
//	// pClockThread = new std::thread(Update_Time , this);
//	// et quand tu le join , tu devrais le delete, et le setter � null
//
//	// Le thread de l'horloge
//	this->th = std::thread(&GameClock::Update_Time, this); //YES
//
//}
//void GameClock::Pause_Clock()		// Arr�te le temps
//{
//	this->running = false;	
//	if(th.joinable())
//		th.join();				// Stop le thread du timer
//}
//
//void GameClock::Unpause_Clock()		// Re-d�marre le temps
//{
//	Start_Clock();	// Red�marre la clock
//}
// Affiche le temps � l'infinie!!!


//void GameClock::Infinite_Dsp(Coord crd, Colors clr)
//{
//	while (true) {
//		this->Dsp_Time(crd, clr);	// Affiche la clock � un certain endroit dans la console
//	//NO	MORE	std::this_thread::sleep_for(std::chrono::seconds(1));	// Attend une seconde entre chaque affichage!!!
//	}
//}

