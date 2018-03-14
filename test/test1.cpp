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
	int fCount = 0, pCount = 0, tCount =0, eCount = 0;
	char trash[50] = "";

	fin >> trash >> trash;
	fin >> trash;
	fin >> pCount;

	vector<vec3d> newPoints(pCount);


	for (int i = 0; i < pCount; i++)
	{
		fin >> newPoints[i].x
			>> newPoints[i].y
			>> newPoints[i].z;
	}

	gmsh.setVertices(newPoints);

	fin >> trash;
	fin >> eCount;
	
	eCount = 2 * eCount;

	vector<vec2i> newEdges(eCount);

	for (int i = 0; i < eCount; i=i+2)
	{
		fin >> newEdges[i].x
			>> newEdges[i].y;
		newEdges[i+1].x = newEdges[i].y;
		newEdges[i+1].y = newEdges[i].x;
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
	fin >> tCount;

	vector<vec4i> newTetra(tCount);

	for (int i = 0; i < tCount; i++)
	{
		fin >> trash
			>> newTetra[i].x
			>> newTetra[i].y
			>> newTetra[i].z
			>> newTetra[i].w;
	}
	
	for (int i = 0; i < fCount; i++)
	{
		cout << "Face number: " << i << endl;
		cout << " |1: " << newEdges[newFaces[i].x].x << " " << newEdges[newFaces[i].x].y
			<< " |2: " << newEdges[newFaces[i].y].x << " " << newEdges[newFaces[i].y].y
			<< " |3: " << newEdges[newFaces[i].z].x << " " << newEdges[newFaces[i].z].y << endl;
		cout << "_______________"<< endl;
	}

	fin.close();

	
	system("pause");
    return 0;
}