// based on Toby Donaldson's solutions to the traveling salesperson problem, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/tsp_example.html

#include <algorithm>
#include <iostream>
#include <time.h>
#include <unordered_map>
#include "Generator.h"
#include "Solver.h"

using namespace std; 

typedef Route(*Algorithm)(Tsp_map&);

// the number of runs to do -- CHANGE THIS TO VARY THE NUMBER OF GRAPHS SOLVED
const int TOTAL_RUNS = 20; 
const int MAX_RANDOM_GUESSES = 500000; 

// brute force algorithm for TSP 
// outputs the best solution for the input map 
Route brute_force_solver(Tsp_map& cities); 

// Monte Carlo randomized algorithm for TSP 
// randomly generates up to num_guesses permutations and selects the best 
// solution out of those guesses
Route random_guesser(Tsp_map& cities); 

// input: takes a number of runs to do (so each run will be done on a map with 
//  one more city than the last one, from 1 to number)
// side effect: runs the given algorithm on the problem with increasing sizes, 
//  then outputs the algorithm used, size, and runtime of each run to the 
//  screen 
void dataCollection(int total_runs, unordered_map<string, Algorithm> algorithms);

int main(void) 
{   
    // set up a list of solution algorithms  
    unordered_map<string, Algorithm> algorithms{}; 
    algorithms["Brute force"] = &brute_force_solver; 
    algorithms["Randomized Monte Carlo"] = &random_guesser; 

    // run data collection using all algorithms 
    dataCollection(TOTAL_RUNS, algorithms); 

	return 0; 
}
 
Route brute_force_solver(Tsp_map& cities) 
{
    // get the default route for this TSP map-- a starting list of all cities 
    Route route(cities.get_default_route());

    // initialize the best score and best route to this initial route 
    double best_score = cities.score(route);
    Route best_route(route);

    // then try all possible permutations of this list of cities on the route
    while (next_permutation(route.begin() + 1, route.end())) {
        double s = cities.score(route);
        
        // if this route has a shorter distance than any previous one, we 
        // have a new best route 
        if (s < best_score) 
        {
            best_score = s;
            best_route = route;
        }
    }
    return best_route;
}

Route random_guesser(Tsp_map& cities) 
{
    // get the default route for this TSP map-- a starting list of all cities 
    Route route(cities.get_default_route());

    // initialize the best score and best route to this initial route 
    double best_score = cities.score(route);
    Route best_route(route);

    // known runtime-- randomly select num_guesses permutations of the map
    for (int i = 0; i < MAX_RANDOM_GUESSES; ++i) 
    {
        // randomly order the cities on the route
        random_shuffle(route.begin() + 1, route.end());
        double s = cities.score(route);

        // if this route has a shorter distance than any previous one, we 
        // have a new best route
        if (s < best_score) 
        {
            best_score = s;
            best_route = route;
        }
    }
    return best_route;
}

void dataCollection(int total_runs, unordered_map<string, Algorithm> algorithms)
{
    // get seed from user 
    // prompt user for seed
    char enter_seed;
    int new_seed = time(NULL);
    cout << "Would you like to enter a custom seed? (y/n) ";
    cin >> enter_seed;
    if (enter_seed == 'y')
    {
        cout << "Enter an integer: ";
        cin >> new_seed;
    }
    cout << endl; 

    // create problem generator on this seed
    Generator generator; 
    generator.setSeed(new_seed); 

    // we want to run the algorithms on all inputs from size 1 to size 
    // total_runs
    for (int i = 1; i <= total_runs; i++)
    {
        // generate the TSP map for this problem size
        generator.setSize(i); 
        Tsp_map input = generator.generateTspMap(); 
        cout << "MAP SIZE " << i << endl; 
        cout << "======================" << endl << endl; 

        // then run the given algorithms on this same problem set 
        for (auto algorithm : algorithms)
        {
            cout << algorithm.first << "-- " << endl; 
            Solver::solve(input, algorithm.second);
            cout << endl;
        }
    }
}
