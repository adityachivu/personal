#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#define ROAD 60

using namespace std;


float road[ROAD];

struct building
{
	float base;
	float height;
	float z;
	float r;
	float g;
	float b;
}s[ROAD];	

typedef struct building building;

float dullness = 0;	

void drawGround()
{
    glColor3f(0.05f, 0.04f, 0.05f);
	glBegin(GL_QUADS);
		// Tar Road
		glVertex3f(-5.0f, 0.0f, -300.0f);
		glVertex3f(-5.0f, 0.0f,  10.0f);
		glVertex3f( 5.0f, 0.0f,  10.0f);
		glVertex3f( 5.0f, 0.0f, -300.0f);
	glEnd();
	
		// Side Markings - Constant
	glColor4f(1,1,1,0.5);
	glBegin(GL_QUADS);
		glVertex3f(-4.7f, 0.002f, -300.0f);
		glVertex3f(-4.7f, 0.002f,  10.0f);
		glVertex3f(-4.5f, 0.002f,  10.0f);
		glVertex3f(-4.5f, 0.002f, -300.0f);
		glVertex3f(4.7f, 0.002f, -300.0f);
		glVertex3f(4.7f, 0.002f,  10.0f);
		glVertex3f(4.5f, 0.002f,  10.0f);
		glVertex3f(4.5f, 0.002f, -300.0f);
	glEnd();
		
	glColor3f(0.9,0.8,0.9);
	glBegin(GL_QUADS);
		// Sidewalk - Concrete
		glVertex3f(-5.0f, 0.0f, -300.0f);
		glVertex3f(-5.0f, 0.0f,  10.0f);
		glVertex3f(-25.0f, 0.0f,  10.0f);
		glVertex3f(-25.0f, 0.0f, -300.0f);
		glVertex3f(5.0f, 0.0f, -300.0f);
		glVertex3f(5.0f, 0.0f,  10.0f);
		glVertex3f(25.0f, 0.0f,  10.0f);
		glVertex3f(25.0f, 0.0f, -300.0f);
	glEnd();
}

void drawColoredCube(float r, float g, float b)
{
	/*Draw a unit cube with specified colour of surfaces*/
	glColor4f(r, g, b, 1.0f);
	glBegin(GL_QUADS);
	// Top face
	    glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	    glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	// Bottom face
	    glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	    glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	// Front face
	    glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	    glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	    glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	// Back face
	    glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	    glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	// Left face
	    glVertex3f(-1.0 / 2, 1.0 / 2, 1.0 / 2);
	    glVertex3f(-1.0 / 2, 1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, -1.0 / 2);
	    glVertex3f(-1.0 / 2, -1.0 / 2, 1.0 / 2);
	// Right face
	    glVertex3f(1.0 / 2, 1.0 / 2, -1.0 / 2);
	    glVertex3f(1.0 / 2, 1.0 / 2, 1.0 / 2);
	    glVertex3f(1.0 / 2, -1.0 / 2, 1.0 / 2);
	    glVertex3f(1.0 / 2, -1.0 / 2, -1.0 / 2);
	glEnd(); // End of drawing color-cube
}

// Function to draw boundaries for the coloured cube

void drawCube(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawColoredCube(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(0.75, 1.0);
	drawColoredCube(r, g, b);
	glDisable(GL_POLYGON_OFFSET_FILL);
}

// The following code is used to simulate motion, without actually moving the camera
// (i.e) the Buildings and RoadMarkings are translated in the positive z direction
// so that it feels like the viewer is in motion 

// Function to draw building at a specified z coordinate,
// on either side of the road
// The RGB values on either side are rotated, but size remains constant

void drawBuilding(building b)
{
	glPushMatrix();
	glScaled(b.base,b.height,b.base);
	glTranslatef((15+b.base/2)/b.base,0.5,(b.z+b.base/2)/b.base);
	drawCube(b.r-dullness,b.g-dullness,b.b-dullness);
	glPopMatrix();
	
	glPushMatrix();
	glScaled(b.base,b.height,b.base);
	glTranslatef((-15-b.base/2)/b.base,0.5,(b.z+b.base/2)/b.base);
	drawCube(b.g-dullness,b.b-dullness,b.r-dullness);
	glPopMatrix();
}

// Initializing the scene, fixing the origin of drawing the building,
// Along with random values for Colour [RGB], Height and Base

void initBuildingScene()
{
	for(int i=0;i<ROAD;i++)
	{
		s[i].z= 5.0 * -i;
		s[i].height= (rand()%50+50)/10.0;
		s[i].base = (rand()%30+20)/10.0;
		s[i].r=(rand()%156+100)/256.0;
		s[i].g=(rand()%156+100)/256.0;
		s[i].b=(rand()%156+100)/256.0;
		drawBuilding(s[i]);
	}
}

// To draw any set of buildings

void drawBuildingScene()
{
	for(int i=0;i<ROAD;i++)
	{
		drawBuilding(s[i]);
	}
}

// Renders screen, and checks for building overflow condition

void renderBuilding()
{
	for ( int i = 0; i < ROAD; i++ )
	{
		s[i].z += 0.1f;
	}
	if ( s[0].z >= 10.0 )
	{
		for ( int i = 0; i < ROAD - 1; i++ )
		{
			s[i] = s[i + 1];    
		}
		s[ROAD-1].height= (rand()%50+50)/10.0;
		s[ROAD-1].base = (rand()%30+20)/10.0;
		s[ROAD-1].r=(rand()%106+150)/256.0;
		s[ROAD-1].g=(rand()%106+150)/256.0;
		s[ROAD-1].b=(rand()%106+150)/256.0;
		s[ROAD-1].z = -((ROAD - 2) * 5.0f);
	}			
	drawBuildingScene();
}

// Draws a single road marking on the road
void drawRoadMarking(float pz)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0,0.002,pz);
	glBegin(GL_QUADS);
		glVertex3f(-0.15f, 0.0f, -1.0f);
		glVertex3f(-0.15f, 0.0f,  1.0f);
		glVertex3f( 0.15f, 0.0f,  1.0f);
		glVertex3f( 0.15f, 0.0f, -1.0f);
	glEnd();
	glPopMatrix();	
}

// Initializing the location for each marking
// Since no other parameter changes, only individual origin is updated.
void initRoad()
{
	for ( int i = 0; i < ROAD; i++)
	{
		road[i] = 5.0 * -i;
		drawRoadMarking(road[i]);
	}
}

// Following functions are used to create and render the moving strip in the
// middle of the road
void drawRoad()
{
	for ( int i = 0; i < ROAD; i++)
	{
		drawRoadMarking(road[i]);
	}
}
void renderRoad()
{
	for ( int i = 0; i < ROAD; i++ )
	{
		road[i] += 0.1f;
	}
	if ( road[0] >= 10.0 )
	{
		for ( int i = 0; i < ROAD - 1; i++ )
		{
			road[i] = road[i + 1];
		}
		road[ROAD-1] = -((ROAD - 2) * 5.0f);
	}			
	drawRoad();
}
