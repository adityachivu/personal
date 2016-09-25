#ifndef MESH_H
#define MESH_H

#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <string>

#include "subdata/face.h"
#include "subdata/halfedge.h"
#include "subdata/vertex.h"
#include "subdata/edgeiterator.h"

class Mesh
{
private:

	std::vector<Vertex> vertices;
	std::vector<HalfEdge> edges;
	std::vector<Face> faces;

	int nfaces, nedges, nvertices;
	//struct compare;

	

public:	

	Mesh()
		:nfaces(0), nedges(0), nvertices(0)
	{

	}

	Vertex* createVertex();
	HalfEdge* createHalfEdge();
	Face* createFace();
	
	std::vector<Vertex>& getVertices();
	std::vector<Face>& getFaces();
	std::vector<HalfEdge>& getHalfEdges();
	

	void createPolyMesh( std::vector<Point> );

	void addEdge( Vertex* , Vertex* );
	void addEdge( int , int );

	void printMesh();
	Face* printFace( int );
	void printVertices();
	Vertex* printVertex( int );
	void makeYmonotone();
	void triangulate();

};

std::vector<Vertex>& Mesh::getVertices()
{
	return this->vertices;
}

std::vector<Face>& Mesh::getFaces()
{
	return this->faces;
}

std::vector<HalfEdge>& Mesh::getHalfEdges()
{
	return this->edges;
}

Vertex* Mesh::createVertex()
{
	this->vertices.push_back( Vertex( nvertices ) );
	Vertex *v = &this->vertices.back();
	nvertices++;
    return &this->vertices.back();
}

HalfEdge* Mesh::createHalfEdge()
{
	this->edges.push_back( HalfEdge() );
	nedges++;
    return &this->edges.back();
}

Face* Mesh::createFace()
{
	this->faces.push_back( Face( nfaces ) );
	nfaces++;
    return &this->faces.back();
}

void Mesh::createPolyMesh( std::vector<Point> vertexlist )
{
	int num = vertexlist.size();

	getVertices().reserve( num );
	getFaces().reserve( num );
	getHalfEdges().reserve( num * 4 );
	
	for ( int i = 0; i < vertexlist.size(); i++ )
	{
		createVertex()->getPos().coord( vertexlist[i].getPos() );	
	}

	Face* exterior = createFace();
	Face* interior = createFace();

	for ( int i = 0; i < vertices.size(); i++ )
	{
		HalfEdge* e = createHalfEdge();
		HalfEdge* etwin = createHalfEdge();
		Vertex* v = &vertices[i];

		e->setTwin( etwin );
		
		e->setFace( exterior );
		etwin->setFace( interior );

		e->setOrigin( v );
		v->setIncEdge( etwin );
	}	

	HalfEdge *first, *firsttwin, *curr;

	first = &edges.front();
	firsttwin = first->getTwin();

	exterior->setIncEdge( first );
	interior->setIncEdge( firsttwin );

	for ( int i = 0; i < edges.size() - 2; i+=2 )
	{
		curr = &edges[i];
		HalfEdge *temp = &edges[i+2];

		curr->setNext( temp );
	}

	for ( int i = 1; i < edges.size() - 2; i+=2 )
	{
		curr = &edges[i];
		HalfEdge *temp = &edges[i+2];

		curr->setPrev( temp );
		curr->setOrigin( curr->getPrev()->getTwin()->getOrigin() );

	}

	HalfEdge *last, *lasttwin;
	
	lasttwin = &edges.back();
	last = lasttwin->getTwin();	
	
	last->setNext( first );
	lasttwin->setPrev( firsttwin );
	lasttwin->setOrigin( &vertices.front() );	
	std::cout << "polygon generated\n";
}

