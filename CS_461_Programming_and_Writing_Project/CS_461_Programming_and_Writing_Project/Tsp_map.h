// based on the Tsp_map class by Toby Donaldson, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/tsp_example.html

#pragma once
#include <vector>
#include "Point.h"

typedef vector<int> Route; 

class Tsp_map {
private:
	// each city is located at a point with (x, y) coordinates 
	vector<Point> cities; 

public:
	// default constructor
	Tsp_map(); 

	// add a city to the map at point p
	void add(const Point& p);

	// add a city to the map at (x, y)
	void add(double x, double y);

	// returns # of cities in the map
	int size() const;

	// calculate the distance between cities i and j
	double dist_between(int i, int j);

	// calculate the score (total distance traveled) of the given route
	double score(Route& route);

	// return a starting route of all the cities in the order 0, 1, 2, 3,
	// ...
	Route get_default_route() const;

}; // class Tsp_map

// operator overload for << Route 
ostream& operator<<(ostream& out, const Route& r);