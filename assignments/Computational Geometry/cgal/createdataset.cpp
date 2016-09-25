/*! \file createdataset.cpp
\brief Generates random dataset from a specified distribution.
*/

#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

int main()
{
	int n, tog;
	float alpha;
	cin >> n >> alpha >> tog;
	cout << n << " " << tog << endl;

	float mul[2] = {0, -2};

	srand(time(NULL));
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator( seed );
  	std::normal_distribution<double> ndistribution( 0.0, alpha );
  	std::weibull_distribution<double> wdistribution( alpha, 1.0 );
  	std::poisson_distribution<int> pdistribution( alpha );

	for ( int i = 0; i < n; i++ )
	{
		//double x = ((float)(rand() % 1000000))/10000.0f - 50.0f;
		//double y = ((float)(rand() % 1000000))/10000.0f - 50.0f;
		//double x = ndistribution(generator);
		//double y = ndistribution(generator);
		//double x = wdistribution(generator) * 20 - 50;
		//double y = wdistribution(generator) * 20 - 50;
		double x = pdistribution(generator);
		double y = pdistribution(generator);

		x += mul[rand()%2] * x;
		y += mul[rand()%2] * y;

		cout << setprecision(16) << x << " " << y << endl;
	}
	return 0;
}