void Mesh::addEdge( Vertex* v1, Vertex* v2 )
{
	
	Face* f = createFace();

	HalfEdge* e = createHalfEdge();
	HalfEdge* etwin = createHalfEdge();
	
	//set pointers
	f->setIncEdge( e );
	e->setOrigin( v2 );
	etwin->setOrigin( v1 );
	e->setTwin( etwin );
	
	EdgeIterator it;
	Point axis;
	std::vector< std::pair< float, HalfEdge* > > pos;

	it.set( v1 );
	axis = it.getHalfEdge()->getOrigin()->getPos();

	pos.push_back( std::make_pair( 2*PI, it.getHalfEdge() ) );

	//vertex list of neighbours
	while( it.hasNext() )
	{
		HalfEdge* e = it.getHalfEdge();
		
		double angle = angleBetween( axis, v1->getPos(), e->getOrigin()->getPos() );
		pos.push_back( std::make_pair( angle, e ) );
		it.next();
	}
	
	//sorted by angle
	std::sort( pos.begin(), pos.end() );
	double angle = angleBetween( axis, v1->getPos(), v2->getPos() );

	HalfEdge *temp;

	//identify vertices to place edge in between
	for( int i = 0; i < pos.size(); i++ )
	{
		temp = pos[i].second;
		if( pos[i].first > angle )
			break;
	}

	//set edge pointers
	temp = temp->getTwin();
	etwin->setPrev( temp->getPrev() );
	e->setNext( temp );


	//repeat for second vertex
	it.set( v2 );
	axis = it.getHalfEdge()->getOrigin()->getPos();
	pos.resize(0);

	//vertex list of neighbours
	while( it.hasNext() )
	{
		
		HalfEdge* e = it.getHalfEdge();

		double angle = angleBetween( axis, v2->getPos(), e->getOrigin()->getPos() );
		pos.push_back( std::make_pair( angle, e ) );
		it.next();
	}

	//sort by angle
	std::sort( pos.begin(), pos.end() );
	angle = angleBetween( axis, v2->getPos(), v1->getPos() );

	//identify vertices to place edge in between
	for( int i = 0; i < pos.size(); i++ )
	{
		temp = pos[i].second;
		if( pos[i].first > angle )
			break;
	}

	//set edge pointers
	temp = temp->getTwin();
	e->setPrev( temp->getPrev() );
	etwin->setNext( temp );


	//reset face pointers for all edges
	it.set( f );
	while( it.hasNext() )
	{
		HalfEdge *e = it.getHalfEdge();
		e->setFace( f );
		it.next();
	}

	//repeat for second face
	f = etwin->getPrev()->getFace();
	f->setIncEdge( etwin );
	it.set( etwin );
	while( it.hasNext() )
	{
		HalfEdge *e = it.getHalfEdge();
		e->setFace( f );
		it.next();
	}	
}

void Mesh::addEdge( int v1, int v2 )
{
	this->addEdge( &vertices[v1], &vertices[v2] );
}

void Mesh::printVertices()
{
	Vertex *v;
	
	for( int i = 0; i < vertices.size(); i++ )
	{
		EdgeIterator it( &vertices[i] );
		std::cout << "\nVertex " << i+1 <<" neighbours:\n";
		
		while( it.hasNext() )
		{
			printPoint( it.getHalfEdge()->getOrigin()->getPos() );
			it.next();
		}

	}

}

void Mesh::printMesh()
{	
	for ( int i = 0; i < faces.size(); i++ )
	{
		EdgeIterator it( &faces[i] );
		HalfEdge *e;
		int count = 1;
		e = it.getHalfEdge();

		std::cout << "\nFace " << e->getFace()->getFaceID() << "-" << std::endl;
		while( it.hasNext() )
		{
			std::cout << "point " << count << ": ";
			printPoint( e->getOrigin()->getPos() );
			e = it.next();
			count++;		
		}
	}
}

