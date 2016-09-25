#ifndef EDGEITERATOR_H
#define EDGEITERATOR_H

#include "../point.h"
#include "../segment.h"


class HalfEdge;
class Vertex;
class Face;

class EdgeIterator
{
private:

	HalfEdge* original;
	HalfEdge* current;
	bool type;
	bool itflag;

public:

	EdgeIterator()
		:itflag( false )
	{

	}
	EdgeIterator( Face* f )
		:original( f->getIncEdge() ), current( f->getIncEdge() ), type( true ), itflag( false )
	{

	}

	EdgeIterator( Vertex* v )
		:original( v->getIncEdge() ), current( v->getIncEdge() ), type( false ), itflag( false )
	{

	}

	EdgeIterator( HalfEdge* e )
		:original( e ), current( e ), type( true ), itflag( false )
	{

	}

	bool hasNext();
	HalfEdge* set( Face* );
	HalfEdge* set( Vertex* );
	HalfEdge* set( HalfEdge* );
	HalfEdge* next();
	HalfEdge* prev();
	HalfEdge* getHalfEdge();

};

bool EdgeIterator::hasNext()
{
	if( itflag )
	{
		if( original == current )
			return false;
		else
			return true;	
	}

	return true;
	
}

HalfEdge* EdgeIterator::set( Face* f )
{
	original = f->getIncEdge();
	current = original;
	type = true;
	itflag = false;
	return current;
}

HalfEdge* EdgeIterator::set( Vertex* v )
{
	original = v->getIncEdge();
	current = original;
	type = false;
	itflag = false;
	return current;
}

HalfEdge* EdgeIterator::set( HalfEdge* e )
{
	original = e;
	current = original;
	type = true;
	itflag = false;
	return current;
}

HalfEdge* EdgeIterator::next()
{
	itflag = true;
	if( type )
	{
		current = current->getNext();
	}
	else
	{
		current = current->getNext()->getTwin();
	}
	return current;
}

HalfEdge* EdgeIterator::prev()
{
	itflag = true;
	if( type )
	{
		current = current->getPrev();
	}
	else
	{
		current = current->getTwin()->getPrev();
	}
	return current;
}

HalfEdge* EdgeIterator::getHalfEdge()
{
	return current;
}

#endif