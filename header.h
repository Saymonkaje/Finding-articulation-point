#pragma once

typedef struct  StackNode {
	int vertice;
	struct StacNode* previous;
}StackNode_t;

void inputFromUser();
void pushStack(StackNode_t** head, int vertice);
int inputFromFile(int argc, char* argv[]);
void DFS(int startVertice, int* wasArticulation);
void printGraph();
void freeStack(StackNode_t* head);
void freeAll();