#include "BF.h"

BF::~BF()
{
	delete[] resultPermut;
	delete[] permuTab;
	delete[] visited;
	//delete myGraph;
}

void BF::brutForce(int v)
{
	int u;
	permuTab[currentSize++] = v;//permuTab jest zawsze tej samej wielkosci, current size to poprwane zapelnienie
	if (currentSize < matrixSize)
	{
		visited[v] = true;
		for (u = 0; u < matrixSize; u++)
			if (!visited[u])
			{
				//std::cout << "edge: " << myGraph->getValueOfEdge(v, u) << std::endl;
				activeCostOfPermut += myGraph->getValueOfEdge(v,u);
				brutForce(u);	//rekurencja
				activeCostOfPermut -= myGraph->getValueOfEdge(v, u);
			}
		visited[v] = false;
	}
	else
	{
		//mamy juz wszystkie wierzcholki
		activeCostOfPermut += myGraph->getValueOfEdge(v, startVert);//laczymy kolo
		if (activeCostOfPermut < minCostResult)		
		{
			minCostResult = activeCostOfPermut; 
			for (u = 0; u < currentSize; u++)
				resultPermut[u] = permuTab[u];
		}
		activeCostOfPermut -= myGraph->getValueOfEdge(v, startVert);
	}
	currentSize--;//!!!!!!!!!cofamy si� w tablicy- wracamy poprawiac te ktore do tej pory byly ustalone
}

void BF::intitialBrutForce(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	resultPermut = new int[matrixSize];
	permuTab = new int[matrixSize];
	visited = new bool[matrixSize];
	//W = new int* [n];
	myGraph = newGraphData;
	std::cout << "Drukuje dane wczytanego grafu:"<<std::endl;
	myGraph->printGraph();
	for (int i = 0; i < matrixSize; i++)
	{
		visited[i] = false;
	}
	currentSize = 0;
	minCostResult = 99999;
	activeCostOfPermut = startVert = 0;
	brutForce(startVert);

	//sekcja wyswietlania
	for (int i = 0; i < matrixSize; i++) std::cout << resultPermut[i] << " ";
	std::cout << startVert << std::endl;
	std::cout << "d = " << minCostResult << std::endl;
}
