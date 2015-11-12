//
//
//
//  SIMPLE TREE DRAWING PROGRAM IN OPENGL.
//
//
//
//
//



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>


using namespace std;



//  GLOBAL VARIABLES

vector < pair < int, int> > pos;        //  Stores position of all nodes after input.
int *parent;                            //  Array containing parent of ith node.
int *height;                            //  Array containing height of ith node.
int *maxwh;
int n;                                  //  Number of nodes.
int maxh = 0;
int maxw = 0;
int spacing;//Spacing of between nodes.
int r;      //  Radius of circle.
float m, c; //  Line constants.

void myInit()
{ 
	// attributes
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// setting up viewing
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 900.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
}

void plot8way(int x, int y, int xc, int yc) //  Plot 8 symmetrical points for circle with centre (xc, yc)
{
    // Set color.
	glColor3f(0,0,1);
	
	//  Draw type.
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
	int x = 0, y = r;   //  Initial conditions
	int d = 1-r;		    //  Decision parameter d to determine region of midpoint
	
	plot8way(x, y, xc, yc); //  First point.
	
	while(y >= x)	        //  Loop to cover points from y axis to slope = 1 (to exploit 8-way symmetry)
	{
	
		if(d < 0)			//  if d < 0, choose east point
		{
			d += 2*x + 3;   //  Update rule using first derivative of implicit equation of circle.
		}
		else
		{
			d += 2*(x-y) + 5;
			y--;
		}
		x++;
		
		plot8way(x, y, xc, yc);
	}
}

void line(int xleft, int yleft, int xright, int yright)
{
    //  Set color
	glColor3f(0,1,1);
	
	//  If vertical line.
	if (xleft == xright )
	{
	    int count = yright - yleft;
	    int add;
	    if ( yright > yleft )
	        add = 1;	        
	    else
	        add = -1;
	    
	    count = abs(count);
	    
	    while ( count-- )
	    {
	        glBegin(GL_POINTS);
			    glVertex2i(xleft, yleft);
		    glEnd();
		    yleft += add;
		}
    }
	else
	{
	    //  Straight Line constants.
	    int dy = (yright-yleft);
	    int dx = (xright-xleft); 
	    m = (float)dy / (float)dx;
	    c = yleft - (m*xleft);
	    
	    
	    
	    int add;
	    if ( dy < 0 )
	    {
	        add = -1;
	        dy = -dy;
	    }
	    else
	        add = 1;
	        
	    int d = 2 * dy - dx;
	    int incrE = 2 * dy;
	    int incrNE = 2 * (dy - dx);
	    
	    
	    float yexact, xexact;	
	    int x = xleft, y = yleft;	
	    if( abs(m) <= 1 )
	    {
	        x = xleft;
		    while( x <= xright )
		    {
		        if ( d < 0 )
		        {
		            d += incrE;
		        }
		        else
		        {
		            d += incrNE;
		            y += add;
		        }
		        glBegin(GL_POINTS);
			        glVertex2i(x, y);
		        glEnd();
		        x++;
		    }
		
		
	    }
	    else
	    {
		    y = yleft;
		    while( y <= yright )
		    {
			    if ( d < 0 )
		        {
		            d += incrE;
		        }
		        else
		        {
		            d += incrNE;
		            x += add;
		        }
		        glBegin(GL_POINTS);
			        glVertex2i(x, y);
		        glEnd();
		        y++;
		    }
		 }
    }
}

void linen2n(int x1, int y1, int x2, int y2)
{
    float xleft, xright, yleft, yright;
    
    //  Euclidean distance between two nodes.
    float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    
    //  Locate Perimeter point of node to draw line from.
    xleft = x1 + r*(x2-x1)/dist;
    yleft = y1 + r*(y2-y1)/dist;
    
    xright = x2 + r*(x1-x2)/dist;
    yright = y2 + r*(y1-y2)/dist;
	
	//  Draw line.
	line(xleft, yleft, xright, yright);
	
}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
    
    int xl, xr, yl, yr;
    for ( int i = 0; i < n; i++)
    {
        xl = pos[i].first;
        yl = pos[i].second;
        
        xr = pos[parent[i]].first;        
        yr = pos[parent[i]].second;
        
        circle(xl, yl, r);
        
        if ( xl < xr )
            linen2n(xl, yl, xr, yr);
        else
            linen2n(xr, yr, xl, yl);
            
    }
    
    
	glutSwapBuffers();
}

int main(int argc, char **argv) {


	cout << "Enter number of nodes: ";
	cin >> n;
	
	//  Allocate required memory
	pos.resize(n);
	parent = (int*)malloc(sizeof(int) * n);
	height = (int*)malloc(sizeof(int) * n);
	maxwh = (int*)malloc(sizeof(int) *n);
	
	memset( parent, 0, sizeof(int) * n);
	memset( height, 0, sizeof(int) * n);
	memset( maxwh, 0, sizeof(int) * n);
		
	cout << "\n\n\nNumber nodes of same level from left to right and Deeper levels with strictly greater numbers.";
	cout << "\n\nnode 0 is root, node 1 is child of root (node 0)";
	
	for ( int i = 2; i < n; i++)
	{
	    cout << "\nEnter parent of node " << i << ": ";
	    cin >> parent[i];
	}
	
	for ( int i = 0; i < n; i++)
	{
	    height[i] = height[parent[i]] + 1;
	    maxwh[height[i]]++;	    
	}
	
	for ( int i = 0; i < n; i++)
	{
	    if ( height[i] > maxh)
	        maxh = height[i];
	    if ( maxwh[i] > maxw)
	        maxw = maxwh[i];
	}
	
	int space;
	if (maxh > maxw)
	    space = maxh;
	else
	    space = maxw;
	    
	spacing = 600 / (space + 1);
	r = spacing / 4;
	
	
    
    int xcur = 2*r, ycur = 600 - xcur, curh = 1;
    for ( int i = 0; i < n;)
    {
        xcur = 2*r;
        
        
        while(height[i] == curh)
        {
            pos[i].first = xcur;
            pos[i].second = ycur;
            xcur += spacing;
            i++;
        }
        ycur -= spacing;
        curh++;
    }
    
    for ( int i = 0; i < n; i++)
	{
	    cout << "node " << i << ": height: " << height[i] << " parent: " << parent[i];
	    cout << "  position: " << pos[i].first << " " << pos[i].second << endl;
	}
    
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
