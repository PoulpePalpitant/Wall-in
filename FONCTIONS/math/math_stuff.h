#pragma once 


using C_D = unsigned int;	// Un countdown qui se décrémente jusqu'à zéro


class Countdown
{
private:
	C_D counter = 0;
	int countStart = 5;

public:
	void Reset() { counter = countStart; }
	
	bool Set(int count)
	{
		if (count < 0)
			return false;
		else
		{
			countStart = count;
			Reset();
			return true;
		}
	}

	bool Count()
	{
		if (--counter == 0)	// Quand finis, retourne vrai
		{
			Reset();
			return true;
		}
		else
			return false;
	}

	int Get_Count() { return counter; };
};