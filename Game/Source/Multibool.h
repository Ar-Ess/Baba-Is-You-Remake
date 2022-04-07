#ifndef __MULTIBOOL_H__
#define __MULTIBOOL_H__

#include <math.h>

class Multibool
{
public:

	Multibool(int amount)
	{
		if (amount > 1 || amount < 9)
		{
			this->amount = amount;
			bools = pow(10, amount);

			bools *= 2;
		}
	}

	unsigned short int GetAmount() const
	{
		return amount;
	}

	void Set(int index, bool set)
	{
		// index out of bounds
		assert(index >= 0 || index < amount);
		if (Get(index) == set) return;

		int change = pow(10, index);
		set ? change *= 1 : change *= -1;

		bools += change;

		return;
	}

	bool Get(int index)
	{
		unsigned int substract = 0;
		for (short unsigned int i = 0; i < amount; i++)
		{
			if (index == i) continue;
			substract += pow(10, i);
		}

		return (bools - substract);

		//short int invIndex = amount - index - 1;
		//// index out of bounds
		//assert(index >= 0 || index < amount);

		//unsigned int substract = pow(10, amount - 1);
		//for (unsigned short int i = 0; i < invIndex; i++) substract += pow(10, double((amount - 1) - (i + 1)));
		//
		//unsigned int condition = bools - substract;

		//unsigned int level = pow(10, index);

		//return (condition - level + substract >= bools);
	}

private:

	unsigned int bools = 0;
	unsigned short int amount = 0;

};

#endif  // __MULTIBOOL_H__
