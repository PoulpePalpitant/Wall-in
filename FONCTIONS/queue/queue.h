#pragma once

/*TEMPLATE TIME*/

// Cette Queue est g�r� par un ring buffer au lieu d'une linked list

template <class T>		// Initialisation � un ring buffer
class RingBufferQueue
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T queue[20];	// La liste de tout les �l�ments Possiblement pr�sents dans la queue
	int head = 0;	// d�but
	int tail = 0;	// fin 
	int total = 0;	// Nb d'�l�ments actuellement

	void Unregister();
public:
	void Register(T msg);	// Ajoute le message � la liste des message � traiter 
	T Extract();	// Prend 1 �l�ment de la liste � TOUT JAMAIS, IL N'EXISTERA PLUS, VOUS NE POUVEZ RIEN FAIRE, LE MONDE S'ENNUYERAS BEAUCOUP, D�SOLATION!

	//CONSTRUCTOR
	RingBufferQueue(int maxSize) : MAX_Q_SIZE(maxSize){

		queue = new T[MAX_Q_SIZE];
	}
	//	DESTRUCTOR
	~RingBufferQueue()
	{
		delete queue;	// Lib�ration
	}
};


// Cette Queue est g�r� par un simple array de dimension fixe qui d�cale chacun de ses �l�ments
// C'est en fait m�me pas une queue, puique le premier arriv� ne sera vraisemblablement pas premier servis

template <typename T>		
class FixedQueue
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T* queue;		// La liste de tout les �l�ments Possiblement pr�sents dans la queue
	int total = 0;	// Nb d'�l�ments actuellement
public:
	int index = 0;	// L'it�rateur de la liste. oh boy. Ne pas mettre public

	// Useful Gets
	int Get_Total() { return total; }

	// GESTION DES �L�MENTS DE LA QUEUE

	bool Unregister();	// Retir un �l�ment de la queue
	void Register(T data);		// Ajoute le message � la liste des message � traiter 
	T Copy_Element(int index);	// Copy 1 �l�ment de la list

	//CONSTRUCTOR
	FixedQueue(int maxSize) : MAX_Q_SIZE(maxSize) {
		//MAX_Q_SIZE = maxSize;
		queue = new T [MAX_Q_SIZE];
	}

	//	DESTRUCTOR
	~FixedQueue() 
	{
		delete queue;	// Lib�ration
	}
};

// D�FINITIONS 

// // // // RING BUFFER

template <class T>		// Initialisation � un ring buffer
void RingBufferQueue<T>::Unregister()	// retire le message de la queue
{
	head = (head + 1) % MAX_Q_SIZE;	// Retire l'�l�ment au d�but de la queue
	total--;
}

template <class T>
void RingBufferQueue<T>::Register(T element)	// Ajoute le message � la liste des message � traiter pour ce cycle
{
	if (total < MAX_Q_SIZE)//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = element;			// Ajoute l'�l�ment sur la tail au bout 
		tail = (tail + 1) % MAX_Q_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'�l�ment z�ro
		total++;
	}
	else
		return;
}

template <class T>		// Initialisation � un ring buffer
T RingBufferQueue<T>::Extract()			// Prend le premier �l�ment de la liste; First-in/First/Out
{
	if (total > 0)
	{
		T element = queue[head];
		Unregister();	// Retire l'�l�ment de la queue
		return T;
	}
	else
		return -1;	// Retourne -1 si �a fail   // SI LA QUEUE PEUT CONTENIR L'�L�MENT -1,	CETTE IMPL�MENTATION NE FONCTIONNERA PAS
}



// // // // FIXED QUEUE

template <typename T>
bool FixedQueue<typename T>::Unregister()	// retire le message de la queue
{

	if (index < total)
	{
		total--;	// 1 de moins 

		for (int i = index; i < total; i++)		// D�cale tout
			queue[i] = queue[i + 1];

		index--;	// FIX PAS RAPPORT
		return true;
	}
	return false;	// did not work
}

template <typename T>
void FixedQueue<typename T>::Register(T data)	// Ajoute le message � la liste des message � traiter pour ce cycle
{
	if (total < MAX_Q_SIZE) 	// Queue non pleine
	{
		queue[total] = data;	// Ajoute l'�l�ment sur la tail au bout 
		total++;			
	}
}

template <typename T>
T FixedQueue<typename T>::Copy_Element(int index)	// Prend 1 �l�ment de la list sans le d�truire
{
	if (index < total)
		return queue[index];
	else
		return -1;	// Retourne aucune �l�ment ne faisait partie de cet index
}

//	->

// if bool
//	returf false;