#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;
float angle = 0.0f, m, c;
int xleft, xright, yleft, yright;

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


void renderScene(void)
{

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,          0.0f, 0.0f,  0.0f,			0.0f, 1.0f,  0.0f);

    glClearColor(0.0, 0.0, 0.0, 0.0);
	glBegin(GL_POINTS)
	    glVertex2i(10,10)
	glEnd();

	glutSwapBuffers();
}

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0 * w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int main( int argc, char **argv)
{
    cout<<"\nEnter (xleft, yleft) :\n";
	cin>>xleft>>yleft;
	cout<<"\nEnter (xright, yright) :\n";
	cin>>xright>>yright;
	
	m=(float)(yright-yleft)/(float)(xright-xleft);
	c=yleft-(m*xleft);	
	
	
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

