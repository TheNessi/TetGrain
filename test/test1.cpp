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

	ifstream fin("test1.ovm", std::ifstream::in);
	int fCount = 0;
	char trash[50] = "";

	fin >> trash >> trash;
	fin >> trash;
	fin >> fCount;

	std::vector<vec3d> newPoints(fCount);
	std::vector<char> newPLabels(fCount);

	for (int i = 0; i < fCount; i++)
	{
		fin >> trash
			>> newPoints[i].x
			>> newPoints[i].y
			>> newPoints[i].z
			>> newPLabels[i];
	}

	gmsh.setVertices(newPoints);
	gmsh.setVerticesLabels(newPLabels);

	fin.close();

	cout << gmsh.getVerticesCount() << endl;
	system("pause");
    return 0;
}