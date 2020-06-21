
#include "timerOP.h"


extern long double gLvlTime = 0;	// test de temps du lvl 

/* MA VERSION STatic*/
 std::chrono::system_clock::time_point GameLoopClock::startTime = std::chrono::system_clock::now();	// Pour quand tu reset?
 float GameLoopClock::timeScale = 1.0f;;
 std::chrono::duration<float> GameLoopClock::deltaTime = std::chrono::duration<float>(0.0f);
 bool GameLoopClock::pause = false;

 void GameLoopClock::UPD_Total_Time()
 {
	 if (!pause) 
		 gLvlTime += GameLoopClock::Get_Delta_Time();	// Update du temps actuel

 }

// reset Start time
void GameLoopClock::Reset_Timer() {
	startTime = std::chrono::system_clock::now();
}

// Va chercher delta time c'est la durée qui sépare chaque tick de la clock je crois
float GameLoopClock::Get_Delta_Time() {
	return deltaTime.count();
}

// set le timeScale
void GameLoopClock::Set_Time_Scale(float t  /* = 1.of*/)
{
	timeScale = t;
}

// Get timescale
float GameLoopClock::Get_Time_Scale()
{
	return timeScale;
}

// ASSIGNE LE DELTA TIME
void GameLoopClock::Tick() {
	deltaTime = std::chrono::system_clock::now() - startTime;	// La différence entre le temps now et le start time
}




// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// clock du dude sur les internet, VERSION ORIGINALE
//
//
//TimerOP* TimerOP::pInstance = NULL;	// pointe sur null
//
//// Créer un nouveau timer, au lieu d'un objet timer, il ne peut y avoir qu'une seule instance étant donné que c'est static
//TimerOP* TimerOP::Set_Instance()
//{
//	if (pInstance == NULL)
//		pInstance = new TimerOP();
//
//	return pInstance;
//
//}
//
//// Sert à delete le Timer pointé par instance
//void TimerOP::Release()
//{
//	delete pInstance;
//	pInstance = NULL;
//}
//
//// Constructor
//TimerOP::TimerOP() {
//	Reset_Timer();
//	timeScale = 1.0f;
//	deltaTime = std::chrono::duration<float>(0.0f);	// Initialisation de précaution
//}
////Destructor
//TimerOP::~TimerOP()
//{}
//
//// reset Start time
//void TimerOP::Reset_Timer() {
//	startTime = std::chrono::system_clock::now();
//}
//
//// Va chercher delta time c'est la durée qui sépare chaque tick de la clock je crois
//float TimerOP::Get_Delta_Time() {
//	return deltaTime.count();
//}
//
//// set le timeScale
//void TimerOP::Set_Time_Scale(float t  /* = 1.of*/)
//{
//	timeScale = t;
//}
//
//// Get timescale
//float TimerOP::Get_Time_Scale()
//{
//	return timeScale;
//}
//
//// ASSIGNE LE DELTA TIME
//void TimerOP::Tick() {
//	deltaTime = std::chrono::system_clock::now() - startTime;	// La différence entre le temps now et le start time
//}
//


//
//
//// La clock du dude    #include "timerOp"
//
//bool isRunning = true;
//float frameRate = 60.0f;
//float lag = 0.0f;
//double letempsquetuveuxMesurer = 0.0;	// f is for float, convertit la valeur en float au lieu d'un double quand tu écrit avec des décimales
//int frames = 0;
//int seconds;
//
//TimerOP* Timer = TimerOP::Set_Instance();
//
//while (isRunning)	// Cette loop sert de gameloop. Chaque tick représente une frame. si tu veux bouger quekchose, ta juste à multiplier la vitesse de ce quek chose par le temps écoulé entre chaque tick(deltatime)
//{					// Dans la console windows par contre, tu peux pas bouger les choses pixel par pixel, mais par case de charactère. J'ai alors pas besoin d'autant de précision, puisque tout les mouvements ont
//	Timer->Tick();	// Déjà l'air saccadé!!
//					// Durée entre End-Start
//	//Delta time describes the time difference between the previous frame that was drawnand the current frame. // Le temps en seconde entre chaque frames!!
//	letempsquetuveuxMesurer += Timer->Get_Delta_Time();	// Delta time est en seconde!!!
//
//	//Detect_Input();		// Détect les inputs mah dude0
//	//Update_Game();		// Update le jeu mah dude
//	cout << Timer->Get_Delta_Time() << "\t \t \n";
//
//	// ou affiche le framerate
//	/*if (Timer->Get_Delta_Time() >= 1 / frameRate) { // Si le DeltaTime atteint 60 fps
//		lag = Timer->Get_Delta_Time() - 1 / frameRate;
//		Timer->Reset_Timer();
//
//		cout << Timer->Get_Delta_Time() << "\t \t";
//		cout << 1 / Timer->Get_Delta_Time() << "\t \t";// << letempsquetuveuxMesurer << endl << endl;	// Affiche le temps écoulé entre chaque frame?
//		cout << letempsquetuveuxMesurer << endl;
//		//std::this_thread::sleep_for(std::chrono::milliseconds(lag);	// On LIMITE  le framerate à 60 fps
//		//Sleep(lag * 1000);
//		//this_thread::sleep_for(chrono::seconds(lag));
//	}*/
//}



