#include "Generator.h"
#include <time.h>
#include <iostream>

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

// gets user input for seed and size
void Generator::getUserInput()
{
	// prompt user for seed
	char enter_seed; 
	int new_seed = time(NULL); 
	cout << "Would you like to enter a seed? (y/n)"; 
	cin >> enter_seed; 
	if (enter_seed == 'y')
	{
		cout << "Enter an integer seed: "; 
		cin >> new_seed;  
	}
	seed = new_seed; 

	// prompt user for size of problem
	int nodes; 
	cout << "How many nodes to put in the graph? (try a number between 1 and 10): "; 
	cin >> nodes; 
	size = nodes; 

	return; 
}

// runs the passed-in algorithm and outputs the solution
void Generator::runAlgorithm(void(*algorithm)(Tsp_map&), Tsp_map cities)
{
	algorithm(cities); 
	// TODO: make the algorithm return the solution as a vector<int>, 
	// and then output solution in this function 
}
