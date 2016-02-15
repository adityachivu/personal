// Assignment 1 - Algorithm 3 (Wetherell and Shannon)
// Tidy Tree Drawing
// Combines both Algorithm 1 and 2 to meet both aesthetics (most of the time)
// - minimum width tree drawing
// - parent centered around children

// Modified Algorithm 3 in assignCoordinates2() at end

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <GL/glut.h>

#include <cmath>
#include <vector>

using namespace std;


//Node data structure used for coordinate assignment and drawing
struct node
{
	//Empty for current application
	int data;
	
	//Values determined by tree specification
	vector<int> children;
	int parent;
	int height;

	//Values for processing by graphics component
	int x,y;
	int status;
	int modifier;

	//Initialization list
	node() : data(0), x(-1), y(-1), status(0), height(0), modifier(0) {}
};

//Enumeration for status field in node structure
enum {NIL, FIRST_VISIT, LEFT_VISIT, RIGHT_VISIT};

//Spacing constants
int spacing;
int r;      

//Global data structures and variables
//Main data structure is dynamic array (vector) tree
//Parent vector is passed from main to the tree builder routine
//N is the size of tree, taken at runtime
//max_height is globally used both for coordinate assignment and drawing functions
vector<node> tree;
vector<int> parent;
int N;
int max_height;

//Prompt at runtime to specify tree by size and parent array
void readTree()
{
	cout<<"Enter number of nodes in tree : ";
	cin>>N;
	
	//Dynamically allocate memory for vector of size N
	parent.resize(N);
	//-1 is symbolic for NIL
	parent[0] = -1;

	int temp;
	for(int i=1;i<N;i++)
	{
		cout<<"Enter "<<i<<"'s parent : ";
		cin>>temp;
		if(temp>=i)
		{
			//A lower-numbered node cannot have a higher-numbered parent
			cout<<"Invalid parent.";
			i--;
			continue;
		}
		parent[i] = temp;
	}
}

//Build internal representation of tree from parental array
//by populating tree vector
void buildTree()
{
	tree.resize(N);
	for(int i=0;i<N;i++)
	{
		if(parent[i]==-1)
		{
			tree[i].height = 0;
			tree[i].parent = -1;
			continue;
		}

		//We get around using pointers by using the concept of parent and child indexes
		//to traverse the tree
		tree[i].parent = parent[i];
		tree[parent[i]].children.push_back(i);
		
		//Update height of new node w.r.t to parent
		//Also store max height so far
		tree[i].height = tree[parent[i]].height + 1;
		max_height = max(tree[i].height, max_height);
	}
}

//Command-line output for debugging
void printTree()
{
	for(int i=0;i<N;i++)
	{
		cout<<"Node "<<i<<" : ";
		vector<int> tempv = tree[i].children;
		if(tempv.size()==0)
			cout<<"Leaf node. ";
		else
			for(int j=0;j<tempv.size();j++)
				cout<<tempv[j]<<" ";
		cout<<"Height : "<<tree[i].height;
		cout<<" x = "<<tree[i].x;
		cout<<" y = "<<tree[i].y;
		cout<<"\n";
	}
}

