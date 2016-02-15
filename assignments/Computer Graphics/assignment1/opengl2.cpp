#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

float angle = 0.0f, m, c;
int xleft, xright, yleft, yright, opt, xc, yc, r;

void myInit()
{ 
	/* attributes */
	glClearColor(0.0, 0.0, 0.0, 0.0);
 
	/* setting up viewing */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 900.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
}

void plot8way( int x, int y, int xc, int yc)
{
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	    glVertex2i(x+xc,y+yc);
	    glVertex2i(-x+xc,y+yc);
	    glVertex2i(x+xc,-y+yc);
	    glVertex2i(-x+xc,-y+yc);
	    glVertex2i(y+xc,x+yc);
	    glVertex2i(-y+xc,x+yc);
    	glVertex2i(y+xc,-x+yc);
	    glVertex2i(-y+xc,-x+yc);
	glEnd();
}
 
 
void circle(int xc, int yc, int r)
{
	int x = 0, y = r;
	plot8way( x, y, xc, yc);
 
	int d = 1 - r;
	while(y >= x)
	{
		if( d < 0 )			
		{
			d += 2.0f * x + 3.0f;
		}
		else		
		{
			d += 2.0f*(x-y) + 5.0f;
			y--;
		}
		x++;
		plot8way(x,y,xc,yc);
	}
}
 
void line(int xleft, int yleft, int xright, int yright)
{
    m = (float)(yright-yleft) / (float)(xright-xleft);
	c = yleft - (m*xleft);
	glColor3f(0,1,1);
	float temp;	
	int x,y;	
	if(abs(m) <= 1)
	{
		x = xleft;
		while(x <= xright)
		{
			temp = m * x + c;
			y = round(temp);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			x = x + 1;
		}
	}
	else
	{
		y=yleft;
		while(y<=yright)
		{
			temp = (y/m) - (c/m);
			x=round(temp);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			y = y + 1;
		}
	}
 
}
void renderScene(void)
{

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (opt == 1)
    {
	    line( xleft, yleft, xright, yright);
	}
	else
	{
	    circle( xleft, yleft, r);
    }

	glutSwapBuffers();
}


int main( int argc, char **argv)
{
    
    cout << "\nCircle 0 / Line 1\n";
	cin >> opt;
	if ( opt == 1 )
	{
	    cout << "\nEnter (xleft, yleft) :\n";
	    cin >> xleft >> yleft;
	    
	    cout << "\nEnter (xright, yright) :\n";
	    cin >> xright >> yright;
	}
	else
	{
	    cout << "\nEnter (xc, yc, r) :\n";
	    cin >> xc >> yc >> r;
	}
	
		
	
	
    // init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900,600);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
	
	// register callbacks
	glutDisplayFunc(renderScene);
    myInit();
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

