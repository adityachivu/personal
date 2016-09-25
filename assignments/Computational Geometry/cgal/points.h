/*! \file points.h
\brief Provides an abstract representation of a point and a set of points.
It provides all the functions to manipulate points to perform various operations required by the Convex hull algorithms.
*/

#include <vector>
#include <stack>
#include <cmath>


// Semantic alias for necessary Data Structues and functions.

/*! \def point
\brief Pair of x, y coordinate of a point.
*/
#define point pair<double, double> 

/*! \def pointset
\brief Vector containing all the points.
*/
#define pointset vector<point>

/*! \def pointstack
\brief Stack of given points.
*/
#define pointstack stack<point>

/*! \def coord
\brief a macro to call make_pair function.
*/
#define coord make_pair 

/*! \def addPoint
\brief a macro to call push_back function.
*/
#define addPoint push_back

/*! \def delPoint
\brief a macro to call pop_back function.
*/
#define delPoint pop_back

/*! \def INVALID
\brief Term used to declare a point as invalid.
*/
#define INVALID 777

/*! \def PI
\brief Term used to represent PI for angle calculation measured in radians.
*/
#define PI 3.141592653589793f

/*! \def ZERO
\brief Term used to represent Zero angle in float.
*/
#define ZERO 0.0f

using namespace std;

/**
* a public variable.
* Denotes the cardinality of the set of given points.
*/
int size = 0;

/**
* a public variable.
* Denotes the cardinality of the set of points in the convex hull.
*/
int sizeCH = 0;

/**
* a public variable.
* Declares a pointset for the set of given input points.
*/
pointset S;

/**
* a public variable.
* Declares a pointset for the set of points in Conves Hull.
*/
pointset CH;

/**
* a public variable.
* Declares an empty stack.
*/
pointstack ET;

/*! \fn void printPoint( point a )
\brief Prints a point ( its x and y coordinate).
\param a A point.
*/
void printPoint( point a )
{
	cout << setprecision(9) << (double)a.first << " " << (double)a.second << endl;
}

/*! \fn double distBetween( point a, point b )
\brief Calculates the distance between two points passed as parameters.
\param a First point.
\param b Second point. 
*/
double distBetween( point a, point b )
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

/*! \fn double angleBetween( point a, point b , point c )
\brief Calculates the angle between two points wrt third point passed as parameters using cos.
\param a First point.
\param c Second point. 
\param b Reference point.
*/
double angleBetween( point a, point b , point c )
{
	/*A local variable. Declares and initializes angle between points as 0. */
	double angle = 0;	

	/*  A local variable. Determines the distance between point 1 and reference point. */
	double moda = distBetween(a, b);	
	
	/*  A local variable. Determines the distance between point 2 and reference point. */
	double modb = distBetween(c, b);  	

	if ( moda == 0 or modb == 0)
	{
		return INVALID;
	}

	/*  A local variable. Calculates the dot product between the segments ac and bc. */
	double dot;	
	dot = ((a.first - b.first) * (c.first - b.first)) + ((a.second - b.second) * (c.second - b.second));

	angle = acos(dot / (moda * modb));
	
	return angle;
}

/*! \fn int signedArea( point a, point b, point c )
\brief Calculates the signed area of three points to find the direction in which these three points connect to each other.
\param a First point.
\param b Second point. 
\param c Third point.
* Returns 1 for anti-clockwise direction or left turn
* Returns -1 for clockwise direction or right turn
* Returns 0 if all the points are collinear.
*/
int signedArea( point a, point b, point c )
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

/*! \fn point getInteriorPoint( pointset S )
\brief Finds a point lying inside the convex hull. Used for Graham scan.
\param S Set of points to find the interior point within.
*/	
point getInteriorPoint( pointset S )
{
	int i = 3;
	
	/* A local variable. Declares and initializes the inside point as (0,0). */
	point inside = coord(0, 0);	
	point a = S[0];
	point b = S[1];
	point c = S[2];

	while( signedArea(a, b, c) == 0 )
	{
		b = c;
		c = S[i++];
	}
	
	//finds a centroid of three non-collinear points and makes it the interior point.
	inside = coord((a.first + b.first + c.first)/3, (a.second + b.second + c.second)/3);
	return inside;
}

/*! \fn point getExteriorPoint( pointset S )
\brief Finds a point lying outside the convex hull. Used for Jarvis March and Andrew's algorithm.
\param S Set of points to find the interior point within.
*/
point getExteriorPoint( pointset S )
{
	/* A local variable. Declares and initializes the outside point as the first point in pointset and later assigns it a point with minimum y coordiante value. */
	point outside = S[0];	
	//printPoint( outside );

	for ( int i = 1; i < S.size(); i++ )
	{
		if ( S[i].second < outside.second )
		{
			outside = S[i];
		}
	}

	return outside;
}

/*! \fn int searchPointSet( pointset S, point a )
\brief Checks if a given point is one among the given set of points.
\param S Set of points..
\param a A point to be searched.
* Returns 1 if the point belongs to the pointset else returns -1.
*/
int searchPointSet( pointset S, point a )
{
	for ( int i = 0; i < S.size(); i++ )
	{
		if ( S[i].first == a.first and S[i].second == a.second )
			return i;
	}

	return -1;
}

/*! \fn bool checkRightTurn( point a, point b, point c )
\brief Finds if a set of points in a sequence make a right turn or not. Used in Graham scan and Andrew's algorithm.
\param a First point.
\param b Second point. 
\param c Third point.
*/
bool checkRightTurn( point a, point b, point c )
{
	if ( signedArea( a, b, c ) > 0 )
		return false;
	else
		return true;
}

/*! \fn void printConvexHull( pointset CH )
\brief Prints the points lying on the Convex Hull via STDOUT.
\param CH pointset
*/
void printConvexHull( pointset CH )
{
	cout << CH.size() << endl;
	for( int i = 0; i < CH.size() ; i++)
	{
		printPoint( CH[i] );
	}
}
