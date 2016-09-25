/*! \file animate.h
\brief Displays the working of the algorithms through animation.
*/

#include "points.h"

/*! \def WIDTH
\brief Width of the Clipping plane is 60.
*/
#define WIDTH 60

/*! \def HEIGHT
\brief Height of the Clipping plane is 60.
*/
#define HEIGHT 60

/*! \def ESC
\brief Exit the GL window.
*/
#define ESC 27

/*! \def MU_SEC
\brief Multiplier for microseconds.
*/
#define MU_SEC 1000

/**
* Animation toggle variable.
*/
int animtog = 0;

/*! \fn void processNormalKeys(unsigned char key, int xx, int yy)
\brief Event handler for a key press.
\param key Key pressed.
\param xx Standard GL variable.
\param yy Standard GL variable. 
*/
void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
	if( key == ESC )
   		exit(0);
}

/*! \fn void graphicsInitialize()
\brief Initializes viewing graphics parameters and registers callbacks.
*/
void graphicsInitialize()
{
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 600,600 );
	glutCreateWindow( "Convex Hull Animation" );
	glutKeyboardFunc(processNormalKeys);
	glPointSize(3);
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	gluOrtho2D( -WIDTH, WIDTH, -HEIGHT, HEIGHT );
}

/*! \fn void drawPoint( point a )
\brief Draws a point on the GL window.
\param a Coordinates of point to be drawn.
*/
void drawPoint( point a )
{
	glBegin(GL_POINTS);
		glVertex3f( a.first, a.second, 0.0f );
	glEnd();
}

/*! \fn void plotPoints( pointset S )
\brief Plots the set of points on GL window.
\param S Pointset to be drawn.
*/
void plotPoints( pointset S )
{
	glColor3f( 1.0, 1.0, 0.0 );
	for ( int i = 0; i < S.size(); i++ )
	{
		drawPoint( S[i] );
	}
}

/*! \fn void drawLine( point a, point b )
\brief Draws a line segment between two given points.
\param a Terminal point of segment.
\param a Terminal point of segment.
*/
void drawLine( point a, point b )
{
	glBegin(GL_LINES);
		glVertex3f( a.first, a.second, 0.0f );
		glVertex3f( b.first, b.second, 0.0f );
	glEnd();
}

/*! \fn void drawLineLoop( pointset S )
\brief Draws a closed loop of line segments.
\param S Ordered pointset.
*/
void drawLineLoop( pointset S )
{
	glBegin(GL_LINE_LOOP);
		for ( int i = 0; i < S.size(); i++ )
		{
			glVertex3f( S[i].first, S[i].second, 0.0f );
		}
	glEnd();
}

/*! \fn void drawPolyLine( pointset S )
\brief Draws a polyline.
\param S Ordered pointset.
*/
void drawPolyLine( pointset S )
{
	glBegin(GL_LINES);
		for ( int i = 1; i < S.size(); i++ )
		{
			glVertex3f( S[i].first, S[i].second, 0.0f );
			glVertex3f( S[i-1].first, S[i-1].second, 0.0f );
		}
	glEnd();
}

/*! \fn void drawPolyLine( pointstack S )
\brief Converts pointstack to pointset and draws a polyline.
\param S Ordered pointstack.
*/
void drawPolyLine( pointstack S )
{
	pointset T;
	while( !S.empty() )
	{
		T.addPoint( S.top() );
		S.pop();
	}

	drawPolyLine( T );
}

/*! \fn void animateSelection( pointset CH, point a, point b )
\brief Initializes the frame parameters. Draws current portion of convex hull and the point being considered.
\param CH current portion of convex hull.
\param a terminal point of current segment.
\param b terminal point of current segment.
*/
void animateSelection( pointset CH, point a, point b )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	plotPoints( S );

	glColor3f(0.0, 1.0, 0.0);
	drawPolyLine( CH );

	glColor3f(1.0, 0.0, 0.0);
	drawLine( a, b );

	glutSwapBuffers();
	usleep( (1000/S.size())* MU_SEC );
}

/*! \fn void animateSelection( pointstack CH, point a, point b, point c, pointstack CH2 )
\brief Initializes the frame parameters. Draws current portion of convex hull and the point being considered.
\param CH current portion of convex hull.
\param a terminal point of current segment.
\param b terminal point of current segment.
\param c terminal point of current segment.
\param CH2 previous portion of convex hull. Used only for Andrew's algorithm.
*/
void animateSelection( pointstack CH, point a, point b, point c, pointstack CH2 )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	plotPoints( S );

	glColor3f(0.0, 1.0, 0.0);
	drawPolyLine( CH );
	drawPolyLine( CH2 );

	glColor3f(1.0, 0.0, 0.0);
	drawLine( a, b );
	glColor3f(0.0, 0.0, 1.0);
	drawLine( b, c );

	glutSwapBuffers();
	usleep( (10000/S.size()) * MU_SEC );
}

/*! \fn void drawConvexHull( pointset CH )
\brief Refreshes the GL window and draws the final convex hull.
\param CH pointset containing final convex hull.
*/
void drawConvexHull( pointset CH )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	plotPoints( S );

	glColor3f(0.0, 1.0, 0.0);
	drawLineLoop( CH );
}