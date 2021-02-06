#pragma once

/*TEMPLATE TIME*/

// Cette Queue est g�r� par un ring buffer au lieu d'une linked list

template <class T>		
class RingBufferQueue
{
	const int  MAX_Q_SIZE;		

	T *queue;		
	int head = 0;	// d�but
	int tail = 0;	// fin 
	int total = 0;	

	void Unregister();
public:
	void EMPTY_QUEUE(); // very dangerous here

	void Register(T msg);	
	bool Is_Full();

	int Get_Current_Size() { return total; }
	int Get_Head() { return head; }
	int Get_Tail() { return tail; }
	bool Get_Nth_Element(int index, T& data);

	T Extract();	// Prend 1 �l�ment de la liste � TOUT JAMAIS, IL N'EXISTERA PLUS, VOUS NE POUVEZ RIEN FAIRE, LE MONDE S'ENNUYERAS BEAUCOUP, D�SOLATION!

	RingBufferQueue(int maxSize) : MAX_Q_SIZE(maxSize){

		queue = new T[MAX_Q_SIZE];
	}
	~RingBufferQueue()
	{
		delete queue;	// Lib�ration
	}
};


// Cette Queue est g�r� par un simple array de dimension fixe qui d�cale chacun de ses �l�ments
// C'est en fait m�me pas une queue, puique le premier arriv� ne sera vraisemblablement pas premier servis
//*********************************************************************************************************

template <typename T>		
class FixedList
{
	const int  MAX_Q_SIZE;

	T* list;		
	int total = 0;	
public:
	int index = 0;	// L'it�rateur de la liste. oh boy. Ne pas mettre public.

	int Get_Total() { return total; }

	// GESTION DES �L�MENTS DE LA QUEUE
	bool Find_Element(const T& data, int& indexFound);
	bool Unregister(int index);	
	void Register(T data);		
	T Copy_Element(int index);	

	FixedList(int maxSize) : MAX_Q_SIZE(maxSize) {
		list = new T [MAX_Q_SIZE];
	}
	~FixedList() 
	{
		delete list;	
	}
};












// D�FINITIONS 
// // // // RING BUFFER

template <class T>
bool RingBufferQueue<T>::Is_Full()
{
	return (total == MAX_Q_SIZE);	
}

template <class T>		
void RingBufferQueue<T>::Unregister()	
{
	head = (head + 1) % MAX_Q_SIZE;	
	total--;
}

template <class T>		
void RingBufferQueue<T>::EMPTY_QUEUE()
{
	while (total)
		Unregister();
}

template <class T>
void RingBufferQueue<T>::Register(T element)	
{
	if (!Is_Full())
	{
		queue[tail] = element;			
		tail = (tail + 1) % MAX_Q_SIZE;		
		total++;
	}
	else
		return;
}
template <class T>
bool RingBufferQueue<T> ::Get_Nth_Element(int nthElement, T & data)		// prend le n-i�me �l�ment de la liste, en prenant en consid�ration la probl�matique du ring buffer
{
	static int realIndex;
	static int diffToMax;

	if (nthElement > total)		// �l�ment trop loin
		return false;

	if (head + nthElement > MAX_Q_SIZE)	// RAPPEL: head et tail sont en valeur d'array , nth et MAX_Q_SIZE ne startent pas � 0
	{
		diffToMax = MAX_Q_SIZE - head;
		realIndex = (nthElement - 1) - diffToMax;	// � partir de 0, on trouve le n-i�me �l�ment
	}
	else
		realIndex = (head - 1) + nthElement;

	data = queue[realIndex];
	return true;
}


template <class T>		
T RingBufferQueue<T>::Extract()			// Prend le premier �l�ment de la liste; First-in/First/Out
{
	if (total > 0)
	{
		T element = queue[head];
		Unregister();	
		return element;
	}
	else
		return -1;	// Retourne -1 si �a fail   // SI LA QUEUE PEUT CONTENIR L'�L�MENT -1,	CETTE IMPL�MENTATION NE FONCTIONNERA PAS
}



// D�FINITIONS 
// // // // FIXED LIST
template <typename T>
bool FixedList<typename T>::Unregister(int INDEX)	
{
	if (INDEX < total)			// je peux pas cancel un autre event que celui qui d�tient l'index. Ce qui veut dire que je peux uniquement cancel� un event dans sa propre m�thode, very bad
	{
		total--;	

		for (int i = INDEX; i < total; i++)		
			list[i] = list[i + 1];

		INDEX--;	// FIX PAS RAPPORT
		return true;
	}
	return false;	
}

template <typename T>
void FixedList<typename T>::Register(T data)	
{
	if (total < MAX_Q_SIZE) 	
	{
		list[total] = data;	
		total++;			
	}
}

template <typename T>
T FixedList<typename T>::Copy_Element(int index)	
{
	if (index < total)
		return list[index];
	else
		return -1;	
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
