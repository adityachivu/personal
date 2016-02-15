#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;
 
int xleft, xright, yleft, yright;
float m,c;
 
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
 
void plot8way(int x, int y, int xc, int yc) //plot 8 symmetrical points for circle with centre (xc,yc)
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
 
 
void circle(int xc, int yc, int r)	//draw circle according to Midpoint Algorithm
{
	int x=0, y=r;
	plot8way(x,y,xc,yc);
 
	int d=1-r;		//decision parameter d to determine region of midpoint
	int deltaE=3;		//increment d by this quantity if east point is chosen
	int deltaSE=-2*r+5;		//increment d by this quantity if southeast point is chosen
	while(y>=x)	//loop to cover points from y axis to slope=1 (to exploit 8-way symmetry)
	{
		if(d<0)			//if d<0, choose east point
		{
			d+=deltaE;
			deltaE+=2;	//use double difference to alter deltaE, SE
			deltaSE+=2;
		}
		else		//if d>=0, choose south-east point
		{
			d+=deltaSE;
			deltaE+=2;	//use double difference to alter deltaE, SE
			deltaSE+=4;
			y--;
		}
		x++;	//increment x each time as slope of tangent<1
		plot8way(x,y,xc,yc);
	}
}
 
void line(int xleft, int yleft, int xright, int yright)
{
	glColor3f(0,1,1);
	float yexact,xexact;	
	int x,y;	
	if(abs(m)<=1)
	{
		x=xleft;
		while(x<=xright)
		{
			yexact=m*x+c;
			y=round(yexact);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			x=x+1;
		}
	}
	else
	{
		y=yleft;
		while(y<=yright)
		{
			xexact=(y/m)-(c/m);
			x=round(xexact);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			y=y+1;
		}
	}
 
}
void display(void) {
 
	glClear(GL_COLOR_BUFFER_BIT);
 
	line(xleft,yleft,xright,yright);
	circle(xleft,yleft,50);
	circle(xright,yright,50);
	circle((xleft+xright)/2,(yleft+yright)/2,30);
	glutSwapBuffers();
}
 
int main(int argc, char **argv) {
 
 
	cout<<"\nEnter (xleft, yleft) :\n";
	cin>>xleft>>yleft;
	cout<<"\nEnter (xright, yright) :\n";
	cin>>xright>>yright;
 
	//computing slope and constant of the line equation y=mx+c
	m=(float)(yright-yleft)/(float)(xright-xleft);
	c=yleft-(m*xleft);	
//	cout<<"\nSlope : "<<m<<"\nConstant : "<<c<<"\n\n";
 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(900,600);
	glutCreateWindow("Success :)");
 
	// register callbacks
	glutDisplayFunc(display);
	myInit();
	// enter GLUT event processing cycle
	glutMainLoop();
 
	return 1;
 
}

