#include <iostream>
#include <vector>
#include <string>
#include <cstring>

template<class T>
class Graph//abstract
{
	virtual void AddVertex(T) = 0;
	virtual void DeleteVertex(int) = 0;
	virtual void AddEdge(int, int) = 0;
	virtual void DeleteEdge(int, int) = 0;
	virtual bool ExistEdge(int, int) = 0;
};

