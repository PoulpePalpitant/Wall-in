#pragma once

#include <chrono>

//////////////////////////////////////////////////////////////////////////
// tentative de faire comme dans la vidéo du dude
class TimerOP {
	static TimerOP* pInstance;						// instance du timer
	std::chrono::system_clock::time_point startTime;	// Pour quand tu reset?
	std::chrono::duration<float> deltaTime;
	float timeScale;


public:
	static TimerOP* Set_Instance();
	static void Release();
	void Reset_Timer();				// reset le timer à starttime

	float Get_Delta_Time();
	float Get_Time_Scale();					// Get le timeScale
	void Set_Time_Scale(float t = 1.0f);	// Permet de set le time scale

	void Tick();							// "Tick" le timer forward

	TimerOP();//constructor
	~TimerOP();// Destructor
	//////////////////////////////////////////////////////////////////////////
};


// La clock du dude    #include "timerOp"

//bool isRunning = true;
//float frameRate = 60.0f;

//float letempsquetuveuxMesurer = 0.0f;	// f is for float, convertit la valeur en float au lieu d'un double quand tu écrit avec des décimales
//int frames = 0;
//int seconds;

//while (isRunning)	// Cette loop sert de gameloop. Chaque tick représente une frame. si tu veux bouger quekchose, ta juste à multiplier la vitesse de ce quek chose par le temps écoulé entre chaque tick(deltatime)
//{					// Dans la console windows par contre, tu peux pas bouger les choses pixel par pixel, mais par case de charactère. J'ai alors pas besoin d'autant de précision, puisque tout les mouvements ont
					// Déjà l'air saccadé!!
	//TimerOp* Timer = TimerOp::Set_Instance();
	//Timer->Tick();				// Durée entre End-Start


	//letempsquetuveuxMesurer += Timer->Get_Delta_Time();	// Delta time est en seconde!!!
	//Delta time describes the time difference between the previous frame that was drawn and the current frame. // Le temps en seconde entre chaque frames!!



	//// ou affiche le framerate
	//if (Timer->Get_Delta_Time() >= 1 / frameRate) { // Si le DeltaTime atteint 60 fps			

	//	Timer->Reset_Timer();
	//	cout << 1 / Timer->Get_Delta_Time() << endl;// << letempsquetuveuxMesurer << endl << endl;	// Affiche le temps écoulé entre chaque frame?
	//}	
//}
