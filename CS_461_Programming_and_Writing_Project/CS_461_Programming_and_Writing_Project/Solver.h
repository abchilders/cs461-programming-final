#pragma once
#include "Generator.h"

// neatly processes and prints out solutions for an algorithm
class Solver
{
private:
	// TODO: add member variables for score and benchmark
	Tsp_map input; 
	Route best_route;
public:
	// default constructor 
	Solver(); 

	// constructor 
	Solver(Tsp_map new_input); 

	// solves and neatly prints out the solution for one run of the given 
	// algorithm on our input
	// TODO: add benchmarking using chronos 
	void solve(Route(*algorithm)(Tsp_map& input)); 
};

