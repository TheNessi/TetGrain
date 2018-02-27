#include "common.h"
#include "grainmesh.h"
#include "iotetgen.h"
#include <iostream>
#include <vector>

using grain::GrainMesh;
using namespace grain;
using namespace std;

int main(int argc, char** argv)
{
	GrainMesh gmsh;
	
	// Geerate stub tetrahedron 
	//gmsh.makeStubTetra();
	
	
	readNodeFile("D:\study\Graphics\Meshes\TetGrain\data\cube.node", &gmsh);
	readFaceFile("D:\study\Graphics\Meshes\TetGrain\data\cube.face", &gmsh);
	//saveEleFile("stubtetra.elle", &gmsh);

	cout << gmsh.getVerticesCount()<< endl;
	system("pause");
    return 0;
}