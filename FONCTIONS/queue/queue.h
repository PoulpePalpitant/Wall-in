#pragma once

/*TEMPLATE TIME*/

// Cette Queue est géré par un ring buffer au lieu d'une linked list

template <class T>		// Initialisation à un ring buffer
class RingBufferQueue
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T queue[20];	// La liste de tout les éléments Possiblement présents dans la queue
	int head = 0;	// début
	int tail = 0;	// fin 
	int total = 0;	// Nb d'éléments actuellement

	void Unregister();
public:
	void Register(T msg);	// Ajoute le message à la liste des message à traiter 
	T Extract();	// Prend 1 élément de la liste À TOUT JAMAIS, IL N'EXISTERA PLUS, VOUS NE POUVEZ RIEN FAIRE, LE MONDE S'ENNUYERAS BEAUCOUP, DÉSOLATION!

	//CONSTRUCTOR
	RingBufferQueue(int maxSize) : MAX_Q_SIZE(maxSize){

		queue = new T[MAX_Q_SIZE];
	}
	//	DESTRUCTOR
	~RingBufferQueue()
	{
		delete queue;	// Libération
	}
};


// Cette Queue est géré par un simple array de dimension fixe qui décale chacun de ses éléments
// C'est en fait même pas une queue, puique le premier arrivé ne sera vraisemblablement pas premier servis

template <typename T>		
class FixedQueue
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T* queue;		// La liste de tout les éléments Possiblement présents dans la queue
	int total = 0;	// Nb d'éléments actuellement
public:
	int index = 0;	// L'itérateur de la liste. oh boy. Ne pas mettre public

	// Useful Gets
	int Get_Total() { return total; }

	// GESTION DES ÉLÉMENTS DE LA QUEUE

	bool Unregister();	// Retir un élément de la queue
	void Register(T data);		// Ajoute le message à la liste des message à traiter 
	T Copy_Element(int index);	// Copy 1 élément de la list

	//CONSTRUCTOR
	FixedQueue(int maxSize) : MAX_Q_SIZE(maxSize) {
		//MAX_Q_SIZE = maxSize;
		queue = new T [MAX_Q_SIZE];
	}

	//	DESTRUCTOR
	~FixedQueue() 
	{
		delete queue;	// Libération
	}
};

// DÉFINITIONS 

// // // // RING BUFFER

template <class T>		// Initialisation à un ring buffer
void RingBufferQueue<T>::Unregister()	// retire le message de la queue
{
	head = (head + 1) % MAX_Q_SIZE;	// Retire l'élément au début de la queue
	total--;
}

template <class T>
void RingBufferQueue<T>::Register(T element)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (total < MAX_Q_SIZE)//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = element;			// Ajoute l'élément sur la tail au bout 
		tail = (tail + 1) % MAX_Q_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro
		total++;
	}
	else
		return;
}

template <class T>		// Initialisation à un ring buffer
T RingBufferQueue<T>::Extract()			// Prend le premier élément de la liste; First-in/First/Out
{
	if (total > 0)
	{
		T element = queue[head];
		Unregister();	// Retire l'élément de la queue
		return T;
	}
	else
		return -1;	// Retourne -1 si ça fail   // SI LA QUEUE PEUT CONTENIR L'ÉLÉMENT -1,	CETTE IMPLÉMENTATION NE FONCTIONNERA PAS
}



// // // // FIXED QUEUE

template <typename T>
bool FixedQueue<typename T>::Unregister()	// retire le message de la queue
{

	if (index < total)
	{
		total--;	// 1 de moins 

		for (int i = index; i < total; i++)		// Décale tout
			queue[i] = queue[i + 1];

		index--;	// FIX PAS RAPPORT
		return true;
	}
	return false;	// did not work
}

template <typename T>
void FixedQueue<typename T>::Register(T data)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (total < MAX_Q_SIZE) 	// Queue non pleine
	{
		queue[total] = data;	// Ajoute l'élément sur la tail au bout 
		total++;			
	}
}

template <typename T>
T FixedQueue<typename T>::Copy_Element(int index)	// Prend 1 élément de la list sans le détruire
{
	if (index < total)
		return queue[index];
	else
		return -1;	// Retourne aucune élément ne faisait partie de cet index
}

//	->

// if bool
//	returf false;