#include "Solver.h"
#include <chrono> 
#include <iostream>

using namespace std::chrono; 

// default constructor
Solver::Solver() : input(Tsp_map::Tsp_map()), best_route({})
{
	// empty body
}

// constructor
Solver::Solver(Tsp_map new_input) : input(new_input), best_route({})
{
	// empty body
}

void Solver::solve(Route(*algorithm)(Tsp_map& input))
{
	// set up the timer 
	system_clock::time_point start; 
	system_clock::time_point end; 

	// start the benchmark 
	start = system_clock::now();

	// solve the given input 
	Route solution = algorithm(input); 

	// end benchmark
	end = system_clock::now(); 
	long long benchmark = duration_cast<milliseconds>(end - start).count();
	
	// get the score for this route 
	double score = input.score(solution); 

	// output results 
	// TODO: figure out how to output the Tsp_map itself, too
}
