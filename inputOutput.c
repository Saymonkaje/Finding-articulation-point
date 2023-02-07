#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern StackNode_t** arrayOfVertices;
extern int amount;

void initializeArrays()
{
	extern int* exploredVertices;
	extern int* parentsOfVertices;
	extern int* low;
	extern int* depth;
	low = calloc(amount + 1, sizeof(int));
	depth = calloc(amount + 1, sizeof(int));
	arrayOfVertices = calloc(amount+1, sizeof(StackNode_t*));
	exploredVertices = calloc(amount+1, sizeof(int));
	parentsOfVertices = calloc(amount+1, sizeof(int));
}

void printGraph()
{
	StackNode_t* tmp = NULL;
	for (int i = 1; i <= amount; ++i)
	{
		tmp = arrayOfVertices[i];
		printf("\nВершини суміжні до вершини № %d:\n", i);
		while (tmp != NULL)
		{
			printf("[%d] ", tmp->vertice);
			tmp = tmp->previous;
		}
	}
	puts("");
}

void inputFromUser()
{
	puts("Введіть кількість вершин");
	if (scanf("%d", &amount) == 0)
	{
		puts("Некоректні дані");
		exit(0);
	}
	if (amount < 1)
	{
		puts("Введена некоректна кількість вершин");
		exit(0);
	}
	initializeArrays();
	puts("Нумерація вершин починається з 1");
	puts("Вводити треба тільки ті суміжні вершини номер який більший за поточну вершину");
	int buf;
	for (int i1 = 1; i1 <= amount; ++i1)
	{
		printf("Введіть список суміжних вершин до вершини №%d (закінчіть введення нулем):\n", i1);
		int i2 = 1;
		while (i2 <= amount)
		{
			if (scanf("%d", &buf) == 0)
			{
				puts("Некоректні дані");
				exit(0);
			}
			if (buf == 0) break;
			pushStack(arrayOfVertices + i1, buf);
			pushStack(arrayOfVertices + buf, i1); // Одне й теж ребро додається автоматично
			++i2;
		}
	}

}

int inputFromFile(int argc, char* argv[])
{
	char pathToFile[150];
	FILE* data = NULL;

	if (argc > 1)
	{
		puts("Шлях до файлу був зчитаний як аргумент командного рядка");
		strcpy(pathToFile, argv[1]);
	}
	else
	{
		puts("Введіть шлях до файлу:");
		gets(pathToFile);
	}
	if ((data = fopen(pathToFile, "r")) == NULL)
		return -1;

	fscanf(data, "%d", &amount);
	initializeArrays();
	int buf;
	for (int i1 = 1; i1 <= amount; ++i1)
	{
		int amountOfBytes = 3;
		for (int ten = 10; i1/ ten != 0; ten *= 10, amountOfBytes++);

		for (; amountOfBytes > 0; --amountOfBytes)
			fgetc(data);
		int i2 = 1;

		while (i2 <= amount)
		{
			fscanf(data, "%d", &buf);
			if (buf == 0) break;
			pushStack(arrayOfVertices + i1, buf);// Одне й теж ребро додається автоматично
			pushStack(arrayOfVertices + buf, i1);
			++i2;
		}
	}
	fclose(data);
}