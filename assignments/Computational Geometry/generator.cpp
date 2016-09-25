/*! \file generator.cpp
\brief Generates random dataset from a specified distribution.
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <bits/stdc++.h>

using namespace std;
int main()
{
	float alpha, xupper, xlower;
	int n;
	cin >> n >> alpha >> xlower >> xupper;
	cout << xlower << endl << xupper << endl;
	srand(time(NULL));
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator( seed );
        std::normal_distribution<double> ndistribution(0.0, alpha);
        std::uniform_real_distribution<double> udistribution(-n, n);
        
        for( int i = 0; i < n ; i++)
        {
        	//double x = ((float)(rand() % 1000000))/1000.0f - 50.0f;
        	//double x = ndistribution(generator);
        	double x = udistribution(generator);
        	cout << x << endl;
        }
        
	return 0;
}
