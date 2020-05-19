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
const int TOTAL_RUNS = 13; 
const int MAX_RANDOM_GUESSES = 120000; 

// brute force algorithm for TSP
// outputs the best solution for the input map
Route brute_force_solver(Tsp_map& cities);

// Monte Carlo randomized algorithm for TSP
// randomly generates up to num_guesses permutations and selects the best
// solution out of those guesses
Route random_guesser(Tsp_map& cities);

// input: takes a number of runs to do (so each run will be done on a map with
//  one more city than the last one, from 1 to number)
// side effect: runs the given algorithms on the problem with increasing sizes,
//  then outputs the algorithm used, size, and runtime of each run to the
//  screen
void dataCollection(int total_runs, unordered_map<string, Algorithm> algorithms);

// test suite to ensure that boundary conditions don't cause program failure
void testSuite();

int main(void) 
{   
    // TEST SUITE 
    char run_test = 'n'; 
    cout << "Run test suite? (y/n) "; 
    cin >> run_test; 
    if (run_test == 'y')
    {
        testSuite();
    }

    // DATA COLLECTION
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

    // if the map has no cities, there doesn't exist any route, really
    if (cities.size() == 0)
    {
        return best_route;
    }

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

    // if the map has no cities, there doesn't exist any route, really
    if (cities.size() == 0)
    {
        return best_route;
    }

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
    // verify number of runs and algorithms given 
    if (total_runs < 1)
    {
        cout << "Invalid number of runs given. Please enter one or more." << endl; 
        return; 
    }

    if (algorithms.size() < 1)
    {
        cout << "No algorithms given to run." << endl; 
        return; 
    }

    // get seed from user 
    // prompt user for seed
    // NOTE: using the same seed every time produces the same maps each time; 
    //  opting not to enter a seed causes it to be seeded from the current time
    //  --> randomly generates new maps 
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

/* Test suite below. */
void testSuite()
{
    bool all_tests_passed = true; 

    // tests generator handling of size 0 
    Generator test_gen; 
    Tsp_map test_map = test_gen.generateTspMap(); 

    cout << "* testing generator that generates a map of size 0: "; 
    // a Generator that is not given a size should create a map with 0 nodes
    if (test_map.size() == 0)
    {
        cout << "ok"; 
    }
    else
    {
        cout << "FAILED"; 
        all_tests_passed = false; 
    }
    cout << endl; 
    
    // testing algorithms when given empty Tsp_map as input-- 0 nodes 
    cout << "* testing brute_force_solver on an empty map: ";
    Route brute_force_soln = brute_force_solver(test_map); 
    // the optimal route for a map with 0 nodes should also have 0 items 
    if (brute_force_soln.size() == 0)
    {
        cout << "ok"; 
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl; 

    cout << "* testing random_guesser on an empty map: ";
    Route random_soln = random_guesser(test_map);
    // the optimal route for a map with 0 nodes should also have 0 items 
    if (random_soln.size() == 0)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl; 
    
    // Testing Tsp_map functions on empty or invalid input 
    
    // set up a second Tsp_map with nodes, an empty route, and invalid routes 
    Tsp_map map_with_nodes; 
    // adding nodes to the map using both versions of add()
    Point test_point(2, 1);  
    map_with_nodes.add(test_point); 
    map_with_nodes.add(3, 4);
    map_with_nodes.add(6, 6); 

    Route empty_route = {}; 
    Route too_few_nodes_route = { 0, 1 };
    Route too_many_nodes_route = { 0, 3, 2, 4, 1 }; 
    Route contains_nonexistent_nodes_route = { 0, 2, 12 }; 

    cout << "* testing score() on an empty route-- " << endl;
    cout << "\t* empty map: "; 
    double test_score_empty = test_map.score(empty_route); 
    // the score is invalid, so it should be -1 
    if (test_score_empty == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl; 
    cout << "\t* map with nodes: "; 
    double test_score_nonempty = map_with_nodes.score(empty_route); 
    // the score is invalid, so it should be -1 
    if (test_score_nonempty == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl; 

    cout << "* testing score() on a route with too few nodes: "; 
    double test_score = map_with_nodes.score(too_few_nodes_route); 
    // invalid TSP route-- the problem requires all nodes to be visited 
    if (test_score == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl;

    cout << "* testing score() on a route with too many nodes-- " << endl;
    cout << "\t* empty map: ";
    // invalid TSP route-- this map has no nodes
    if (test_score == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl;
    cout << "\t* map with nodes: "; 
    test_score = map_with_nodes.score(too_many_nodes_route);
    // invalid TSP route-- each node must be in the map, and must be visited at
    // most once 
    if (test_score == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl;

    cout << "* testing score() on a route with invalid nodes: ";
    test_score = map_with_nodes.score(contains_nonexistent_nodes_route);
    // invalid TSP route-- each node must be in the map
    if (test_score == -1)
    {
        cout << "ok";
    }
    else
    {
        cout << "FAILED";
        all_tests_passed = false;
    }
    cout << endl;

    cout << "* testing distBetween() with invalid nodes: ";
    double dist_between = map_with_nodes.dist_between(2, 3);
    // node 3 doesn't exist in map_with_nodes, so we should get an invalid 
    // response back 
    if (dist_between == -1)
    {
        cout << "ok"; 
    }
    else
    {
        cout << "FAILED"; 
        all_tests_passed = false;
    }
    cout << endl; 

    cout << endl << "TEST RESULTS: " << endl; 
    if (all_tests_passed)
    {
        cout << "All tests with non-void output passed." << endl; 
    }
    else
    {
        cout << "!!! At least one test failed!" << endl; 
    }
    cout << "Please inspect the remaining tests visually for correctness.";
    cout << endl << endl; 

    cout << "testing solver--" << endl; 
    cout << "* expected output: distance traveled = -1: " << endl;
    Solver::solve(test_map, &brute_force_solver);
    cout << endl; 

    cout << "testing dataCollection()--" << endl; 
    
    cout << "* expected: output showing invalid number of runs given" << endl; 
    unordered_map<string, Algorithm> algorithms{};
    dataCollection(0, algorithms); 

    cout << "* expected: output showing no algorithms given" << endl;
    dataCollection(1, algorithms); 
    cout << endl; 
}
