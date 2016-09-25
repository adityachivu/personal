#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Point;

class Segment
{
private:
	Point begin;
	Point end;
	float length;

public:

	void setEndPoints( Point b, Point e )
	{
		this->begin = b;
		this->end = e;

	}

	std::pair<Point, Point> getEndPoints()
	{
		return std::make_pair( this->begin, this->end );
	}

};

#endif