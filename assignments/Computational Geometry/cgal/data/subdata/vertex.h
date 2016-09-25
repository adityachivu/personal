#ifndef VERTEX_H
#define VERTEX_H

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class HalfEdgeT;

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class VertexT
{
	typedef VertexT<VertexDataT, EdgeDataT, FaceDataT> Vertex;
	typedef HalfEdgeT<VertexDataT, EdgeDataT, FaceDataT> HalfEdge;
	
private:

	HalfEdge* incidentEdge;
	VertexDataT data;

protected:

public:
	/*
	getIncidentEdge
	setIncidentEdge
	getData
	setData
	*/

};

#endif