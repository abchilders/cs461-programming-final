#include "Solver.h"
#include <chrono> 
#include <iostream>

using namespace std::chrono; 

// default constructor
Solver::Solver() 
{
	// empty body
}

void Solver::solve(Tsp_map& input, Route(*algorithm)(Tsp_map&)) 
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
	cout << "Time taken: " << benchmark << " ms" << endl; 
	cout << "Distance traveled on solution: " << score << endl; 
}
