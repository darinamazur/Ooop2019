#pragma once
#include <vector>
#include "Graph.h"
template <class T>
class  GraphMatrix : public Graph<T>{
private:
	bool**Matrix;
	int Size; T*Data;
	int SizeMax = 0;
	
public:
	GraphMatrix(int);

	~GraphMatrix();

	void AddVertex(T);

	void DeleteVertex(int);

	void AddEdge(int, int){Matrix[first][second] = true;}
		
	void DeleteEdge(int, int) {Matrix[first][second] = false;}

	bool ExistEdge(int, int) {return Matrix[first][second];}

	std::vector<int> findConnection(int);

    void DFS(int, int*);

	bool Connected();

	int Distance(int, int); 
};
