#ifndef FACE_H
#define FACE_H

class HalfEdge;

class Face
{
private:
	HalfEdge* IncidentEdge;
	int faceID;

public:

	Face( int f )
		:faceID( f )
	{

	}

	int getFaceID()
	{
		return this->faceID;
	}

	void setIncEdge( HalfEdge* e )
	{
		this->IncidentEdge = e;
	}

	HalfEdge* getIncEdge() const
	{
		return this->IncidentEdge;
	}
};

#endif