//Algorithm 3 for coordinate assignment
//Satisfies both aesthetics while minimizing paper width most of the time
void assignCoordinates()
{
	//Variables required by algorithm
	int modifier[max_height+1];
	int next_pos[max_height+1];

	for(int i=0;i<=max_height;i++)
		{modifier[i] = 0, next_pos[i] = 1;}

	//Initiate traversal from tree
	node* current = &tree[0];
	current->status = FIRST_VISIT;
	//Flag is to indicate when NIL has been reached i.e when parent=-1
	bool flag = true;

	while(flag)
	{
		//Iterative traversal through status markers
		switch(current->status)
		{
			//POST-ORDER TRAVERSAL
			case FIRST_VISIT:
								//Move to LEFT section from node
								current->status = LEFT_VISIT;
								if(current->children.size()>0)
								{
									current = &tree[current->children[0]];
									current->status = FIRST_VISIT; 
								}
								break;
			case LEFT_VISIT:
								//LEFT section visited, now visit RIGHT section
								current->status = RIGHT_VISIT;
								if(current->children.size()>1)
								{
									current = &tree[current->children[1]];
									current->status = FIRST_VISIT;
								}
								break;
			case RIGHT_VISIT:
								//After RIGHT, two possibilities arise
								//We are on a leaf or an internal node

								//We need to adjust the place of this node accordingly
								int h = current->height;
								bool is_leaf = (current->children.size()==0);
								int place;

								//Use algorithm 1's concept if a leaf
								if(is_leaf)
									place = next_pos[h];
								//If only one child, keep child below parent
								else if(current->children.size()<2)
									place = tree[current->children[0]].x;
								//If both children, take average of positions and assign
								else
									place = (tree[current->children[0]].x + tree[current->children[1]].x)/2;
								
								//Compute modifier for second traversal
								modifier[h] = max(modifier[h], next_pos[h] - place);
								if(is_leaf)
									current->x = place;
								else
									current->x = place + modifier[h];
								current->modifier = modifier[h];
								
								//Update next_pos for current height
								next_pos[h] = current->x + 2;
								
								//Go up level and visit parent
								if(current->parent!=-1)
									current = &tree[current->parent];
								//If parent==-1, means we have reached NIL
								else
									flag = false;
								break;
		}
	}

	//Set traversal variables to initial values for second traversal
	current = &tree[0];
	current->status = FIRST_VISIT;
	int modifier_sum = 0;
	flag = true;

	while(flag)
	{
		//POST-ORDER traversal
		switch(current->status)
		{
			case FIRST_VISIT:
								//Pass down modifier_sum down the tree
								//Set x,y coordinates for current node
								current->x = current->x + modifier_sum;
								modifier_sum = modifier_sum + current->modifier;
								current->y = 2*current->height + 1;
								//Move to left section of tree
								current->status = LEFT_VISIT;
								if(current->children.size()>0)
								{
									current = &tree[current->children[0]];
									current->status = FIRST_VISIT;
								}
								break;
			case LEFT_VISIT:
								//Same as previous traversal, move from left to right
								current->status = RIGHT_VISIT;
								if(current->children.size()>1)
								{
									current = &tree[current->children[1]];
									current->status = FIRST_VISIT;
								}
								break;
			case RIGHT_VISIT:
								//Traverse upwards
								//Do not pass up the same modifier sum up the tree
								modifier_sum = modifier_sum - current->modifier;
								if(current->parent!=-1)
									current = &tree[current->parent];
								else
									flag = false;
								break;
		}
	}
}

//Required initializations for a 2D workspace
void init2D()
{ 
	//Black background
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Set working matrix to projection for loading identity matrix to specify non-rotated
	//orthogonal plane
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Orthogonally defined clipped plane
	gluOrtho2D(0.0, 900.0, 0.0, 600.0);
	//Reset working matrix to MODELVIEW to work with the tree
	glMatrixMode(GL_MODELVIEW);
}

