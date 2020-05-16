#pragma once
#include <cstddef>
#include "Graph.h"
template <class T>
struct Node {
	T data;
	Node* next;
	Node(T data)
	{
		this->data = data;
		this->next = NULL;
	}
};

template <class T>
class GraphList : public Graph<T>
{
private:
	Node** head = NULL;

	T* Data;

	int Size = 0;

	int MaxSize = 0;

public:
	GraphList(int MaxSize);

	~GraphList();

	void AddVertex(T) {Data[Size++] = data;}

	void DeleteVertex(int);

	void AddEdge(int, int);

	void DeleteEdge(int, int);

	bool ExistEdge(int, int);

	bool Connected();

	int Distance(int, int);

	void DFS(int , int* );
};

