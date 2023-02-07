#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern int amount;
extern StackNode_t **arrayOfVertices;

int* exploredVertices;// 0 означає, що вершина ще не відкрита, 1 - відкрита, але не опрацьована, 2 - опрацьована
int* parentsOfVertices; // Масив предків для вершин
int* low;				// масив за допомогою якого перевіряється існування зворотніх ребер
int* depth;				// Масив глибин(часу відкриття) кожної вершини
int time = 1;			// для визначення часу входження

void DFS(int currentVertice, int* wasArticulation)
{
	StackNode_t* nextVertice;
	exploredVertices[currentVertice] = 1;
	nextVertice = arrayOfVertices[currentVertice];

	depth[currentVertice] = time;
	low[currentVertice] = time;
	time++;
	int childCount = 0;
	int isSharnir = 0;
	while (nextVertice != NULL)
	{
		if (exploredVertices[nextVertice->vertice] == 0)
		{
			parentsOfVertices[nextVertice->vertice] = currentVertice;
			childCount++;
			DFS(nextVertice->vertice, wasArticulation);
			if (low[nextVertice->vertice] == depth[currentVertice])
				isSharnir = 1;
			low[currentVertice] = low[currentVertice] < low[nextVertice->vertice] ? low[currentVertice] : low[nextVertice->vertice];
		}
		else if (depth[nextVertice->vertice] < low[currentVertice])
			low[currentVertice] = depth[nextVertice->vertice];
		nextVertice = nextVertice->previous;
	}
	if ((parentsOfVertices[currentVertice] != NULL && isSharnir) || (parentsOfVertices[currentVertice] == NULL && childCount > 1))
	{
		printf("Вершина [%d] - шарнір\n", currentVertice);
		*wasArticulation = 1;
	}
}
