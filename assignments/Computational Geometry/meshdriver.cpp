#include <cstdio>
#include <iostream>
#include "temp/data/mesh.h"
#include "temp/visuals/draw.h"



int main( int argc, char* argv[] )
{
    glutInit( &argc, argv);
    int num;

    std::cout << "Enter num:" << std::endl;
    std::cin >> num;

    std::vector<Point> vertices;
    float x, y;

    for ( int i = 0; i < num; i++ )
    {
    	std::cin >> x >> y;
    	Point a;
    	a.coord( std::make_pair( x, y ) );
    	vertices.push_back( a );
    }

    Mesh mymesh;
    MeshDraw mypoly( &mymesh );

    mymesh.createPolyMesh( vertices );
    std::cout<< "tp\n";
    mymesh.printMesh();
    //mymesh.addEdge( 3, 9 );
    //mymesh.printMesh();
    mymesh.triangulate();
    
    mypoly.draw();
    //std::cout<< "tptp\n";
    mymesh.printMesh();

	return 0;
}
