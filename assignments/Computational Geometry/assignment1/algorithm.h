#include <algorithm>
#include <cmath>

#include "points.h"
#define PI 3.141592653589793


pointset convexHullGrahamScan( pointset S )
{
	vector< pair< double, point > > angS;
	pointstack stackCH;

	point centre = getInteriorPoint( S );
	printPoint( centre );
	cout << endl;

	point axis = coord( centre.first + 1, centre.second );

	for ( int i = 0; i < S.size(); i++ )
	{
		double angle = angleBetween( S[i], centre, axis );
		if ( angle == INVALID )
		{
			continue;
		}

		if ( S[i].second < centre.second )
		{
			angle = (2 * PI) - angle;
		}

		angS.push_back(make_pair(angle, S[i]));		
	}

	sort(angS.begin(), angS.end());
	for ( int i = 0; i < angS.size(); i++ )
	{
		cout << angS[i].first << " ";
		printPoint( angS[i].second );
	}

	point a = angS[0].second, b = angS[1].second, c;
	stackCH.push(a);
	stackCH.push(b);


	for ( int i = 2; i < angS.size(); i++ )
	{
		b = stackCH.top();
		stackCH.pop();

		a = stackCH.top();
		stackCH.pop();

		c = angS[i].second;

		printPoint(a);
		printPoint(b);
		printPoint(c);
		cout << endl;

		while( checkRightTurn(a, b, c) )
		{
			if ( stackCH.empty() )
				break;
			b = a;
			a = stackCH.top();
			stackCH.pop();
			cout << ".";
			printPoint(a);
			printPoint(b);
			printPoint(c);
			cout << endl;
			if ( stackCH.empty() )
				break;
		}

		stackCH.push( a );
		stackCH.push( b );
		stackCH.push( c );
	}

	while ( !stackCH.empty() )
	{
		CH.addPoint( stackCH.top() );
		stackCH.pop();
	}


	return CH;
}

pointset convexHullJarvisMarch( pointset S )
{
	double minangle = PI, angle = 0;
	int id = 0;
	

	point start = getExteriorPoint( S );
	//printPoint( getExteriorPoint( S ) );
	point curr = start;
	point prev;
	point axis = coord(curr.first + 1, curr.second);
	
	CH.addPoint(start);
	sizeCH = 0;
	
	while( curr != start or CH.size() < 2 )
	{
		printPoint( curr );
		printPoint( axis );
		minangle = PI;
		for ( int i = 0; i < S.size(); i++ )
		{
			angle = angleBetween(S[i], curr, axis);
			cout << angle << " ";
			if ( angle < minangle and angle != INVALID )
			{
				minangle = angle;
				id = i;
				cout << "y";
			}
		}
		cout << endl << endl;
		curr = S[id];
		prev = CH[sizeCH];
		CH.addPoint( curr );
		sizeCH++;

		axis = coord(2 * curr.first - prev.first, 2 * curr.second - prev.second);
		
	}
	
	CH.delPoint();	
	return CH;
}

pointset convexHullAndrew( pointset S )
{
	pointstack Lup, Llo;

	sort( S.begin(), S.end() );
	point a = S[0], b = S[1], c;

	Lup.push( a );
	Lup.push( b );

	for ( int i = 2; i < S.size(); i++ )
	{
		b = Lup.top();
		Lup.pop();

		a = Lup.top();
		Lup.pop();

		c = S[i];

		printPoint(a);
		printPoint(b);
		printPoint(c);
		cout << endl;

		while( !checkRightTurn(a, b, c) )
		{
			b = a;
			a = Lup.top();
			Lup.pop();
			cout << ".";
			printPoint(a);
			printPoint(b);
			printPoint(c);
			cout << endl;
		}

		Lup.push( a );
		Lup.push( b );
		Lup.push( c );
	}

	printPoint(a);
	printPoint(b);
	printPoint(c);
	cout << endl;
	cout << "lol\n";
	reverse( S.begin(), S.end() );

	a = S[0];
	b = S[1];

	Llo.push( a );
	Llo.push( b );

	for ( int i = 2; i < S.size(); i++ )
	{
		b = Llo.top();
		Llo.pop();

		a = Llo.top();
		Llo.pop();

		c = S[i];

		printPoint(a);
		printPoint(b);
		printPoint(c);
		cout << endl;

		while( !checkRightTurn(a, b, c) )
		{
			b = a;
			a = Llo.top();
			Llo.pop();
			printPoint(a);
			printPoint(b);
			printPoint(c);
			cout << endl;

		}

		Llo.push( a );
		Llo.push( b );
		Llo.push( c );
	}
    
    Llo.pop();
	while( !Llo.empty() )
	{
		CH.addPoint( Llo.top() );
		Llo.pop();
	}

	Lup.pop();
	while( !Lup.empty() )
	{
		CH.addPoint( Lup.top() );
		Lup.pop();
	}
	return CH;
}