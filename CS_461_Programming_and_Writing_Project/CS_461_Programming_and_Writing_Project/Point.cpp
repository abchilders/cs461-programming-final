// based on the Point class by Toby Donaldson, 
// https://www2.cs.sfu.ca/CourseCentral/125/tjd/oop_intro

#include "Point.h"
#include <iostream>
#include <cmath>

// default constructor
Point::Point() : x(0), y(0) 
{   
  // empty body
}

// constructor
Point::Point(double a, double b) : x(a), y(b) 
{   
  // empty body
}

// copy constructor
Point::Point(const Point& p) : x(p.x), y(p.y) 
{  
  // empty body
}

// getter for x
double Point::getX()
{
    return x;
}

// getter for y 
double Point::getY()
{
    return y;
}

// setter for x
void Point::setX(double new_x)
{
    x = new_x; 
}

void Point::setY(double new_y)
{
    y = new_y; 
}

// returns true if the given Point is the same as this one 
bool Point::equals(const Point& p) 
{
    return abs(p.x - x) < MIN_DIFF && abs(p.y - y) < MIN_DIFF;
}

// operator overload for Point == Point 
bool Point::operator==(const Point& p) 
{
    return equals(p);
}

// operator overload for Point != Point
bool Point::operator!=(const Point& p) 
{
    return !equals(p);
}

// prints the coordinates of a Point
void Point::print() 
{
    cout << "(" << x << ", " << y << ")";
}

// prints the coordinates of a Point on its own line
void Point::println() 
{
    print();
    cout << endl;
}

// destructor
Point::~Point() 
{
    // empty body-- no pointers to delete
}

// operator overload for << Point
ostream& operator<<(ostream& out, Point& p) 
{
    out << "(" << p.getX() << ", " << p.getY() << ")";
    return out;
}

// returns the distance between two Points
double dist(Point& p, Point& q)
{
    double dx = p.getX() - q.getX();
    double dy = p.getY() - q.getY();
    return sqrt(dx * dx + dy * dy);
}
