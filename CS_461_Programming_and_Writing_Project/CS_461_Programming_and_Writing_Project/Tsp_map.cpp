#include "Tsp_map.h"
#include <vector>

// default constructor
Tsp_map::Tsp_map() : cities({})
{
	// empty body
}

// add a city to the map at point p 
void Tsp_map::add(const Point & p)
{
	cities.push_back(p);
}

// add a city to the map at (x, y)
void Tsp_map::add(double x, double y)
{
	Point p(x, y);
	add(p);
}

// returns # of cities in the map
int Tsp_map::size() const
{
	return cities.size(); 
}

// calculate the distance between cities i and j 
double Tsp_map::dist_between(int i, int j) const
{
	// each city is represented by its index in the vector of cities
	return dist(cities[i], cities[j]);  // dist is from Point.
}

// calculate the score (total distance traveled) of the given route 
double Tsp_map::score(const vector<int>& route) const
{
	double result = dist_between(route[0], route[size() - 1]);
	for (int i = 1; i < size(); ++i) {                // i starts at 1, not 0!
		result += dist_between(route[i - 1], route[i]);
	}
	return result;
}

// return a starting route of all the cities in the order 0, 1, 2, 3,
// ...
vector<int> Tsp_map::get_default_route() const
{
	// a route, represented by a vector of ints, shows the order in which nodes 
	// are visited 
	vector<int> route(size());
	for (int i = 0; i < size(); ++i) {
		route[i] = i;
	}
	return route;
}






