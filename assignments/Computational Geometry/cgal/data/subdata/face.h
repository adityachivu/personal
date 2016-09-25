#ifndef FACE_H
#define FACE_H

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class HalfEdgeT;

template<class VertexDataT, class EdgeDataT, class FaceDataT>
class FaceT
{
	typedef HalfEdgeT<VertexDataT, EdgeDataT, FaceDataT> HalfEdge;
	typedef FaceT<VertexDataT, EdgeDataT, FaceDataT> Face;

private:

	HalfEdge* boundary;
	FaceDataT data;

protected:

public:
	/*
	getBoundary
	setBoundary
	getData
	setData
	*/

};








#endif