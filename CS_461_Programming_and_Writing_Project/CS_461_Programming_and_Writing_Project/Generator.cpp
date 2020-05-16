#include "Generator.h"
#include <time.h>
#include <iostream>
#include <string>

// default constructor
Generator::Generator() : seed(time(NULL)), size(0)
{
	// empty body
}

// constructor
Generator::Generator(int new_seed, int new_size) : seed(new_seed), size(new_size)
{
	// empty body
}

// gets size
int Generator::getSize()
{
	return size; 
}

// sets seed
void Generator::setSeed(int new_seed)
{
	seed = new_seed; 
}

// sets size
void Generator::setSize(int new_size)
{
	size = new_size; 
}

// produces a random traveling salesman map, to be inputted into one of the 
// solution algorithms 
void Generator::generateTspMap()
{
	// prompt user for seed
	char enter_seed; 
	int new_seed = time(NULL); 
	cout << "Would you like to enter a seed? (y/n) "; 
	cin >> enter_seed; 
	if (enter_seed == 'y')
	{
		cout << "Enter an integer seed: "; 
		cin >> new_seed;  
	}
	seed = new_seed; 
	srand(seed); 

	// generate a random map using given size and seed  
	for (int i = 0; i < size; i++)
	{
		int x = rand() % 100; 
		int y = rand() % 100; 
		cout << "i = " << i << ": adding city at (" << x << ", " << y << ")" << endl; 
		input.add(x, y); 
	}
	return; 
}
