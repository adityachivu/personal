#ifndef POINT_H
#define POINT_H

#include <cmath>

#define INVALID 1e10
#define PI 3.14159265359

class Point
{
private:
	float x;
	float y;

public:

	Point()
	{

	}

	Point( std::pair<float, float> pt )
	{
		this->x = pt.first;
		this->y = pt.second;
	}

	std::pair<float, float> getPos()
	{
		return std::make_pair( x, y );
	}

	void coord( std::pair<float, float> pt )
	{
		this->x = pt.first;
		this->y = pt.second;
	}

	friend void printPoint( Point );
	friend bool checkRightTurn( Point, Point, Point );
	friend int signedArea( Point, Point, Point );
	friend double distBetween( Point, Point );
	friend double angleBetween( Point, Point, Point );

	bool operator < ( const Point& pt ) const
	{
		//std::pair< float, float > a = this->getPos();
		//std::pair< float, float > b = pt.getPos();

		if( y > pt.y )
		{
			return true;
		}
		else if( y == pt.y and x < pt.x )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

void printPoint( Point pt )
{
	std::pair<float, float> coord = pt.getPos();
	std::cout << coord.first << ", " << coord.second << std::endl;
}
int signedArea( std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c )
{
	/* A local variable.Declares and initializes area as 0. */
	double area = 0;

	area = ((b.second - a.second) * (c.first - b.first)) - ((b.first - a.first) * (c.second - b.second));
	if ( area > 0 )
		return -1;
	else if ( area < 0 )
		return 1;
	else
		return 0;
}

bool checkRightTurn( std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c )
{
	if ( signedArea( a, b, c ) >= 0 )
		return false;
	else
		return true;
}

bool checkRightTurn( Point p, Point q, Point r )
{
	return checkRightTurn( p.getPos(), q.getPos(), r.getPos() );
}

double distBetween( Point p, Point q )
{
	distBetween( p.getPos(), q.getPos() );
}
double distBetween( std::pair<float, float> a, std::pair<float, float> b )
{
	/* A local variable. Declares and initializes distance as 0. */
	double distance = 0;

	/* A local variable. Determines squared distance in x direction. */
	double x = (a.first - b.first) * (a.first - b.first);	
	
	/* A local variable. Determines squared distance in y direction. */
	double y = (a.second - b.second) * (a.second - b.second);	
	
	distance = sqrt( x + y );
        
	return distance;
}


double angleBetween( std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c )
{
	/*A local variable. Declares and initializes angle between points as 0. */
	double angle = 0;	

	/*  A local variable. Determines the distance between point 1 and reference point. */
	double moda = distBetween(a, b);	
	
	/*  A local variable. Determines the distance between point 2 and reference point. */
	double modb = distBetween(c, b);  	

	if ( moda == 0 or modb == 0 )
	{
		return INVALID;
	}

	/*  A local variable. Calculates the dot product between the segments ac and bc. */
	double dot;	
	dot = ((a.first - b.first) * (c.first - b.first)) + ((a.second - b.second) * (c.second - b.second));

	angle = acos(dot / (moda * modb));

	if ( checkRightTurn( a, b, c ) )
	{
		angle = (2 * PI) - angle;
	}
	
	return angle;
}
double angleBetween( Point p, Point q, Point r )
{
	return angleBetween( p.getPos(), q.getPos(), r.getPos() );
}





#endif