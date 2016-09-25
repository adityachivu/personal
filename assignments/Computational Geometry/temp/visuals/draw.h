#ifndef DRAW_H
#define DRAW_H

#include <GL/glut.h>
#include "../data/point.h"
class Point;

#define pointset std::vector< Point >

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

class MeshDraw
{

	Mesh* mymesh;
public:

	void graphicsInitialize();
	friend void processNormalKeys( unsigned char, int, int );
	friend void renderScene();
	void draw();

	MeshDraw()
	{
		graphicsInitialize();
	}
	MeshDraw( Mesh* meshdraw )
		:mymesh( meshdraw )
	{
		graphicsInitialize();

	}

	
};

/*! \fn void processNormalKeys(unsigned char key, int xx, int yy)
\brief Event handler for a key press.
\param key Key pressed.
\param xx Standard GL variable.
\param yy Standard GL variable. 
*/
void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
	if( key == ESC )
   		return;
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}
void MeshDraw::graphicsInitialize()
{
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 600,600 );
	glutCreateWindow( "Drawing Window" );
	glutKeyboardFunc( processNormalKeys );
	glutDisplayFunc( renderScene );
	glPointSize(3);
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	gluOrtho2D( -WIDTH, WIDTH, -HEIGHT, HEIGHT );
	glutMainLoop();
}

/*! \fn void drawLineLoop( pointset S )
\brief Draws a closed loop of line segments.
\param S Ordered pointset.
*/
void drawLineLoop( pointset S )
{

	glColor3f( 0.0, 0.0, 1.0 );
	glBegin(GL_LINE_LOOP);
		for ( int i = 0; i < S.size(); i++ )
		{
			std::pair<float, float> a = S[i].getPos();
			glVertex3f( a.first, a.second, 0.0f );
		}
	glEnd();
}

void MeshDraw::draw()
{
	std::vector< Face > faces = mymesh->getFaces();
	pointset S;

	for( int i = 0; i < faces.size(); i++ )
	{
		EdgeIterator it( &faces[i] );
		while( it.hasNext() )
		{
			S.push_back( it.getHalfEdge()->getOrigin()->getPos() );
			it.next();
		}
		drawLineLoop( S );
	}
	glutSwapBuffers();

}

/*! \fn void drawPoint( point a )
\brief Draws a point on the GL window.
\param a Coordinates of point to be drawn.
*/
void drawPoint( Point p )
{
	std::pair<float, float> a = p.getPos();
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
void drawLine( Point p, Point q )
{
	std::pair<float, float> a = p.getPos();
	std::pair<float, float> b = q.getPos();
	glBegin(GL_LINES);
		glVertex3f( a.first, a.second, 0.0f );
		glVertex3f( b.first, b.second, 0.0f );
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
			std::pair<float, float> a = S[i].getPos();
			std::pair<float, float> b = S[i-1].getPos();
			glVertex3f( a.first, a.second, 0.0f );
			glVertex3f( b.first, b.second, 0.0f );
		}
	glEnd();
}

/*! \fn void drawPolyLine( pointstack S )
\brief Converts pointstack to pointset and draws a polyline.
\param S Ordered pointstack.
*/
/*
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
*/
#endif