#ifndef HALFEDGE_H
#define HALFEDGE_H


template<class VertexDataT, class HalfEdgeDataT, class FaceDataT>
class VertexT;

template<class VertexDataT, class HalfEdgeDataT, class FaceDataT>
class FaceT;

template<class VertexDataT, class HalfEdgeDataT, class FaceDataT>
class HalfEdgeT
{
	typedef FaceT<VertexDataT, HalfEdgeDataT, FaceDataT> Face;
	typedef VertexT<VertexDataT, HalfEdgeDataT, FaceDataT> Vertex;
	typedef HalfEdgeT<VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;

private:

	HalfEdge* twin;
	HalfEdge* next;
	HalfEdge* prev;
	Face* face;
	Vertex* origin;
	HalfEdgeDataT data;

protected:

public:

	HalfEdgeT( HalfEdgeDataT edgeData = NULL )
		:data(edgeData), twin(NULL), next(NULL), prev(NULL), face(NULL), origin(NULL)
	{

	}

	HalfEdge* getTwin()
	{
		return this->twin;
	}

	void setTwin( HalfEdge* updatedtwin )
	{
		this->twin = updatedtwin;
	}

	HalfEdge* getNext()
	{
		return this->next;
	}

	void setNext( HalfEdge* updatednext )
	{
		this->next = updatednext;
	}

	HalfEdge* getPrev()
	{
		return this->prev;
	}

	void setPrev( HalfEdge* updatedprev )
	{
		this->prev = updatedprev;
	}

	Face* getFace()
	{
		return this->face;
	}

	void setFace( Face* updatedface )
	{
		this->face = updatedface;
	}

	Vertex* getOrigin()
	{
		return this->origin;
	}

	void setOrigin( Vertex* updatedorigin )
	{
		this->origin = updatedorigin;
	}

	HalfEdgeDataT getData()
	{
		return this->data;
	}

	void setData( HalfEdgeDataT updateddata )
	{
		this->data = updateddata;
	}






};
#endif