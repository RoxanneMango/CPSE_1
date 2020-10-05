#ifndef SET_H
#define SET_H

#include <iostream>
#include <array>

template< typename D, int S >
class Set
{
private:
	std::array<D, S> array = {0};
	bool availableSpaces[S];
public:
	Set()
	{
		for(int i = 0; i < S; ++i)
		{
			availableSpaces[i] = true;
		}
	}
	void add(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					return;
				}
			}
		}
		for(unsigned int i = 0; i < S; ++i)
		{
			if(availableSpaces[i])
			{
				array[i] = num;
				availableSpaces[i] = false;
				return;
			}
		}
	}
	void remove(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					array[i] = 0;
					availableSpaces[i] = true;
					return;
				}
			}
		}
	}
	bool contains(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					return true;
				}
			}
		}
		return false;
	}
	D max()
	{
		D x = 0;
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				x = array[i];
				break;
			}
		}
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] > x)
				{
					x = array[i];
				}
			}
		}
		return x;
	}	
	void print()
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				std::cout << array[i] << ' ';
			}
		}
	}
};

#endif // SET_H