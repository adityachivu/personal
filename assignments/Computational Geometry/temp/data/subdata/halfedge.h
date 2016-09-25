#ifndef HALFEDGE_H
#define HALFEDGE_H


#include "face.h"
#include "vertex.h"
//#include "edgeiterator.h"
#include "../segment.h"


class Segment;

class HalfEdge
{
private:
	HalfEdge* next;
	HalfEdge* prev;
	HalfEdge* twin;
	Face* IncidentFace;
	Vertex* origin;
	Segment edge;

public:

	HalfEdge()
		:next( NULL ), prev( NULL ), twin( NULL ), IncidentFace( NULL ), origin( NULL )
	{

	}

	void setNext( HalfEdge* e )
	{
		this->next = e;
		e->prev = this;
	}

	HalfEdge* getNext() const
	{
		return this->next;
	}

	void setPrev( HalfEdge* e )
	{
		this->prev = e;
		e->next = this;
	}

	HalfEdge* getPrev() const
	{
		return this->prev;
	}

	void setTwin( HalfEdge* e )
	{
		this->twin = e;
		e->twin = this;
	}

	HalfEdge* getTwin() const
	{
		return this->twin;
	}

	void setFace( Face* e )
	{
		this->IncidentFace = e;
	}

	Face* getFace() const
	{
		return this->IncidentFace;
	}

	void setOrigin( Vertex* v )
	{
		this->origin = v;
	}

	Vertex* getOrigin() const
	{
		return this->origin;
	}

	Segment& getSegment()
	{
		return this->edge;
	}

};

#endif