#pragma once
#include "Generator.h"

// neatly processes and prints out solutions for an algorithm
class Solver
{
public:
	// default constructor 
	Solver(); 

	// solves and neatly prints out the solution for one run of the given 
	// algorithm on our input 
	static void solve(Tsp_map& input, Route(*algorithm)(Tsp_map&)); 
};

