#include "common.h"
#include "grainmesh.h"
#include "iotetgen.h"
#include <iostream>
#include <vector>
#include <fstream>


/*
Для более простой работы в common.h была добавлена струткура vec2i для более простого считывания ребер в стек
*/
using grain::GrainMesh;
using namespace grain;
using namespace std;

int main(int argc, char** argv)
{
	GrainMesh gmsh;

	ifstream fin("test1.ovm", ifstream::in);
	int fCount = 0, pCount = 0, tCount =0, eCount = 0;
	char trash[50] = "";
	
	/*
			Файл .ovm состоит из 4 частей Vertices, Edges, Faces, Polyhedra
			На первом этапе считываем все вершины (Vertices) и добавляем в mesh
			
			ПЕРВЫЙ ЭТАП
	*/
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


	/* КОНЕЦ ПЕРВОГО ЭТАПА
	
	   ВТОРОЙ ЭТАП
			Далее считываются грани. в ovm они хранятся как полуграни, поэтому для упрощения считывания заводим стек в 2 раза
			больше и идем по четным числам. Нечетные заполняем обратными полуребрами (ставим координаты наооброт)
	*/
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

	/* КОНЕЦ ВТОРОГО ЭТАПА
		
		ТРЕТИЙ ЭТАП
			Далее считываем треугольники. Для более простого объяснения кода рассмотрим пример.
			Представление треугольников в TetGrain -  0 1 3
			в OVM - 0 2 4
			в OVM ссылка идет на соответствующие полуребра - нулевое, второе и четвертое
			Поскольку мы заносили все полуребра, у нас не будет никаких проблем с учетом четности/нечетности.
			Представление нужных полуребер 0 1 ; 1 3 ; 3 0 ;
			Как можно заметить для получения того же, что было в TetGrain необходимо взять первую координату.
			Затем просто добавить и внести треугольники в меш.
	*/

	fin >> trash;
	fin >> fCount;

	vector<vec3i> newFaces(fCount);

	for (int i = 0; i < fCount; i++)
	{
		fin >> trash
			>> newFaces[i].x
			>> newFaces[i].y
			>> newFaces[i].z;

		newFaces[i].x = newEdges[newFaces[i].x].x;
		newFaces[i].y = newEdges[newFaces[i].y].x;
		newFaces[i].z = newEdges[newFaces[i].z].x;

	}
	/*КОНЕЦ ТРЕТЬЕГО ЭТАПА

	  ЧЕТВЕРТЫЙ ЭТАП
		на 4 этапе считываем тетраэдры. В результате нескольких тестов было установлено, что OVM хранит
		нечетные номера, поделив которые на 2 (числа целые) мы получим исходное (TetGrain) задание тетраэдров.
		Затем добавляем тетраэдры в меш.
		
	*/
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

		newTetra[i].x = newTetra[i].x / 2;
		newTetra[i].y = newTetra[i].y / 2;
		newTetra[i].z = newTetra[i].z / 2;
		newTetra[i].w = newTetra[i].w / 2;
	}
	

	gmsh.setTriangles(newFaces);
	gmsh.setTetra(newTetra);

	/*
		Внесение в меш и сохранение файлов вершин, треугольников и тетраэдров
	*/
	saveNodeFile("test.node", &gmsh);
	saveFaceFile("test.face", &gmsh);
	saveEleFile("test.ele", &gmsh);

	fin.close();

    return 0;
}