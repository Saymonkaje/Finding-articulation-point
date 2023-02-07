#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern int amount;
extern StackNode_t **arrayOfVertices;

int* exploredVertices;// 0 ������, �� ������� �� �� �������, 1 - �������, ��� �� �����������, 2 - �����������
int* parentsOfVertices; // ����� ������ ��� ������
int* low;				// ����� �� ��������� ����� ������������ ��������� �������� �����
int* depth;				// ����� ������(���� ��������) ����� �������
int time = 1;			// ��� ���������� ���� ���������

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
		printf("������� [%d] - �����\n", currentVertice);
		*wasArticulation = 1;
	}
}
