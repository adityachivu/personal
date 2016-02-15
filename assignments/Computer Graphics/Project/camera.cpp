#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include "objects.h"
#include "musicfile.h"
using namespace std;



// Angles of rotation for the camera direction
float XZangle = 0.0f;
float Yangle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
float ly = 0.0f;



// the key states. These variables will be zero
//when no key is being presses
float deltaXZangle = 0.0f;
float deltaYangle = 0.0f;
int xOrigin = -1;
int yOrigin = -1;
int buildtog = 1;
float r,g,b;

void changeSize(int w, int h) 
{
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glClearColor(102.0/255.0-dullness, 204.0/255.0-2*dullness, 1.0f-2*dullness, 1.0f);
	glLoadIdentity();
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0+ly,  z+lz,
			0.0f, 1.0f,  0.0f);
			
	

	// Toggle for rain
	ifstream filei("pianosignal.txt");
	if(filei)
		raintoggle ^= 1;
	
	// Render all Scene elements.	
	drawGround();
	rainWithMusic();
	renderRoad();
	if ( buildtog )
    	renderBuilding();
	
	glutSwapBuffers();
} 

void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
        if (key == 27)
              exit(0);
        if (key == 't')
            raintoggle ^= 1;
		if(key == 'f')
			freezetoggle^=1;
		if(key == 'i')
			windz -= 0.01f;
		if(key == 'j')
			windx -= 0.01f;
		if(key == 'k')
			windz += 0.01f;
		if(key == 'l')
			windx += 0.01f;
	    if(key == 'q')
	    {
	        NUM_DROPS += 100;
	        size = NUM_DROPS/5000 + 0.2f;
	        initDrops();
	    }
	    if(key == 'a')
	    {
	        NUM_DROPS -= 100;
	        size = NUM_DROPS/5000 + 0.2f;
	        initDrops();
	    }
	    if(key == 'b')
			buildtog^=1;
}

void mouseMove(int x, int y) 
{ 	
         if(xOrigin >= 0) 
		        {
			        deltaXZangle = (x - xOrigin) * 0.010f;

			        lx = sin(XZangle + deltaXZangle);
			        lz = -cos(XZangle + deltaXZangle);
		        }

		        if(yOrigin >= 0)
		        {
			        deltaYangle = (yOrigin - y) * 0.006f;
			        ly = sin(Yangle + deltaYangle);
		        }
}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_UP)
	    {
			XZangle += deltaXZangle;
			xOrigin = -1;
			Yangle += deltaYangle;
			yOrigin = -1;		
		}
		else
		{
			xOrigin = x;
			yOrigin = y;
		}	
	}
}

void timed(int a)
{
	glutPostRedisplay();
	glutTimerFunc(500, timed, 0);
}
void reDraw(int value)
{
	renderRoad();
	renderBuilding();
	glutSwapBuffers();
	glutTimerFunc(20, reDraw, 0);
}	
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1250,400);
	glutCreateWindow("The Walk");
	glEnable(GL_DEPTH_TEST);
	
    //  Register all callbacks.
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
    
    //  Register interaction callbacks.
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	
	//  Initialize starting scenery.
    initDrops();
	initRoad();
	initBuildingScene();
	
	glutMainLoop();

	return 0;
}

