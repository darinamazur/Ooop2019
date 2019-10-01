#include "GraphList.h"
#include <queue>

template<class T>
void GraphList<T>::DeleteVertex(int index)
{
	Node* temp = head[index];
	Node* next;
	int counter(0);
	while (temp != NULL) {
		next = temp->next;
		counter++;
		if (counter == index);
		delete temp;
		else
		temp = next;
	}
}

template<class T>
void GraphList<T>::AddEdge(int first, int second)
{
	if (head[first] == NULL) head[first] = new Node(second);
	else {
		Node* temp = head[first];
		head[first] = new Node(second);
		head[first]->next = temp;
	}
}

template<class T>
void GraphList<T>::DeleteEdge(int first, int second)
{
	Node* current = head[first];
	if (current == NULL) return; 
	if (current->data == second) {
		head[first] = current->next;
		free(current);
		return;
	}
	Node* prev;
	while (current != NULL && current->data != second) {
		prev = current;
		current = current->next;
	}

	if (current == NULL) return; 
	prev->next = current->next;
	free(current);
}

template<class T>
bool GraphList<T>::ExistEdge(int first, int second)
{
	Node* x = head[first];
	while (x != NULL) {
		if (head->data == second) return true;
		x = x->next;
	}
	return false;
}

template<class T>
void GraphList<T>::DFS(int v, int* visited)
{
	visited[v] = 1;
	Node* temp = head[v];
	while (temp != NULL) {
		if (!visited[temp->data]) DFS(temp->data, visited);
		temp = temp->next;
	}
}

template<class T>
bool GraphList<T>::Connected()//is 
{
	int* used = new int[Size];
	for (int i = 0; i < Size; i++)
		used[i] = false;
	DFS(0, used);
	for (int i = 0; i < Size; i++)
		if (used[i] == false) return false;
	return true;
}

template<class T>
int GraphList<T>::Distance(int first, int second) // find distant using iterative dfs algorithm
{
	std::queue<int> Queue;
	int startVertice = first;
	int* distance = new int[Size];
	bool* used = new bool[Size];
	for (int i = 0; i < Size; i++) {
		used[i] = distance[i] = false;
	}
	used[startVertice] = true;
	Queue.push(startVertice);
	int front;
	while (!Queue.empty()) {
		front = Queue.front();Queue.pop();
		for (int i = 0; i < Size; i++) {
			Node* temp = head[i];
			while (temp != NULL) {
				if (!used[i]) {distance[i]++;
	used[i] = true; Queue.push(i);
				}
				temp = temp->next;
			}
		}
	}
	return distance[u];
}

template<class T>
GraphList<T>::GraphList(int MaxSize)
{
	head = new Node * [MaxSize];
	for (int i = 0; i < MaxSize; i++) head[i] = NULL;
	Data = new T[MaxSize];
	this->MaxSize = MaxSize;
}

template<class T>
GraphList<T>::~GraphList()
{
	for (int i = 0; i < Size; i++) {
		Node* temp = head[i], next;
		while (temp != NULL) {
			next = temp->next;
			delete temp;
		}
	}
	delete[] Data;
}


