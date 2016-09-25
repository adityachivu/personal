#ifndef VERTEX_H
#define VERTEX_H

#include "../point.h"

class HalfEdge;
class Point;

enum vtype { split, merge, top, bottom, leftregular, rightregular };

class Vertex
{
private:
	HalfEdge* IncidentEdge;
	Point pos;
	vtype type;
	int vID;

protected:

public:
	Vertex( int v )
		:IncidentEdge( NULL ), vID( v )
	{

	}

	Vertex( Point pt, int v )
		:pos( pt ), IncidentEdge( NULL ), vID( v )
	{
		
	}

	Point& getPos() 
	{
		return this->pos;
	}

	void setIncEdge( HalfEdge* e )
	{
		this->IncidentEdge = e;
	}

	HalfEdge* getIncEdge() const
	{
		return this->IncidentEdge;
	}

	int getVertexID()
	{
		return this->vID;
	}
	void setType( vtype t )
	{
		this->type = t;
	}
	vtype getType()
	{
		return this->type;
	}


};

#endif