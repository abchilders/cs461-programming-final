// based on the Tsp_map class by Toby Donaldson, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/tsp_example.html

#include <vector>
#include <unordered_map>
#include "Tsp_map.h"
#include "Point.h"

typedef vector<int> Route;

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

// returns the list of cities in the map
vector<Point> Tsp_map::getCities()
{
	return cities; 
}

// calculate the distance between cities i and j 
double Tsp_map::dist_between(int i, int j)
{
	// check if i and j are valid cities in the map  
	if ((i >= cities.size()) || (j >= cities.size()))
	{
		return -1; 
	}

	// each city is represented by its index in the vector of cities 
	double distance = dist(cities[i], cities[j]);  // dist is from Point.
	return distance; 
}

// calculate the score (total distance traveled) of the given route 
double Tsp_map::score(Route& route)
{
	// Check if route is valid: 
	// the route must have the same number of cities as the Tsp_map does,
	//	and the map must have at least one city in it 
	if ((route.size() != cities.size()) || (cities.size() == 0))
	{
		return -1; 
	}

	// initialize hashtable representing all the cities that should be on the 
	//	route for this map 
	//  key = city, value = flag denoting a node's presence 
	unordered_map<int, bool> expected_cities_seen{}; 
	for (int i = 0; i < cities.size(); i++)
	{
		expected_cities_seen[i] = false; 
	}
	// then check if all the expected cities are in the Route 
	for (auto city : route)
	{
		expected_cities_seen[city] = true; 
	}
	// finally, iterate through hashtable and see if any cities weren't 
	// included on the route 
	for (auto city : expected_cities_seen)
	{
		if (city.second == false)
		{
			return -1; 
		}
	}

	// Score calculation: 
	// calculate distance between start and end city, to complete the circuit
	double result = dist_between(route[0], route[size() - 1]);

	// then calculate the distance between all other nodes along the route
	for (int i = 1; i < size(); ++i) {                // i starts at 1, not 0!
		result += dist_between(route[i - 1], route[i]);
	}
	return result;
}

// return a starting route of all the cities in the order 0, 1, 2, 3,
// ...
Route Tsp_map::get_default_route() const
{
	// a route, represented by a vector of ints, shows the order in which nodes 
	// are visited 
	Route route(size());
	for (int i = 0; i < size(); ++i) {
		route[i] = i;
	}
	return route;
}

// operator overload for << Route 
ostream& operator<<(ostream& out, const Route& r)
{ 
	for (auto city : r)
	{
		out << city << " "; 
	}
	return out; 
}

ostream& operator<<(ostream& out, Tsp_map& map)
{
	bool needs_comma = false; 
	out << "{"; 
	for (auto city : map.getCities())
	{
		if (needs_comma)
		{
			out << ","; 
		}
		out << city;
		needs_comma = true; 
	}
	out << "}"; 
	return out; 
}
