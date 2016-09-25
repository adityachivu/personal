#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include "algorithm.h"
using namespace std;

int main()
{
	//cout << "Hello" << endl;

	cin >> size;
	for ( int i = 0; i < size; i++ )
	{
		double x, y;
		cin >> x >> y;
		S.addPoint( coord(x, y) );
	}

	for ( int i = 0; i < size; i++ )
	{
		//printPoint( S[i]);
	}


	//cout << setprecision(16) << angleBetween( coord(0, 500), coord(0, 0), coord(1, 0)) << endl;
	//cout << setprecision(50) << angleBetween( coord(-2, 0), coord(0, 0), coord(1, 0)) << endl << endl;
	CH = convexHullGrahamScan( S );

	cout << "\nFinal Output:\nSize: ";
	cout << CH.size() << endl;
	for ( int i = 0; i < CH.size(); i++ )
	{
		printPoint( CH[i] );
	}

	//cout << signedArea(coord(1,1), coord(1,3), coord(3,1));

	return 0;
}