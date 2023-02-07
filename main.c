#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

StackNode_t** arrayOfVertices; // ����� ������ ������� ������
int amount;					   // ������� ������ �����

int main(int argc, char* argv[])
{
	system("chcp 1251");	
	int answer = 0;
	puts("������, ��� �������� ��������� ��� � �����? y/n");
	scanf("%c", &answer);
	if (answer == 'y')
	{
		if (inputFromFile(argc, argv) == -1)
		{
			puts("����������� ���� �� �����");
			return 0;
		}
	}
	else if (answer == 'n')
		inputFromUser();
	else
	{
		puts("���������� ������ ���");
		return 0;
	}
	puts("�������� ����");
	printGraph();

	int wasArticulation = 0;
	DFS(1, &wasArticulation); // ����� ����� �������� � ����-��� ����� �����, ��� � � �����
	if (!wasArticulation)
		puts("������ � ����� ����");
	freeAll();
}

void freeStack(StackNode_t* head)
{
	StackNode_t* tmp = (head)->previous;
	free(head);
	while (tmp != NULL)
	{
		head = tmp;
		tmp = tmp->previous;
		free(head);
	}
}

void pushStack(StackNode_t** head, int vertice)
{
	StackNode_t* next = (StackNode_t*)calloc(1, sizeof(StackNode_t));
	next->vertice = vertice;

	if (*head != NULL)
	{
		next->previous = *head;
	}
	*head = next;
}


void freeAll()
{
	extern int* exploredVertices;
	extern int* parentsOfVertices;
	extern int* low;
	extern int* depth;
	free(exploredVertices);
	free(parentsOfVertices);
	free(low);
	free(depth);
	for (int i = 1; i < amount; ++i)
	{
		freeStack(*(arrayOfVertices + i));
	}
}