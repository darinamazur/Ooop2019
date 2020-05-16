#include "GraphMatrix.h"
#include <queue>

template<class T>
GraphMatrix<T>::GraphMatrix(int SizeMax)
{
	Matrix = new int* [SizeMax];
	for (int i = 0; i < SizeMax; i++) 
	Matrix[i] = new int[SizeMax];
	Data = new T[SizeMax];
	this->SizeMax = SizeMax;
}

template<class T>
GraphMatrix<T>::~GraphMatrix()
{
	for (int i = 0; i < SizeMax; i++) delete[] Matrix[i];
	delete[] Data;
}

template<class T>
void GraphMatrix<T>::AddVertex(T value)
{
	int newSize = Size;
	Size++;
	for (int i = 0; i < Size; i++) {
		Matrix[i][newSize] = false;
		Matrix[newSize][i] = false;
	}
	Data[Size] = value;
}

template<class T>
void GraphMatrix<T>::DeleteVertex(int index)
{
	for (int i = 0; i < Size; i++) {
		Matrix[i][index] = false;
		Matrix[index][i] = false;
	}
	Data[index] = NULL;
}


template<class T>
std::vector<int> GraphMatrix<T>::findConnection(int VNumber)
{
	std::vector<int>Connection;
	for (int i = 0; i < Size; i++) {
		if (Matrix[VNumber][i])
	Connection.push_back(i);
	}

}

template<class T>
void GraphMatrix<T>::DFS(int v, int* used)
{
	used[v] = 1;
	for (int i = 0; i < Size; i++)
		if (Matrix[v][i] && !used[i])DFS(i, used, Matrix);
}

template<class T>
bool GraphMatrix<T>::Connected()
{
	int* visited = new int[Size];
	for (int i = 0; i < Size; i++) visited[i] = 0;
	DFS(0, visited);
	for (int i = 0; i < Size; i++)
		if (!visited[i]) return false;
	return true;
}

template<class T>
int GraphMatrix<T>::Distance(int first, int second)
{
	std::queue<int> Queue;
	int startVertice = first;
	int* distance = new int[Size];
	bool* used = new bool[Size];
	for (int i = 0; i < Size; i++) {
		used[i] = false;
		distance[i] = false;
	}
	used[startVertice] = true;
	Queue.push(startVertice);
	int front;
	while (!Queue.empty()) {
		front = Queue.front();
		Queue.pop();
		for (int i = 0; i < Size; i++) {
			if (Matrix[front][i] == true && used[i] == false) {
				distance[i]++;
				used[i] = true;
				Queue.push(i);
			}
		}
	}
	return distance[second];
}



