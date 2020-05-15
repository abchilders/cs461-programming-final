// based on Toby Donaldson's solutions to the traveling salesperson problem, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/tsp_example.html

#include <algorithm>
#include <iostream>
#include <time.h>
#include "Tsp_map.h"

using namespace std; 

typedef vector<int> Route; 

void brute_force_solver(Tsp_map& cities) {
    // get the default route for this TSP map-- a starting list of all cities 
    Route route(cities.get_default_route());

    // initialize the best score and best route to this initial route 
    double best_score = cities.score(route);
    Route best_route(route);
    cout << route << "  score = " << best_score << endl;

    // then try all possible permutations of this list of cities on the route
    while (next_permutation(route.begin() + 1, route.end())) {
        double s = cities.score(route);
        // if this route has a shorter distance than any previous one, we 
        // have a new best route 
        if (s < best_score) {
            best_score = s;
            best_route = route;
        }

        cout << route << "  score = " << s << endl;
    } 

    cout << "best route: " << best_route
        << "\nscore = " << best_score << endl;
}

int main(void) 
{
    // initialize random seed and list of cities
    srand(10000); 
    Tsp_map cities;

    // run the brute force algorithm on a series of 1 - i cities
    for (int i = 0; i < 8; i++)
    {
        cout << "TSP on " << i << "cities: " << endl; 

        // add another randomly generated city to the list and re-run
        cities.add(rand() % 100, rand() % 100); 
    }

    // 3. call the algorithm you wish to use on the map you created
    brute_force_solver(cities);

	return 0; 
}