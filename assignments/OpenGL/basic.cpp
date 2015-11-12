#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#define fo(n) for(int i=0;i<n;i++)
#define KEY_WIDTH 19.0/140.0
#define BLACK_KEY_WIDTH 13.0/140.0
#define KEY_SPACE 1.0/140.0

using namespace std;

void releaseKey( int value )
{    
    glutPostRedisplay();
}

void drawBlackKey()
{
    //  Draw Black Key Rectangle.
    glBegin(GL_QUADS);
	    glVertex3f(-1.0,1.0,0.0);
	    glVertex3f(-1.0,-0.333,0.0);
		glVertex3f(-(1 - BLACK_KEY_WIDTH),-0.333,0.0);
		glVertex3f(-(1 - BLACK_KEY_WIDTH),1.0,0.0);
    glEnd();
	
}

void drawAllBlackKeys()
{
    //  Reset MODEL_MATRIX
    glLoadIdentity();
    
    //  Set color to BLACK.
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Locate key position and draw.
    glTranslatef(BLACK_KEY_WIDTH, 0.0f, 0.0f);
    for(int i = 1; i < 11; i++)
    {
        drawBlackKey();
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
        glTranslatef( KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);
        if ( i%5 == 2 || i%5 == 0 )
            glTranslatef( KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);   
	}
	
}
void drawWhiteKey()
{
    //  Draw White Key Rectangle.
    glBegin(GL_QUADS);
	    glVertex3f(-1.0,1.0,0.0);
	    glVertex3f(-1.0,-1.0,0.0);
		glVertex3f(-(1 - KEY_WIDTH),-1.0,0.0);
		glVertex3f(-(1 - KEY_WIDTH),1.0,0.0);
    glEnd();
	
}

void drawAllWhiteKeys()
{
    //  Set color to WHITE.
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Locate key position and draw.
    fo(14)
	{
	    drawWhiteKey();
	    glTranslatef(KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);	    
	}
}

void reddenWhiteKey(int n)
{
    //  Reset MODEL_MATRIX
    glLoadIdentity();
    
    //  Set color to RED.
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //  Locate key position.
    fo(n-1) glTranslatef(KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);
    
    //  Draw Key.
    drawWhiteKey();
    drawAllBlackKeys();
    
    // Load to Screen.
	glutSwapBuffers();
	glutTimerFunc(200, releaseKey, 0);
}
 
void reddenBlackKey(int n)
{
    //  Reset MODEL_MATRIX
    glLoadIdentity();
    
    //  Set color to RED.
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //  Locate key position.
    glTranslatef(BLACK_KEY_WIDTH, 0.0f, 0.0f);
    for(int i = 1; i < n; i++)
    {       
        glTranslatef(KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);
        if ( i%5 == 2 || i%5 == 0 )
            glTranslatef(KEY_WIDTH + KEY_SPACE, 0.0f, 0.0f);   
	}
	
	//  Draw Key.
	drawBlackKey();
	
	// Load to Screen.
	glutSwapBuffers();
	glutTimerFunc(200, releaseKey, 0);
}

                       
void handleKeyPress( unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27: exit(0);
        case '\t':{
                 reddenWhiteKey(1);
	            }break;
	    case '1':{
	              reddenBlackKey(1);
	             }break;
	    case 'q':{
	              reddenWhiteKey(2);
	             }break;
	    case '2':{
	              reddenBlackKey(2);
	             }break;
	    case 'w':{
	              reddenWhiteKey(3);
	             }break;
	    case 'e':{
	              reddenWhiteKey(4);
	             }break;
	    case '4':{
	              reddenBlackKey(3);
	             }break;
	    case 'r':{
	              reddenWhiteKey(5);
	             }break;
	    case '5':{
	              reddenBlackKey(4);
	             }break;
	    case 't':{
	              reddenWhiteKey(6);
	             }break;
	    case '6':{
	              reddenBlackKey(5);
	             }break;
	    case 'y':{
	              reddenWhiteKey(7);
	             }break;
	    case 'u':{
	              reddenWhiteKey(8);
	             }break;
	    case '8':{
	              reddenBlackKey(6);
	             }break;
	    case 'i':{
	              reddenWhiteKey(9);
	             }break;
	    case '9':{
	              reddenBlackKey(7);
	             }break;
	    case 'o':{
	              reddenWhiteKey(10);
	             }break;
	    case 'p':{
	              reddenWhiteKey(11);
	             }break;
	    case '-':{
	              reddenBlackKey(8);
	             }break;
	    case '[':{
	              reddenWhiteKey(12);
	             }break;
	    case '=':{
	              reddenBlackKey(9);
	             }break;
	    case ']':{
	              reddenWhiteKey(13);
	             }break;
	    case 8:  {
	              reddenBlackKey(10);
	             }break;
	    case '\\':{
	              reddenWhiteKey(14);
	             }break;
	}
}

        
void renderScene(void)
{
    //  Set Buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  Reset MODEL_MATRIX
    glLoadIdentity();    
    
	//  Draw Keys.
	drawAllWhiteKeys();
	drawAllBlackKeys();
    
    // Load to Screen.
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1200,500);
	glutCreateWindow("Piano");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(handleKeyPress);	
	
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
