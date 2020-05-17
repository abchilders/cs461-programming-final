// based on the Point class by Toby Donaldson, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/oop_intro

#pragma once
#include <ostream>

using namespace std; 

// Each Point represents a point with (x, y) coordinates 
//  on a Cartesian plane. 
class Point
{
private:
	double x; 
	double y; 
    const double MIN_DIFF = 0.00000000001;
    
public:
    // default constructor 
    Point(); 

    // constructor 
    Point(double a, double b); 

    // copy constructor
    Point(const Point& p); 

    // getter for x 
    double getX(); 

    // getter for y 
    double getY(); 

    // setter for x 
    void setX(double new_x); 

    // setter for y 
    void setY(double new_y); 

    // returns true if the given Point is the same as this one 
    bool equals(const Point& p); 

    // operator overload for Point == Point 
    bool operator==(const Point& p); 

    // operator overload for Point != Point
    bool operator!=(const Point& p);

    // prints the coordinates of a Point
    void print(); 

    // prints the coordinates of a Point on its own line
    void println(); 

    // destructor 
    ~Point();
}; 

// operator overload for << Point 
ostream& operator<<(ostream& out, Point& p); 

// returns the distance between two Points
double dist(Point& p, Point& q); 
