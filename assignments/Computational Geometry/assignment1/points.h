#include <vector>
#include <stack>
#include <cmath>


//	Semantic alias for necessary Data Structues and functions.
#define point pair<double, double> 
#define pointset vector<point>
#define pointstack stack<point>
#define coord make_pair 
#define addPoint push_back
#define delPoint pop_back
#define INVALID 777

using namespace std;

//	Global variables
int size = 0;
int sizeCH = 0;
pointset S;
pointset CH;

void printPoint( point a )
{
	cout << (double)a.first << " " << (double	)a.second << endl;
}

double distBetween( point a, point b )
{
	double distance = 0;

	double x = (a.first - b.first) * (a.first - b.first);
	double y = (a.second - b.second) * (a.second - b.second);

	distance = sqrt( x + y );

	return distance;
}

double angleBetween( point a, point b , point c )
{
	double angle = 0;

	double moda = distBetween(a, b);
	double modb = distBetween(c, b);

	if ( moda == 0 or modb == 0)
	{
		return INVALID;
	}
	double dot;
	dot = ((a.first - b.first) * (c.first - b.first)) + ((a.second - b.second) * (c.second - b.second));

	angle = acos(dot / (moda * modb));
	
	return angle;
}

int signedArea( point a, point b, point c )
{
	double area = 0;

	area = ((b.second - a.second) * (c.first - b.first)) - ((b.first - a.first) * (c.second - b.second));
	if ( area > 0 )
		return -1;
	else if ( area < 0 )
		return 1;
	else
		return 0;
}
	
point getInteriorPoint( pointset S )
{
	int i = 3;
	point inside = coord(0, 0);
	point a = S[0];
	point b = S[1];
	point c = S[2];

	while( signedArea(a, b, c) == 0 )
	{
		b = c;
		c = S[i++];
	}

	inside = coord((a.first + b.first + c.first)/3, (a.second + b.second + c.second)/3);
	return inside;
}

point getExteriorPoint( pointset S )
{
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



int searchPointSet( pointset S, point a )
{
	for ( int i = 0; i < S.size(); i++ )
	{
		if ( S[i].first == a.first and S[i].second == a.second )
			return i;
	}

	return -1;
}

bool checkRightTurn( point a, point b, point c )
{
	if ( signedArea( a, b, c ) > 0 )
		return false;
	else
		return true;
}

double f( double M, double C, point a )
{
	double parity;
	parity = a.second + M * a.first + C;
	return parity;
}

