#pragma once
#include "Tsp_map.h"

// used to produce a random graph for the problem
class Generator
{
private:
	int seed;
	int size;
public:
	// default constructor
	Generator();

	// constructor
	Generator(int new_seed, int new_size);

	// gets size
	int getSize();

	// sets seed 
	void setSeed(int new_seed);

	// sets size
	void setSize(int new_size);

	// gets user input for seed and size 
	void getUserInput();

	// runs the passed-in algorithm and outputs the solution 
	void runAlgorithm(void(*algorithm)(Tsp_map&), Tsp_map cities);
};