//Called by drawCircle function to plot a point in 8 symmetric sections
//drawCircle only executes midpoint algorithm on an octant
//This helps replicate all the octants to form a circle 
void plot8symmetry(int x, int y, int xc, int yc)
{
	//Set color to blue
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

void drawCircle(int xc, int yc, int r)
{
	//Start point is (0,r) and decision parameter is set.
	int x = 0, y = r; 
	int d = 1-r;
	
	//Plot the first point
	plot8symmetry(x, y, xc, yc);
	
	//  Loop to cover points from y axis to a y where circle's slope = 1 (to exploit 8-way symmetry)
	while(y >= x)	        
	{
		if(d < 0)				//  If d < 0, choose EAST point
			d += 2*x + 3;   	//  Update rule using first derivative of implicit equation of circle.
		else					//  SOUTHEAST point chosen
		{
			d += 2*(x-y) + 5;
			y--;
		}
		x++;
		//Plot the new generated pointS
		plot8symmetry(x, y, xc, yc);
	}
}

//Line drawing algorithm
void drawLine(int xleft, int yleft, int xright, int yright)
{
    // Set color to cyan
	glColor3f(0,1,1);
	
	//Line drawing constants
	float m, c;
	
	//If slope = infinity special case
	if(xleft==xright)
	{
	    int count = yright - yleft;
	    int add;

	    //Need to handle for both cases where one point is up, other down;
	    //vice versa
	    if (yright>yleft)
	        add = 1;	        
	    else
	        add = -1;
	    
	    count = abs(count);
	    
	    while(count--)
	    {
	        glBegin(GL_POINTS);
			    glVertex2i(xleft, yleft);
		    glEnd();
		    yleft += add;
		}
    }

	else
	{
	    // Compute Straight Line constants.    
	    m = (float)(yright-yleft) / (float)(xright-xleft);
	    c = yleft - (m*xleft);
	   
	   	// Need to round to integral pixel coordinates
	    float yexact, xexact;
		int x, y;	
	    
	    //Absolute value of slope is <=1 case
	    if(abs(m) <= 1)
	    {
	        x = xleft;
		    while( x <= xright )
		    {
		        yexact = m*x + c;
		        y = round(yexact);
		        glBegin(GL_POINTS);
			        glVertex2i(x, y);
		        glEnd();
		        x++;
		    }
	    }

	    //Absolutee value of slope >=1 case
	    else
	    {
	    	//Since the function parameters are sorted by x
	    	//We need to account for the ordering in y
	    	//This handles one such case
	    	if(yleft<yright)
	    	{
		    	y = yleft;
			    while( y <= yright )
			    {
				    xexact = (y/m) - (c/m);
				    x = round(xexact);
				    glBegin(GL_POINTS);
					    glVertex2i(x, y);
				    glEnd();
				    y++;
			    }
			}

			//This handles the other ordering in y
			else
			{
				y = yleft;
			    while( y >= yright )
			    {
				    xexact = (y/m) - (c/m);
				    x = round(xexact);
				    glBegin(GL_POINTS);
					    glVertex2i(x, y);
				    glEnd();
				    y--;
			    }
			}
		}
    }
}

//Line drawing from node to node
//Calculates the periphery points of both nodes to draw line between
void linen2n(int x1, int y1, int x2, int y2)
{
	cerr<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
    float xleft, xright, yleft, yright;
    
    //Euclidean distance between two nodes.
    float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    
    //Locate Perimeter point of node to draw line from.
    xleft = x1 + r*(x2-x1)/dist;
    yleft = y1 + r*(y2-y1)/dist;
    
    xright = x2 + r*(x1-x2)/dist;
    yright = y2 + r*(y1-y2)/dist;
	
	//Draw line.
	drawLine(xleft, yleft, xright, yright);
	
}

//Main tree drawing function
//Composed of circle for node and line from node to node
void drawTree(void) {

	glClear(GL_COLOR_BUFFER_BIT);
    
    int xl, xr, yl, yr;
    drawCircle(tree[0].x, tree[0].y, r);

    for(int i=1; i<N; i++)
    {
        xl = tree[i].x;
        yl = tree[i].y;
        
        xr = tree[tree[i].parent].x;        
        yr = tree[tree[i].parent].y;
        
        drawCircle(xl, yl, r);
       
        if(xl<xr)
          	linen2n(xl, yl, xr, yr);
        else
            linen2n(xr, yr, xl, yl);        
    }

	glutSwapBuffers();
}

//Horizontal = vertical spacing
//r is radius of circle used for nodes
//Reassign coordinates based on spacing parameters
void setSpacingParameters()
{
	spacing = min(40, 600 / (max_height + 1));
	r = spacing / 4;

	for(int i=0;i<N;i++)
	{
		tree[i].x = spacing*tree[i].x;
		tree[i].y = 600 - spacing*tree[i].y;
	}
}

//Algorithm 3 for coordinate assignment (modified as per paper)
//Satisfies both aesthetics while minimizing paper width
void assignCoordinates2()
{
	//Variables required by algorithm
	int modifier[max_height+1];
	int next_pos[max_height+1];

	for(int i=0;i<=max_height;i++)
		{modifier[i] = 0, next_pos[i] = 1;}

	//Initiate traversal from tree
	node* current = &tree[0];
	current->status = FIRST_VISIT;
	//Flag is to indicate when NIL has been reached i.e when parent=-1
	bool flag = true;

	while(flag)
	{
		//Iterative traversal through status markers
		switch(current->status)
		{
			//POST-ORDER TRAVERSAL
			case FIRST_VISIT:
								//Move to LEFT section from node
								current->status = LEFT_VISIT;
								if(current->children.size()>0)
								{
									current = &tree[current->children[0]];
									current->status = FIRST_VISIT; 
								}
								break;
			case LEFT_VISIT:
								//LEFT section visited, now visit RIGHT section
								current->status = RIGHT_VISIT;
								if(current->children.size()>1)
								{
									current = &tree[current->children[1]];
									current->status = FIRST_VISIT;
								}
								break;
			case RIGHT_VISIT:
								//After RIGHT, two possibilities arise
								//We are on a leaf or an internal node

								//We need to adjust the place of this node accordingly
								int h = current->height;
								bool is_leaf = (current->children.size()==0);
								int place;

								//Use algorithm 1's concept if a leaf
								if(is_leaf)
									place = next_pos[h];
								//If only one child, keep child below parent
								else if(current->children.size()<2)
									place = tree[current->children[0]].x;
								//If both children, take average of positions and assign
								else
									place = (tree[current->children[0]].x + tree[current->children[1]].x)/2;
								
								//Compute modifier for second traversal
								modifier[h] = max(modifier[h], next_pos[h] - place);
								if(is_leaf)
									current->x = place;
								else
									current->x = place + modifier[h];
								current->modifier = modifier[h];
								
								//Update next_pos for current height
								next_pos[h] = current->x + 2;
								
								//Go up level and visit parent
								if(current->parent!=-1)
									current = &tree[current->parent];
								//If parent==-1, means we have reached NIL
								else
									flag = false;
								break;
		}
	}

	//Set traversal variables to initial values for second traversal
	//MODIFICATIONS BEGIN HERE
	for(int i=0;i<=max_height;i++)
		next_pos[i] = 1;
	current = &tree[0];
	current->status = FIRST_VISIT;
	int modifier_sum = 0;
	flag = true;

	while(flag)
	{
		switch(current->status)
		{
			case FIRST_VISIT:
								//Pass down modifier_sum down the tree
								modifier_sum = modifier_sum + current->modifier;
								current->status = LEFT_VISIT;
								//Move to left section of tree
								if(current->children.size()>0)
								{
									current = &tree[current->children[0]];
									current->status = FIRST_VISIT;
								}
								break;
			case LEFT_VISIT:
								//Main modifications here
								//Discussed on Page 519 of paper
								current->x = min(next_pos[current->height], 
									current->x+modifier_sum-current->modifier);
								if(current->children.size()>0)
									current->x = max(current->x, tree[current->children[0]].x+1);
								if(current->parent!=-1)
									if(tree[current->parent].status==RIGHT_VISIT)
										current->x = max(current->x, tree[current->parent].x+1);
								//This helps eliminate worst case drawings
								next_pos[current->height] = current->x + 2;
								current->y = 2*current->height + 1;

								current->status = RIGHT_VISIT;
								if(current->children.size()>1)
								{
									current = &tree[current->children[1]];
									current->status = FIRST_VISIT;
								}
								break;
			case RIGHT_VISIT:
								//Traverse upwards
								//Do not pass up the same modifier sum up the tree again
								modifier_sum = modifier_sum - current->modifier;
								if(current->parent!=-1)
									current = &tree[current->parent];
								else
									flag = false;
								break;
		}
	}
}

int main(int argc, char* argv[])

{
	//Read, build and assign coordinates to tree nodes according to Algorithm 3
	readTree();
	buildTree();
	printTree();
	assignCoordinates();
	printTree();

	//GLUT setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(900,600);
	glutCreateWindow("Algorithm 3");

	//Spacing Parameter set and reassigning tree node coordinates
	setSpacingParameters();

	//Display and initialize 2D setup
	glutDisplayFunc(drawTree);
	init2D();
	glutMainLoop();

	return 0;
}

