#pragma once

/*TEMPLATE TIME*/

// Cette Queue est géré par un ring buffer au lieu d'une linked list

template <class T>		// Initialisation à un ring buffer
class RingBufferQueue
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T *queue;	// La liste de tout les éléments Possiblement présents dans la queue
	int head = 0;	// début
	int tail = 0;	// fin 
	int total = 0;	// Nb d'éléments actuellement

	void Unregister();
public:
	void Register(T msg);	// Ajoute le message à la liste des message à traiter 
	bool Is_Full();

	int Get_Current_Size() { return total; }
	int Get_Head() { return head; }
	int Get_Tail() { return tail; }
	bool Get_Nth_Element(int index, T& data);

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
class FixedList
{
	const int  MAX_Q_SIZE;		// La dimension max de la queue

	T* list;		// La liste de tout les éléments Possiblement présents dans la queue
	int total = 0;	// Nb d'éléments actuellement
public:
	int index = 0;	// L'itérateur de la liste. oh boy. Ne pas mettre public

	// Useful Gets
	int Get_Total() { return total; }

	// GESTION DES ÉLÉMENTS DE LA QUEUE
	bool Find_Element(const T& data, int& indexFound);

	bool Unregister(int index);	// Retir un élément de la queue
	void Register(T data);		// Ajoute le message à la liste des message à traiter 
	T Copy_Element(int index);	// Copy 1 élément de la list

	//CONSTRUCTOR
	FixedList(int maxSize) : MAX_Q_SIZE(maxSize) {
		//MAX_Q_SIZE = maxSize;
		list = new T [MAX_Q_SIZE];
	}

	//	DESTRUCTOR
	~FixedList() 
	{
		delete list;	// Libération
	}
};












// DÉFINITIONS 

// // // // RING BUFFER

template <class T>
bool RingBufferQueue<T>::Is_Full()
{
	return (total == MAX_Q_SIZE);	//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
}

template <class T>		// Initialisation à un ring buffer
void RingBufferQueue<T>::Unregister()	// retire le message de la queue
{
	head = (head + 1) % MAX_Q_SIZE;	// Retire l'élément au début de la queue
	total--;
}

template <class T>
void RingBufferQueue<T>::Register(T element)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (!Is_Full())//((tail + 1) % QUEUE_SIZE != head)	// Queue non pleine
	{
		queue[tail] = element;			// Ajoute l'élément sur la tail au bout 
		tail = (tail + 1) % MAX_Q_SIZE;		// Si On atteint le max, l'ajout sera fait sur l'élément zéro
		total++;
	}
	else
		return;
}
template <class T>
bool RingBufferQueue<T> ::Get_Nth_Element(int nthElement, T & data)		// prend le n-ième élément de la liste, en prenant en considération la problématique du ring buffer
{
	static int realIndex;
	static int diffToMax;

	if (nthElement > total)		// élément trop loin
		return false;

	if (head + nthElement > MAX_Q_SIZE)	// RAPPEL: head et tail sont en valeur d'array , nth et MAX_Q_SIZE ne startent pas à 0
	{
		diffToMax = MAX_Q_SIZE - head;
		realIndex = (nthElement - 1) - diffToMax;	// À partir de 0, on trouve le n-ième élément
	}
	else
		realIndex = (head - 1) + nthElement;

	data = queue[realIndex];
	return true;
}


template <class T>		// Initialisation à un ring buffer
T RingBufferQueue<T>::Extract()			// Prend le premier élément de la liste; First-in/First/Out
{
	if (total > 0)
	{
		T element = queue[head];
		Unregister();	// Retire l'élément de la queue
		return element;
	}
	else
		return -1;	// Retourne -1 si ça fail   // SI LA QUEUE PEUT CONTENIR L'ÉLÉMENT -1,	CETTE IMPLÉMENTATION NE FONCTIONNERA PAS
}



// // // // FIXED LIST

template <typename T>
bool FixedList<typename T>::Unregister(int INDEX)	// retire le message de la queue
{
	if (INDEX < total)			// je peux pas cancel un autre event que celui qui détient l'index. Ce qui veut dire que je peux uniquement cancelé un event dans sa propre méthode, very bad
	{
		total--;	// 1 de moins 

		for (int i = INDEX; i < total; i++)		// Décale tout
			list[i] = list[i + 1];

		INDEX--;	// FIX PAS RAPPORT
		return true;
	}
	return false;	// did not work
}

template <typename T>
void FixedList<typename T>::Register(T data)	// Ajoute le message à la liste des message à traiter pour ce cycle
{
	if (total < MAX_Q_SIZE) 	// Queue non pleine
	{
		list[total] = data;	// Ajoute l'élément sur la tail au bout 
		total++;			
	}
}

template <typename T>
T FixedList<typename T>::Copy_Element(int index)	// Prend 1 élément de la list sans le détruire
{
	if (index < total)
		return list[index];
	else
		return -1;	// Retourne aucune élément ne faisait partie de cet index
}



template <typename T>
bool FixedList<typename T>::Find_Element(const T& data, int& indexFound)
{
	for (int i = 0; i < total; i++)
	{
		if (list[i] == data)
		{
			indexFound = i;
			return true;
		}
	}

	return false;
}

//	->

// if bool
//	returf false;