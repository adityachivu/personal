#ifndef MESH_H
#define MESH_H

#include <vector>

#include "subdata/halfedge.h"
#include "subdata/vertex.h"
#include "subdata/face.h"

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class HalfEdgeT;

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class VertexT;

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class FaceT;

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class MeshT
{
	typedef MeshT<VertexDataT, HalfEdgeDataT, FaceDataT> Mesh;
	typedef HalfEdgeT<VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;
	typedef VertexT<VertexDataT, HalfEdgeDataT, FaceDataT> Vertex;
	typedef FaceT<VertexDataT, HalfEdgeDataT, FaceDataT> Face;	
	
private:
	std::vector<Vertex> vertices;
	std::vector<HalfEdge> edges;
	std::vector<Face> faces;

	unsigned int num_vertices;
	unsigned int num_edges;
	unsigned int num_faces;

	/*
	bool isSplitVertex( Vertex* );
	bool isMergeVertex( Vertex* );
	bool isTopVertex( Vertex* );
	bool isBottomVertex( Vertex* );
	bool isRegularVertex( Vertex* );
	Vertex* helper( HalfEdge* );
	*/

protected:

public:

	MeshT()
	{

	}

	MeshT( int nvertices, int nedges, int faces )
		:num_vertices(nvertices), num_edges(nedges), num_faces(faces)
	{
		vertices.resize( num_vertices );
		edges.resize( num_edges );
		faces.resize( num_faces );
	}

	MeshT( vector<VertexDataT> vertices, vector<HalfEdgeDataT> edges )
		:num_vertices(vertices.size()), num_edges(edges.size()/2)
	{

	}

	/*
	Mesh* triangulateMesh();
	Mesh* makeYMonotone();
	*/


};

/*
template<class VDT, class EDT, class FDT>
MeshT<VDT,EDT,FDT>* MeshT<VDT,EDT,FDT>::triangulateMesh()
{
	this.makeYMonotone();
	return mesh;
}

template<class VDT, class EDT, class FDT>
MeshT<VDT,EDT,FDT>* MeshT<VDT,EDT,FDT>::triangulateMesh()
{
	this.makeYMonotone();
	return mesh;
}
*/

#endif