Face* Mesh::printFace( int fid )
{
	EdgeIterator it( &faces[fid] );
	while( it.hasNext() )
	{
		printPoint( it.getHalfEdge()->getOrigin()->getPos() );
		it.next();
	}
}
void Mesh::triangulate()
{
	makeYmonotone();
	
	//std::cout << "starttr\n";
	typedef std::pair< std::pair< Point, Vertex* >, bool > cand;
	
	int fnum = faces.size();
	for( int i = 1; i < fnum; i++ )
	{
		EdgeIterator it( &faces[i] );

		Point top, bottom;
		std::vector< cand > points, left, right;

		int count = 1;
		while( it.hasNext() )
		{
			HalfEdge *e = it.getHalfEdge();
			Vertex *v = e->getOrigin();
			if( e->getNext()->getOrigin()->getPos() < v->getPos() )
			{
				points.push_back( std::make_pair( std::make_pair( v->getPos(), v ), true ) );
				right.push_back( points.back() );
			}
			else
			{
				points.push_back( std::make_pair( std::make_pair( v->getPos(), v ), false ) );
				left.push_back( points.back() );
			}
			it.next();
			count++;
		}

		std::sort( points.begin(), points.end() );
		std::sort( left.begin(), left.end() );
		std::sort( right.begin(), right.end() );

		top = points.front().first.first;
		bottom = points.back().first.first;
		
		std::cout << "\nsorted points:\n";
		for( int i = 0; i < points.size(); i++ )
		{
			printPoint( points[i].first.first );
		}																																																	std::cout << points.size() <<" l:" << left.size() << " r:" << right.size() << "\n\n\n";
		std::stack< cand > addvertex;
		int lcount = 0, rcount = 0;

		points[0].second?rcount++:lcount++;
		addvertex.push( points[0] );
		points[1].second?rcount++:lcount++;
		addvertex.push( points[1] );

		printPoint( points[0].first.first );
		//std::cout << (bool)points[0].second;
		printPoint( points[1].first.first );
		//std::cout << (bool)points[1].second;
		
		std::cout << "\n\nstart\n\n";
		for( int i = 2; i < points.size()-1; i++ )
		{
			cand u = points[i];
			cand v = addvertex.top();
			v = addvertex.top();

			std::cout << "\n****new u****\nu: ";
			printPoint( u.first.first );

			if( u.second )
			{
				std::cout << "u on right, stack size: " << addvertex.size() << "\n";
				rcount++;

				if( u.second != v.second )
				{
					std::cout << "diffchain\n";
					while( not addvertex.empty() )
					{
						v = addvertex.top();
						addvertex.pop();
						std::cout << "\nconsidering v: ";
						printPoint( v.first.first );

						if( addvertex.empty() )
							break;

						std::cout << "\nAdding Edge:\n";
						printPoint( u.first.first );
						printPoint( v.first.first );
						addEdge( u.first.second, v.first.second );
						//printMesh();
					}

					addvertex.push( points[i-1] );
					addvertex.push( points[i] );
				}
				else
				{
					std::cout << "samechain\n";
					v = addvertex.top();
					cand prev = v;
					cand check = v;
					addvertex.pop();

					while( not addvertex.empty() )
					{
						v = addvertex.top();

						std::cout << "\nconsidering v:";
						printPoint( v.first.first );

						std::cout << "checking right turn with\n";
						printPoint( check.first.first );
						printPoint( u.first.first );
						printPoint( v.first.first );

						if( checkRightTurn( check.first.first, u.first.first, v.first.first ) )
						{
							std::cout << "\nAdding Edge:\n";
							printPoint( u.first.first );
							printPoint( v.first.first );
							addEdge( u.first.second, v.first.second );
							//printMesh();
							prev = v;
							addvertex.pop();
						}
						else
						{
							std::cout << "Push on stack\n";
							break;
						}
					}

					addvertex.push( prev );
					addvertex.push( u );
				}
			}
			else
			{
				std::cout << "u on left, size: " << addvertex.size() << "\n";
				lcount++;

				if( u.second != v.second )
				{
					std::cout << "diffchain\n";
					while( not addvertex.empty() )
					{
						v = addvertex.top();
						addvertex.pop();

						if( addvertex.empty() )
							break;

						std::cout << "\nAdding Edge:\n";
						printPoint( u.first.first );
						printPoint( v.first.first );
						addEdge( u.first.second, v.first.second );
						//printMesh();

					}

					addvertex.push( points[i-1] );
					addvertex.push( points[i] );
				}
				else
				{
					std::cout << "samechain\n";
					v = addvertex.top();
					cand prev = v;
					cand check = v;
					addvertex.pop();

					while( not addvertex.empty() )
					{
						v = addvertex.top();

						std::cout << "considering: ";
						printPoint( v.first.first );

						std::cout << "checking right turn with\n";
						printPoint( v.first.first );
						printPoint( u.first.first );
						printPoint( check.first.first );

						if( checkRightTurn( v.first.first, u.first.first, check.first.first ) )
						{
							std::cout << "\nAdding Edge:\n";
							printPoint( u.first.first );
							printPoint( v.first.first );
							addEdge( u.first.second, v.first.second );
							//printMesh();
							prev = v;
							addvertex.pop();
						}
						else
						{
							std::cout << "Push on stack\n";
							break;
						}
					}

					addvertex.push( prev );
					addvertex.push( u );
				}
			}
		}
		
		
		cand v = addvertex.top();
		cand u = points.back();
		addvertex.pop();

		std::cout << "u bottom. size: " << addvertex.size() << "\n";
		while( not addvertex.empty() )
		{
			std::cout << "botvert. size: " << addvertex.size() << "\n";
			v = addvertex.top();
			addvertex.pop();

			if( addvertex.empty() )
				break;
			
			std::cout << "\nAdding Edge\n";
			printPoint( u.first.first );
			printPoint( v.first.first );
			addEdge( u.first.second, v.first.second );
		}
	}
	std::cout << "endtr\n";
}
/*
struct Mesh::compare
{
	bool operator() (const int &lhs, const int &rhs) const
	{
         if( vertices[lhs].getPos() < vertices[lhs+1].getPos() )
         	return checkRightTurn( getVertices()[lhs].getPos(), vertices[lhs+1].getPos(), vertices[rhs].getPos());
         else
         	return checkRightTurn( vertices[lhs+1].getPos(), vertices[lhs].getPos(), vertices[rhs].getPos());
    }
};*/
void Mesh::makeYmonotone()
{
	typedef std::vector< std::pair< Point, int > > priority;
	//typedef std::set< int, compare > status;

	priority Q;
	//status T;

	//Block to identify type of each vertex.
	EdgeIterator it( &(faces.back()) );
	while( it.hasNext() )
	{
		Point curr, next, prev;
		HalfEdge *e = it.getHalfEdge(); 
		Vertex *v = e->getOrigin();

		curr = v->getPos();
		next = e->getNext()->getOrigin()->getPos();
		prev = e->getPrev()->getOrigin()->getPos();

		if( checkRightTurn( prev, curr, next ) )
		{
			if( prev < curr )
			{
				if( next < curr )
					v->setType( merge );
				else
					v->setType( rightregular );
			}
			else
			{
				if( next < curr )
					v->setType( leftregular );
				else
					v->setType( split );
			}
		}
		else
		{
			if( prev < curr )
			{
				if( next < curr )
					v->setType( bottom );
				else
					v->setType( rightregular );
			}
			else
			{
				if( next < curr )
					v->setType( leftregular );
				else
					v->setType( top );
			}
		}
		Q.push_back( std::make_pair( curr, v->getVertexID() ) );
		it.next();
	}

	std::sort( Q.begin(), Q.end() );
	std::vector<int> helper( Q.size(), -1 );

	
	//Handle each vertex.
	std::cout << Q.size() << std::endl;
	for ( int i = 0; i < Q.size(); i++ )
	{
		std::string s;

		switch( vertices[Q[i].second].getType() )
		{
			case split:{
				s = "split";/*
				std::pair< float, int > temp = std::make_pair( Q[i].first.getPos().first, 0 );*/
			}break;
			case merge:{
				s = "merge";
			}break;
			case leftregular:{
				s = "leftregular";
			}break;
			case rightregular:{
				s = "rightregular";
			}break;
			case top:{
				s = "top";/*
				helper[i] = i;
				//if( vertices[i].getPos() < vertices[i+1].getPos() )
					//T.insert( std::make_pair( vertices[i+1].getPos().getPos().first, i ) );
				//else
					//T.insert( std::make_pair( vertices[i].getPos().getPos().first, i ) );*/
			}break;
			case bottom:{
				s = "bottom";/*
				if( vertices[helper[i-1]].getType() == merge )
				{
					addEdge( Q[i].second, helper[i-1] );
				}
				//T.erase( std::make_pair( Q[i].first.getPos().first, i-1 ) );*/
			}break;
			default:{
				s = "invalid";
			}
		}
		
		std::cout << "vertex " << Q[i].second << ": " << s << "\n";
		printPoint( Q[i].first );
	}


}
#endif