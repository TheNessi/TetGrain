#include "common.h"
#include "grainmesh.h"
#include "iotetgen.h"
#include <iostream>
#include <vector>
#include <fstream>

using grain::GrainMesh;
using namespace grain;
using namespace std;

int main(int argc, char** argv)
{
	GrainMesh gmsh;

	ifstream fin("test1.ovm", ifstream::in);
	int fCount = 0;
	char trash[50] = "";

	fin >> trash >> trash;
	fin >> trash;
	fin >> fCount;

	vector<vec3d> newPoints(fCount);


	for (int i = 0; i < fCount; i++)
	{
		fin >> newPoints[i].x
			>> newPoints[i].y
			>> newPoints[i].z;
	}

	gmsh.setVertices(newPoints);

	fin >> trash;
	fin >> fCount;
	
	vector<vec2i> newEdges(fCount);

	for (int i = 0; i < fCount; i++)
	{
		fin >> newEdges[i].x
			>> newEdges[i].y;
	}

	fin >> trash;
	fin >> fCount;
	vector<vec3i> newFaces(fCount);

	for (int i = 0; i < fCount; i++)
	{
		fin >> trash
			>> newFaces[i].x
			>> newFaces[i].y
			>> newFaces[i].z;
	}

	fin >> trash;
	fin >> fCount;

	vector<vec4i> newTetra(fCount);

	for (int i = 0; i < fCount; i++)
	{
		fin >> trash
			>> newTetra[i].x
			>> newTetra[i].y
			>> newTetra[i].z
			>> newTetra[i].w;
	}


	fin.close();


	cout << gmsh.getVerticesCount() << endl;
	system("pause");
    return 0;
}