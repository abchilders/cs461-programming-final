#pragma once
#include "Point.h"
#include <vector>

class Tsp_map {
private:
	// each city is located at a point with (x, y) coordinates 
	std::vector<Point> cities; 

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
	double dist_between(int i, int j) const;

	// calculate the score (total distance traveled) of the given route
	double score(const vector<int>& route) const;

	// return a starting route of all the cities in the order 0, 1, 2, 3,
	// ...
	vector<int> get_default_route() const;

}; // class Tsp_map