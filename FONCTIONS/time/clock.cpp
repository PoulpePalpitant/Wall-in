
#include <thread>
#include <chrono>

#include "../UI/console_output/dsp_int.h"
#include "../UI/console_output/dsp_string.h"
#include "clock.h"


extern time_t gCrntLvLTime = 0;	 
extern GameClock gameClockTEST = {};	


void GameClock::Start_Clock()	
{
	if (this->running)	
		return;
	else
		running = true;

	if (time == 0)
		origin = clock();
}

void GameClock::Tick()
{
	if (running)
	{
		realTime = clock();			
		time = realTime - origin;	
	
	}
}

void GameClock::Pause_Clock()
{
	this->running = false;
	origin = time;
}

void GameClock::Update_Time()
{
	while (running)
	{	
		realTime = clock();
		time = realTime - origin;	
	}
}

// UI
void GameClock::Dsp_Time(Coord crd, Colors clr)	
{
	UI_Dsp_String(crd, std::to_string(time), clr, updateDelay);	
	// tu peux mettre une update speed avec std::this_thread::sleep_for(std::chrono::milliseconds(updateDelay));	// Attend 5 miliseconde entre chaque update!!!
}
void GameClock::Dsp_Name(Coord crd, Colors clr, time_t time)			
{
	UI_Dsp_String(crd, clockName, clr, time);		
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
//	// possibilité
//	// std::thread * pClockThread = NULL;		
//	// pClockThread = new std::thread(Update_Time , this);
//	// et quand tu le join , tu devrais le delete, et le setter à null
//
//	// Le thread de l'horloge
//	this->th = std::thread(&GameClock::Update_Time, this); //YES
//
//}
//void GameClock::Pause_Clock()		// Arrête le temps
//{
//	this->running = false;	
//	if(th.joinable())
//		th.join();				// Stop le thread du timer
//}
//
//void GameClock::Unpause_Clock()		// Re-démarre le temps
//{
//	Start_Clock();	// Redémarre la clock
//}
// Affiche le temps à l'infinie!!!


//void GameClock::Infinite_Dsp(Coord crd, Colors clr)
//{
//	while (true) {
//		this->Dsp_Time(crd, clr);	// Affiche la clock à un certain endroit dans la console
//	//NO	MORE	std::this_thread::sleep_for(std::chrono::seconds(1));	// Attend une seconde entre chaque affichage!!!
//	}
//}

