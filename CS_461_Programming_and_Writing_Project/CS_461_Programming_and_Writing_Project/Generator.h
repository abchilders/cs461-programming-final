#pragma once
#include "Tsp_map.h"

// used to produce a random graph for the problem
class Generator
{
private:
	int seed;
	int size;
	Tsp_map input; 

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

	// produces a random traveling salesman map, to be inputted into one of the 
	// solution algorithms 
	void generateTspMap();
};

