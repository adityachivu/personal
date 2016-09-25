/*! \file driver.cpp
\brief Driver program that makes calls to Covex Hull API.
*/

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

#include "cgal/algorithm.h"

using namespace std;

/*! \fn void renderScene( void )
\brief Registered call back for GL display function. 
*/
void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	if ( !computed )
	{
		plotPoints( S );
		computed = true;

		//CH = convexHullGrahamScan( S );
		//CH = convexHullAndrew( S );
		CH = convexHullJarvisMarch( S );

		printConvexHull(CH);
	}

	drawConvexHull(CH);
	glutSwapBuffers();
}

/*! \fn int main( int argc, char* argv[] )
\brief Main function.
\param argc default commandline argument.
\param argv default commandline arguments.  
*/
int main( int argc, char* argv[] )
{

	cin >> size >> animtog;
	for ( int i = 0; i < size; i++ )
	{
		double x, y;
		cin >> x >> y;
		S.addPoint( coord(x, y) );
	}

	glutInit(&argc, argv);
	graphicsInitialize();
	glutDisplayFunc( renderScene );
	glutMainLoop();

	return 0;
}

