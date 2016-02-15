#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

// Angles of rotation for the camera direction
float XZangle = 0.0f;
float Yangle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
float ly = 0.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaXZangle = 0.0f;
float deltaYangle = 0.0f;

float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
int lstrafe = 0;
int rstrafe = 0;

float r,g,b;
float u[15][15];
float v[15][15];

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

void drawParapetX(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
	int h;
    for(h=0;h<8;h++)
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.6f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.1+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, 0.0f);
	 
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.1+h*0.3, len);
		glVertex3f(0.0f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.1+h*0.3, len);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, len);
		glVertex3f(0.0f, 0.1+h*0.3, len);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.3+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, 0.0f);
 	}
    glEnd();
}

void drawDoorX()
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 4.0f);
    glVertex3f(0.0f, 5.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 4.0f);
    glVertex3f(0.6f, -1.0f, 4.0f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 4.0f);
    glVertex3f(0.0f, -1.0f, 4.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawDoorZ()
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(4.0f, -1.0f, 0.6f);
    glVertex3f(4.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(4.0f, -1.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.6f);
    glVertex3f(4.0f, -1.0f, 0.6f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, -1.0f, 0.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawWallZ(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(len, -1.0f, 0.6f);
    glVertex3f(len, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(len, -1.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.6f);
    glVertex3f(len, -1.0f, 0.6f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.0f);
    glVertex3f(len, -1.0f, 0.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawWallX(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, len);
    glVertex3f(0.6f, 5.0f, len);
    glVertex3f(0.6f, 5.0f, 0.0f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, len);
    glVertex3f(0.0f, 5.0f, len);
    glVertex3f(0.6f, 5.0f, len);
    glVertex3f(0.6f, -1.0f, len);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, len);
    glVertex3f(0.0f, -1.0f, len);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void computePos(float deltaMove) 
{
	if(lstrafe)
	{
		x += lz * 0.1f;
		z += (-lx) * 0.1f;
	}
	else if(rstrafe)
	{
		x += (-lz) * 0.1f;
		z += 	lx * 0.1f;
	}
	else
	{
		x += deltaMove * lx * 0.1f;
		z += deltaMove * lz * 0.1f;
	}
}

void watersim(void)
{	int i,j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
		{
			v[i][j] += (i==0)?(u[i-1][j]):(u[i][j]) + (i==14)?(u[i+1][j]):(u[i][j]) + (j==0)?(u[i][j-1]):(u[i][j]) + (j==14)?(u[i][j+1]/4):(u[i][j]) - u[i][j];
			v[i][j] *= 0.99;
			u[i][j] += v[i][j];
		}

	glColor3f(0.0,0.0,0.9);
	glBegin(GL_POINTS);
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			glVertex3f(i,j,u[i][j]);
	glEnd();
	glColor3f(r,g,b);
}

void renderScene(void) 
{
	if (deltaMove || lstrafe || rstrafe)
		computePos(deltaMove);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glClearColor(102.0/255.0, 204.0/255.0, 1.0f, 1.0f);
	glLoadIdentity();
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0+ly,  z+lz,
			0.0f, 1.0f,  0.0f);

	glColor3f(0.0f, 0.65f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	int i,j;

	//Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(29.6,0,30);
    drawDoorZ();
    glPopMatrix();

	//Door attached wall
	r = 0.9, g = 0.9, b = 0.9;
	glPushMatrix();
    glTranslatef(33,0,30.6);
    drawWallX(10);
    glPopMatrix();

	//Door attached wall
	glPushMatrix();
    glTranslatef(26.6,0,30);
    drawWallZ(3);
    glPopMatrix();

	//Living room wall
	glPushMatrix();
    glTranslatef(26.6,0,30);
    drawWallX(-5);
    glPopMatrix();

	//Long living room wall	
	glPushMatrix();
    glTranslatef(26.6,0,25);
    drawWallZ(-30);
    glPopMatrix();

	//Balcony to hall living room connector	
	glPushMatrix();
    glTranslatef(-3.4,0,40);
    drawWallZ(15);
    glPopMatrix();

	//Balcony parapet
	r = 0.0, g = 0.0, b = 0.0;
	glPushMatrix();
    glTranslatef(-9.6,0,25.65);
    drawParapetX(14.2);
    glPopMatrix();

	r = 0.9, g = 0.9, b = 0.9;
	//Balcony wall
	glPushMatrix();
    glTranslatef(-3.4,0,25);
    drawWallZ(-6);
    glPopMatrix();

	//Balcony wall
	glPushMatrix();
    glTranslatef(-3.4,0,40);
    drawWallZ(-6);
    glPopMatrix();

	//Balcony slide doors
	glPushMatrix();
    glTranslatef(-3.4,0,25);
    drawWallX(6);
    glPopMatrix();

	//Balcony slide doors
	glPushMatrix();
    glTranslatef(-3.4,0,34);
    drawWallX(6);
    glPopMatrix();

	//Shoebox wall	
	glPushMatrix();
    glTranslatef(33,0,40);
   	drawWallZ(-6);
    glPopMatrix();
    
	//Hall wall to bathroom
	glPushMatrix();
    glTranslatef(27,0,40);
    drawWallX(15);
    glPopMatrix();

	//Hall wall
	glPushMatrix();
    glTranslatef(11.6,0,40);
    drawWallX(25);
    glPopMatrix();

	//Bathroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(27,0,55);
    drawDoorX();
    glPopMatrix();

	//Bedroom bathroom separator
	r = 0.9, g = 0.9, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(27,0,59);
    drawWallX(1);
    glPopMatrix();

	//Bathroom walls
	r = 0.0, g = 0.0, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(27.6,0,59);
    drawWallZ(10);
    glPopMatrix();
	//Bathroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,49);
    drawWallZ(10);
    glPopMatrix();
	//Bathroom walls
	glPushMatrix(); 
    glTranslatef(37.6,0,59);
    drawWallX(-10);
    glPopMatrix();

	//Bedroom walls
	r = 0.9, g = 0.9, b = 0.9;
	glPushMatrix(); 
    glTranslatef(27.6,0,59.6);
    drawWallZ(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix();     
	glTranslatef(37.6,0,59);
    drawWallX(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallZ(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallX(-4.8);
    glPopMatrix();
	//Bathroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(27.6,0,60.2);
    drawDoorX();
    glPopMatrix();
	
	//Bedroom kitchen separator
	r = 0.9, g = 0.9, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallZ(-5);
    glPopMatrix();

	//Kitchen walls
	glPushMatrix(); 
    glTranslatef(22.6,0,69);
    drawWallX(15);
    glPopMatrix();
	//Kitchen walls
	glPushMatrix();     
	glTranslatef(22.6,0,84);
    drawWallZ(-7);
    glPopMatrix();
	//Kitchen walls
	glPushMatrix();     
	glTranslatef(15.6,0,84);
    drawWallX(-15);
    glPopMatrix();

	//Kitchen bedroom separator
	glPushMatrix(); 
    glTranslatef(15.6,0,69);
    drawWallZ(-2);
    glPopMatrix();

	//Bedroom 2 walls
	glPushMatrix(); 
    glTranslatef(13.6,0,69);
    drawWallX(15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(13.6,0,84);
    drawWallZ(-15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(-2.6,0,84);
    drawWallX(-15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(-2.6,0,69);
    drawWallZ(12);
    glPopMatrix();

	//Bedroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(9.6,0,69);
    drawDoorZ();
    glPopMatrix();

	//Bathroom 2 walls
	r = 0.9, g = 0.9, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(5.6,0,65);
    drawWallZ(-13);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(-7.4,0,65);
    drawWallX(-6);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(-7.4,0,59);
    drawWallZ(19);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(9.6,0,65);
   	drawWallZ(2);
    glPopMatrix();
	//Bathroom 2 Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(5.59,0,65);
    drawDoorZ();
    glPopMatrix();
	
	//Bedroom 3 walls
	r = 0.9, g = 0.9, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(-7.4,0,59);
    drawWallZ(-6);
    glPopMatrix();
	//Bedroom 3 walls
	glPushMatrix();     
	glTranslatef(-13.4,0,59);
    drawWallX(25);
    glPopMatrix();
	//Bedroom 3 walls
	glPushMatrix();     
	glTranslatef(-13.4,0,84);
    drawWallZ(15);
    glPopMatrix();
	//Bedroom 3 Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(-2.6,0,65);
    drawDoorX();
    glPopMatrix();

    glPushMatrix(); 
    glTranslatef(-30,0,-30);
    watersim();
    glPopMatrix();
	glutSwapBuffers();
} 

void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
        if (key == 27)
              exit(0);
} 

void pressKey(int key, int xx, int yy) 
{
       switch (key) 
	   {
             case GLUT_KEY_UP : deltaMove = 0.8f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.8f; break;	
		 	 case GLUT_KEY_RIGHT: rstrafe = 1; break;
			 case GLUT_KEY_LEFT: lstrafe = 1; break;
       }
} 

void releaseKey(int key, int x, int y) 
{ 	
        switch (key) 
		{
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0; break;
			 case GLUT_KEY_LEFT : lstrafe = 0; break;
			 case GLUT_KEY_RIGHT : rstrafe = 0; break;       
		}
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

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	int i,j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			v[i][j] = 0, u[i][j] = (i+j)/1000.0;
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}


